//============================================================================
// Name        : Controller.cpp
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Dec 23, 2025
// Description : This class is controller for a main app functionality
//============================================================================

#include "../../console_art/controller/Controller.h"
namespace consoleart
{
Controller::Controller(AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter) : Controller("", notifier, menu, asciiPrinter)
{
}
Controller::Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter) :
		selectedImageIndex(0), isRunnable(true), messenger(notifier), menuInterface(menu), abstractAsciiPrinter(asciiPrinter), workspacePath(path)
{
	supportedImageFormats[".pcx"] = consoleartlib::ImageType::PCX;
	supportedImageFormats[".bmp"] = consoleartlib::ImageType::BMP;
	supportedImageFormats[".ppm"] = consoleartlib::ImageType::PPM;
	supportedImageFormats[".png"] = consoleartlib::ImageType::PNG;
	supportedImageFormats[".jpg"] = consoleartlib::ImageType::JPG;
	supportedImageFormats[".jpeg"] = consoleartlib::ImageType::JPG;
	supportedImageFormats[".JPEG"] = consoleartlib::ImageType::JPG;
	supportedImageFormats[".gif"] = consoleartlib::ImageType::GIF;
	supportedImageFormats[".hdr"] = consoleartlib::ImageType::HDR;
	supportedImageFormats[".tga"] = consoleartlib::ImageType::TGA;
	supportedImageFormats[".dcx"] = consoleartlib::ImageType::DCX;
	// Functions
	argumentMethods["--image"] = [&](const std::vector<std::string>& vector)
	{
		for (const std::string& path : vector)
			addImageAsync(loadImageAsync(workspacePath + path));
		if (!images.empty())
			selectImage(images.size() - 1);
	};
	argumentMethods["--path"] = [&](const std::vector<std::string>& vector) { if (vector.empty()) return; setWorkspace(vector[0]); };
	argumentMethods["--p"] = argumentMethods["--path"];
	argumentMethods["--loadAll"] = [&](const std::vector<std::string>&) { std::thread([&]() { loadAllImagesAsync(); }).detach(); };
	argumentMethods["--binomial"] = [&](const auto& vector)
	{
		auto res = Math::MathUtils::binomialDistribution(vector);
		consolelib::output::configStream(16);
		consolelib::output::printResults<int, long double>(res);
		isRunnable = false;
	};
	argumentMethods["--removeGray"] = [&](const auto&)
	{
		loadAllImagesAsync();
		for (const VectorData& image : images)
			consoleartlib::simple_edit::removeGrayFromTexture(*image.imageUptr.get());
		isRunnable = false;
	};
	argumentMethods["--splitGIF"] = [&](const auto& vector)
	{
		if (vector.size() == 0)
			return;
		consoleartlib::ImageGIF gif(vector[0]);
		if (gif)
		{
			gif.spitIntoPNGs();
		}
		isRunnable = false;
	};
	argumentMethods["--overlayTextures"] = [&](const auto& vector)
	{
		if (vector.size() == 0)
			return;
		consoleartlib::Image* baseLayer = nullptr;
		for (const std::string& baseImage : vector)
		{
			baseLayer = loadImageAsync(workspacePath + baseImage);
			if (baseLayer == nullptr || !baseLayer->isLoaded())
				return;
			for (const VectorData& image : images)
				consoleartlib::simple_edit::overlayTextures(*baseLayer, *image.imageUptr.get());
			delete baseLayer;
		}
		isRunnable = false;
	};
	argumentMethods["--packIntoDCX"] = [&](const auto& vector)
	{
		if (vector.size() == 0)
			return;
		consoleartlib::Image* image = nullptr;
		consoleartlib::ImageDCX imagePack("packed.dcx", vector.size());
		for (const std::string& imagePath : vector)
		{
			image = loadImageAsync(workspacePath + imagePath);
			if (image == nullptr || !image->isLoaded())
				return;
			switch (image->getImageInfo().imageFormat)
			{
				case consoleartlib::ImageType::PCX: imagePack.addImage(((consoleartlib::ImagePCX*)image)->convertToPage()); break;
				default: delete image;
			}
		}
		imagePack.saveImage();
		isRunnable = false;
	};
}
Controller::~Controller()
{
	if (menuInterface)
		delete menuInterface;
	if (messenger)
		delete messenger;
	if (abstractAsciiPrinter)
		delete abstractAsciiPrinter;
	std::cout << "Controller deleted" << std::endl;
}

void Controller::configure(consolelib::argVector& config)
{
	auto it = argumentMethods.find("");
	for (const consolelib::argVectorItem& argument : config)
	{
		it = argumentMethods.find(argument.first);
		if (it != argumentMethods.end())
			it->second(argument.second);
		else
			messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "Invalid argument [" + argument.first + "]\n");
	}
}

void Controller::configure(consolelib::argMap& config)
{
	auto it = argumentMethods.find("");
	for (const std::pair<const std::string, std::vector<std::string>>& argument : config)
	{
		it = argumentMethods.find(argument.first);
		if (it != argumentMethods.end())
			it->second(argument.second);
		else
			messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "Invalid argument [" + argument.first + "]\n");
	}
}

void Controller::convertImage(consoleartlib::Image* image, consoleartlib::AsciiConverter::CHAR_SETS charSet)
{
	if (image == nullptr || !*image || abstractAsciiPrinter == nullptr)
		return;
	consoleartlib::AsciiConverter ac(*image);
	if (charSet == consoleartlib::AsciiConverter::CHAR_SETS::CHAR_SETS_COUNT)
		return;
	ac.setCharSet(charSet);
	messenger->messageUser(AbstractNotifier::MessageType::NOTIFICATION, std::string("Started conversion of image: ").append(image->getFilename()));
	if (!ac.convertToASCII())
	{
		messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, "Image conversion has failed!\n");
		return;
	}
	messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "Conversion to ascii done!\n");
	abstractAsciiPrinter->setTarget(&ac);
	abstractAsciiPrinter->printToFile();
}

void Controller::loadAllImagesAsync()
{
	std::string extension = "";
	std::string itDir = workspacePath;
	if (itDir == "")
		itDir = std::filesystem::current_path().generic_string();
	try
	{
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(itDir))
		{
			extension = entry.path().extension().generic_string();
			std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
			addImageAsync(loadImageAsync(entry.path().generic_string(), extension));
		}
	}
	catch (std::runtime_error& e)
	{
		messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return;
	}
	std::lock_guard<std::mutex> lock(mutexImages);
	std::sort(images.begin(), images.end());
	messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "All loaded!\n");
}

Controller::IndexDataType Controller::addImageAsync(consoleartlib::Image* image)
{
	static IndexDataType index = 0;
	if (image == nullptr)
		return 0;
	if (!image->isLoaded())
	{
		messenger->messageUser(AbstractNotifier::MessageType::PROBLEM, image->getFileStatus() + "\n");
		delete image;
		image = nullptr;
		return 0;
	}
	std::lock_guard<std::mutex> lock(mutexImages);
	if (!images.empty())
	{
		for (VectorData& existingImage : images)
		{
			if (existingImage.imageUptr->getFilename() == image->getFilename())
			{
				delete image;
				image = nullptr;
				return 0;
			}
		}
	}
	index++;
	images.emplace_back(VectorNode{ index, std::unique_ptr<consoleartlib::Image>(image)});
	return index;
}

consoleartlib::Image* Controller::loadImageAsync(const std::string& path)
{
	std::string extension = "";
	try
	{
		extension = path.substr(path.find_last_of("."));
	}
	catch (std::exception& e)
	{
		messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return nullptr;
	}
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
	return loadImageAsync(path, extension);
}

consoleartlib::Image* Controller::loadImageAsync(const std::string& path, const std::string& extension)
{
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	if (supportedImageFormats.contains(extension))
		switch (supportedImageFormats.at(extension))
		{
			case consoleartlib::ImageType::BMP: return new consoleartlib::ImageBMP(path);
			case consoleartlib::ImageType::PCX: return new consoleartlib::ImagePCX(path);
			case consoleartlib::ImageType::PPM: return new consoleartlib::ImagePPM(path);
			case consoleartlib::ImageType::PNG: return new consoleartlib::ImagePNG(path);
			case consoleartlib::ImageType::JPG: return new consoleartlib::ImageJPG(path);
			case consoleartlib::ImageType::GIF: return new consoleartlib::ImageGIF(path);
			case consoleartlib::ImageType::HDR: return new consoleartlib::ImageHDR(path);
			case consoleartlib::ImageType::TGA: return new consoleartlib::ImageTGA(path);
			case consoleartlib::ImageType::DCX: return new consoleartlib::ImageDCX(path);
			default: return nullptr;
		}
	messenger->messageUser(AbstractNotifier::MessageType::WARNING, "Unsupported format [" + extension + "]\n");
	return nullptr;
}

void Controller::notifyUser(AbstractNotifier::MessageType messageType, const std::string& message)
{
	if (messenger)
		messenger->messageUser(messageType, message);
	else
		std::cout << message;
}

void Controller::displayImageInfo(const consoleartlib::Image& image)
{
	if (messenger)
		messenger->displayImageInfo(image);
	else
		std::cout << image;
}

void Controller::setWorkspace(std::string path)
{
	if (path.length() == 0)
		return;
	if ((path.length() > 0) && (path.substr(path.length() - 1) != "/"))
		path.append("/");
	workspacePath = path;
	messenger->messageUser(AbstractNotifier::MessageType::INFO, "Workspace path: " + workspacePath + "\n");
}

void Controller::setNotifier(AbstractNotifier* notifier)
{
	if (notifier)
	{
		if (messenger)
			delete messenger;
		messenger = notifier;
	}
}

void Controller::setMenu(IMenu* imenu)
{
	if (imenu)
	{
		if (menuInterface)
			delete menuInterface;
		menuInterface = imenu;
	}
}

const std::string& Controller::getWorkspace()
{
	return workspacePath;
}

void Controller::selectImage(IndexDataType selectedImageIndex)
{
	this->selectedImageIndex = selectedImageIndex;
}

Controller::IndexDataType Controller::getSelectedImageIndex() const
{
	return selectedImageIndex;
}

consoleartlib::Image* Controller::getSelectedImage()
{
	if (selectedImageIndex == 0)
		return nullptr;
	for (VectorNode& img : images)
		if (img.index == selectedImageIndex)
			return img.imageUptr.get();
	return nullptr;
}

int Controller::getNumberOfLoadedImages()
{
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	return images.size();
}

void Controller::iterateImagesAsync(std::function<void(const VectorNode& node)> actionOnImage)
{
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	for (const VectorNode& image : images)
		actionOnImage(image);
}

}

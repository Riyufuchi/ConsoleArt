//============================================================================
// Name        : Controller.cpp
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Nov 07, 2025
// Description : This class is controller for a main app functionality
//============================================================================

#include "Controller.h"

namespace ConsoleArt
{
Controller::Controller(AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter) : Controller("", notifier, menu, asciiPrinter)
{
}
Controller::Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter) : isRunnable(true), messenger(notifier), menuInterface(menu), abstractAsciiPrinter(asciiPrinter), selectedImage(nullptr), workspacePath(path)
{
	supportedImageFormats[".pcx"] = Images::ImageType::PCX;
	supportedImageFormats[".bmp"] = Images::ImageType::BMP;
	supportedImageFormats[".ppm"] = Images::ImageType::PPM;
	supportedImageFormats[".png"] = Images::ImageType::PNG;
	supportedImageFormats[".jpg"] = Images::ImageType::JPG;
	supportedImageFormats[".jpeg"] = Images::ImageType::JPG;
	supportedImageFormats[".JPEG"] = Images::ImageType::JPG;
	supportedImageFormats[".gif"] = Images::ImageType::GIF;
	supportedImageFormats[".hdr"] = Images::ImageType::HDR;
	// Functions
	argumentMethods["--image"] = [&](const std::vector<std::string>& vector)
	{
		for (const std::string& path : vector)
			addImageAsync(loadImageAsync(workspacePath + path));
		if (!images.empty())
			selectedImage = images[0].get();
	};
	argumentMethods["--path"] = [&](const std::vector<std::string>& vector) { if (vector.empty()) return; setWorkspace(vector[0]); };
	argumentMethods["--p"] = argumentMethods["--path"];
	argumentMethods["--loadAll"] = [&](const std::vector<std::string>&) { std::thread([&]() { loadAllImagesAsync(); }).detach(); };
	argumentMethods["--binomial"] = [&](const auto& vector)
	{
		auto res = Math::MathUtils::binomialDistribution(vector);
		Other::OtherhUtils::printResults<int, long double>(res);
		isRunnable = false;
	};
	argumentMethods["--removeGray"] = [&](const auto&)
	{
		loadAllImagesAsync();
		for (const std::unique_ptr<Images::Image>& image : images)
			ImageUtils::SimpleEdit::removeGrayFromTexture(*image.get());
		isRunnable = false;
	};
	argumentMethods["--overlayTextures"] = [&](const auto& vector)
	{
		if (vector.size() == 0)
			return;
		Images::Image* baseLayer = nullptr;
		for (const std::string& baseImage : vector)
		{
			baseLayer = loadImageAsync(workspacePath + baseImage);
			if (baseLayer == nullptr || !baseLayer->isLoaded())
				return;
			for (const std::unique_ptr<Images::Image>& image : images)
				ImageUtils::SimpleEdit::overlayTextures(*baseLayer, *image.get());
			delete baseLayer;
		}
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

void Controller::configure(ConsoleLib::argVector& config)
{
	auto it = argumentMethods.find("");
	for (const ConsoleLib::argVectorItem& argument : config)
	{
		it = argumentMethods.find(argument.first);
		if (it != argumentMethods.end())
			it->second(argument.second);
		else
			messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Invalid argument [" + argument.first + "]\n");
	}
}

void Controller::configure(ConsoleLib::argMap& config)
{
	auto it = argumentMethods.find("");
	for (const std::pair<const std::string, std::vector<std::string>>& argument : config)
	{
		it = argumentMethods.find(argument.first);
		if (it != argumentMethods.end())
			it->second(argument.second);
		else
			messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Invalid argument [" + argument.first + "]\n");
	}
}

void Controller::convertImage(Images::Image* image, ImageUtils::AsciiConverter::CHAR_SETS charSet)
{
	if (image == nullptr || !*image || abstractAsciiPrinter == nullptr)
		return;
	ImageUtils::AsciiConverter ac(*image);
	if (charSet == ImageUtils::AsciiConverter::CHAR_SETS::CHAR_SETS_COUNT)
		return;
	ac.setCharSet(charSet);
	messenger->messageUser(AbstractNotifier::MessageType::NOTIFICATION, std::string("Started conversion of image: ").append(image->getFilename()));
	if (!ac.convertToASCII())
	{
		messenger->messageUser(AbstractNotifier::MessageType::ERROR, "Image conversion has failed!\n");
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
			extension = entry.path().extension();
			std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
			addImageAsync(loadImageAsync(entry.path(), extension));
		}
	}
	catch (std::runtime_error& e)
	{
		messenger->messageUser(AbstractNotifier::MessageType::EXCEPTION, std::string(e.what()).append("\n"));
		return;
	}
	std::lock_guard<std::mutex> lock(mutexImages);
	std::sort(images.begin(), images.end(), [](const std::unique_ptr<Images::Image>& a, const std::unique_ptr<Images::Image>& b)
	{
		return a->getFilename() < b->getFilename();
	});
	messenger->messageUser(AbstractNotifier::MessageType::SUCCESFUL_TASK, "All loaded!\n");
}

bool Controller::addImageAsync(Images::Image* image)
{
	if (image == nullptr)
		return false;
	if (!image->isLoaded())
	{
		messenger->messageUser(AbstractNotifier::MessageType::ERROR, image->getFileStatus() + "\n");
		delete image;
		image = NULL;
		return false;
	}
	std::lock_guard<std::mutex> lock(mutexImages);
	if (!images.empty())
	{
		for (std::unique_ptr<Images::Image>& existingImage : images)
		{
			if (existingImage->getFilename() == image->getFilename())
			{
				delete image;
				image = NULL;
				return false;
			}
		}
	}
	images.emplace_back(std::unique_ptr<Images::Image>(image));
	return true;
}

Images::Image* Controller::loadImageAsync(const std::string& path)
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

Images::Image* Controller::loadImageAsync(const std::string& path, const std::string& extension)
{
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	if (supportedImageFormats.contains(extension))
		switch (supportedImageFormats.at(extension))
		{
			case Images::BMP: return new Images::ImageBMP(path);
			case Images::PCX: return new Images::ImagePCX(path);
			case Images::PPM: return new Images::ImagePPM(path);
			case Images::PNG: return new Images::ImagePNG(path);
			case Images::JPG: return new Images::ImageJPG(path);
			case Images::GIF: return new Images::ImageGIF(path);
			case Images::HDR: return new Images::ImageHDR(path);
			default: return nullptr;
		}
	messenger->messageUser(AbstractNotifier::MessageType::WARNING, "Unsupported format [" + extension + "]\n");
	return nullptr;
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

void Controller::setSelectedImage(Images::Image* selectedImage)
{
	this->selectedImage = selectedImage;
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

AbstractNotifier& Controller::getMessenger()
{
	return *messenger;
}
Images::Image* Controller::getSelectedImage()
{
	return selectedImage;
}

int Controller::getNumberOfLoadedImages()
{
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	return images.size();
}

void Controller::iterateImagesAsync(std::function<void(Images::Image*)> actionOnImage)
{
	std::lock_guard<std::mutex> lock(mutexImageFormats);
	for (const std::unique_ptr<Images::Image>& image : images)
		actionOnImage(image.get());
}

}

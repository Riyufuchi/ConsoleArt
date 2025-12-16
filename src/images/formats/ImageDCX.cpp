//==============================================================================
// File       : ImageDCX.cpp
// Author     : riyufuchi
// Created on : Nov 13, 2025
// Last edit  : Dec 16, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "ImageDCX.h"

namespace consoleartlib
{

ImageDCX::ImageDCX(const std::string& filename) : Image(filename, ImageType::DCX), selectedPage(0)
{
	image.multipage = true;
	image.planar = true;
	loadImage();
}

ImageDCX::ImageDCX(const std::string& filename, int numberOfPages) : Image(filename, ImageType::DCX), selectedPage(0), numOfPages(numberOfPages)
{
	pages.reserve(numberOfPages);
}

ImageDCX::~ImageDCX()
{
}

void ImageDCX::loadImage()
{
	std::ifstream stream(filepath, std::ios::in | std::ios::binary);
	if (!stream)
		return;
	// --- Read magic ---
	uint32_t magic = 0;
	stream.read(reinterpret_cast<char*>(&magic), 4);
	if (magic != 0x3ADE68B1) // DCX is little-endian
		return; // not a DCX file
	// --- Read offset table ---
	std::vector<uint32_t> offsets;
	uint32_t off = 0;
	while (true)
	{
		stream.read(reinterpret_cast<char*>(&off), 4);
		if (!stream)
			return; // malformed file
		if (off == 0)
			break; // terminator
		offsets.push_back(off);
	}

	if (offsets.empty())
		return; // DCX with no PCX pages

	// --- Calculate ranges ---
	ImageRange r;
	std::streampos current = stream.tellg(); // save current pos
	stream.seekg(0, std::ios::end);
	std::streampos fileSize = stream.tellg(); // get size
	stream.seekg(current);
	for (size_t i = 0; i < offsets.size(); ++i)
	{
		r.start = offsets[i];
		if (i + 1 < offsets.size())
			r.end = offsets[i + 1];
		else
			r.end = static_cast<uint32_t>(fileSize); // last page ends at EOF
		ranges.push_back(r);
	}

	// --- Load images ---
	numOfPages = ranges.size();
	ImagePCX::PagePCX page;
	for (const ImageRange& range : ranges)
	{
		stream.seekg(range.start);
		page.image = image;
		if (ImagePCX::readPCX(stream, page, range.start, range.end))
		{
			page.image.name = getFilename();
			pages.emplace_back(page);
		}
	}
	selectPage(0);
	technical.fileState = FileState::VALID_IMAGE_FILE;
}
Pixel ImageDCX::getPixel(int x, int y) const
{
	x = (y * headerPCX.bytesPerLine * headerPCX.numOfColorPlanes) + x;
	Pixel pixel;
	switch (headerPCX.numOfColorPlanes)
	{
		case 4:
			pixel.alpha = pixelData[x + 3 * image.width];
			/* no break */
		case 3:
			pixel.red = pixelData[x];
			pixel.green = pixelData[x + headerPCX.bytesPerLine];
			pixel.blue = pixelData[x + 2 * image.width];
		break;
	}
	return pixel;
}
void ImageDCX::setPixel(int x, int y, Pixel newPixel)
{
	x = y * 3 * image.width + x;
	switch (headerPCX.numOfColorPlanes)
	{
		case 4:
			pixelData[x + 3 * image.width] = newPixel.alpha;
			/* no break */
		case 3:
			pixelData[x] = newPixel.red;
			pixelData[x + image.width]= newPixel.green;
			pixelData[x + 2 * image.width] = newPixel.blue;
		break;
	}
}
bool ImageDCX::saveImage() const
{
	if (pages.empty())
		return false;
	std::ofstream out(filepath, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!out)
		return false;
	// 1. Write magic number (little endian)
	uint32_t magic = 0x3ADE68B1;
	out.write(reinterpret_cast<const char*>(&magic), 4);
	// 2. Reserve space for offset table (N offsets + a terminating zero)
	size_t count = pages.size();
	std::vector<std::streampos> offsetPositions; // where offsets are written
	offsetPositions.reserve(count);
	const uint32_t ZERO = 0;
	for (size_t i = 0; i < count + 1; ++i)
	{
		offsetPositions.push_back(out.tellp());  // remember where
		out.write(reinterpret_cast<const char*>(&ZERO), 4);
	}
	// 3. Write PCX pages & record offsets
	std::vector<uint32_t> realOffsets;
	realOffsets.reserve(count);
	std::streampos pos;
	for (size_t i = 0; i < count; ++i)
	{
		pos = out.tellp();    // current file position
		realOffsets.push_back(static_cast<uint32_t>(pos));
		// write PCX data at this position
		ImagePCX::savePCX(out, pages[i]);
	}
	// 4. Patch offsets in the table
	for (size_t i = 0; i < count; ++i)
	{
		out.seekp(offsetPositions[i], std::ios::beg);
		uint32_t v = realOffsets[i];
		out.write(reinterpret_cast<const char*>(&v), 4);
	}
	// 5. Write terminating offset = 0 (already placeholder, but we ensure it)
	out.seekp(offsetPositions[count], std::ios::beg);
	out.write(reinterpret_cast<const char*>(&ZERO), 4);
	return true;
}

void ImageDCX::addImage(ImagePCX::PagePCX image)
{
	pages.emplace_back(image);
}

size_t ImageDCX::getSelectedPageIndex() const
{
	return selectedPage;
}

void ImageDCX::selectPage(size_t index)
{
	if (index < pages.size())
	{
		selectedPage = index;
		pixelData = pages[index].pixelData;
		image = pages[index].image;
		headerPCX = pages[index].header;
	}
}

const ImagePCX::PagePCX& ImageDCX::getSelectedPage() const
{
	return pages[selectedPage];
}

size_t ImageDCX::getPageCount() const
{
	return pages.size();
}

} /* namespace consoleartlib */

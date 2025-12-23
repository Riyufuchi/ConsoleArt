//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_CONTROLLERCLI_H_
#define CONSOLEART_CONTROLLERCLI_H_

#include <chrono>
#include <thread>

#include "../../other/ScheduleTracker.h"
#include "../controller/Controller.h"
#include "../cli/AsciiPrinterCLI.h"
#include "../cli/MenuCLI.h"
#include "../cli/NotifierCLI.h"
// ConsoleLib
#include "consolelib/tools/color_tools.h"
#include "consolelib/tools/console_tools.h"
#include "consolelib/tools/data_tools.h"
#include "consolelib/consoles.hpp"
// ConsoleArtLib
#include "consoleartlib/image_tools/image_tools.h"
#include "consoleartlib/image_tools/filter.h"

namespace consoleart
{
class ControllerCLI : public Controller
{
protected:
	consolelib::IConsole* console;
	void loadAllImagesAsync();
	virtual void refreshMenu();
	virtual std::string inputImageName() override;
	virtual IndexDataType selectImageMenu() override;
	virtual void showAboutApplicationInfo() override;
private:
	consolelib::DefaultConsole defaultConsole;
	consolelib::Color warningColor{255, 255, 0};
	void imageActionsSubmenu();
	void benchmark(const std::vector<std::string>& vector);
	void compareImages(const std::vector<std::string>& vector);
	// Events
	void loadImageEvent();
	void selectImageEvent();
	void convertImageToAsciiEvent();
public:
	ControllerCLI(consolelib::IConsole* console);
	ControllerCLI(std::string path, consolelib::IConsole* console);
	void run() override;
	~ControllerCLI();
};
}
#endif /* CONSOLEART_CONTROLLERCLI_H_ */

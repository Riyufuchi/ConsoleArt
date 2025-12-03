//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Nov 17, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_CONTROLLERCLI_H_
#define CONSOLEART_CONTROLLERCLI_H_

#include <chrono>
#include <thread>

#include "ColorUtils.h"
#include "ConsoleUtils.h"
#include "UnixConsole.h"
#include "DefaultConsole.h"
#include "DataUtils.h"
#include "Library.h"

#include "../../other/ScheduleTracker.h"
#include "../controller/Controller.h"
#include "../cli/AsciiPrinterCLI.h"
#include "../cli/MenuCLI.h"
#include "../cli/NotifierCLI.h"
#include "../imageTools/ImageTools.h"
#include "../imageTools/Filter.h"

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

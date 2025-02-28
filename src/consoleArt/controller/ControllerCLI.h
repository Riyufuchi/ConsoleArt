//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Feb 27, 2025
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
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
#include "../network/client/ClientTools.h"
#include "../imageTools/ImageTools.h"
#include "../imageTools/Filter.h"


namespace ConsoleArt
{
class ControllerCLI : public Controller
{
protected:
	ConsoleLib::IConsole* console;
	void loadAllImagesAsync();
	virtual void refreshMenu();
	virtual std::string inputImageName() override;
	virtual Images::Image* selectImage() override;
	virtual void showAboutApplicationInfo() override;
private:
	ConsoleLib::DefaultConsole defaultConsole;
	ConsoleLib::Color warningColor{255, 255, 0};
	void runAsClient(std::string ip);
	void imageAction();
	void benchmark(const std::vector<std::string>& vector);
	void compareImages(const std::vector<std::string>& vector);
public:
	ControllerCLI(ConsoleLib::IConsole* console);
	ControllerCLI(std::string path, ConsoleLib::IConsole* console);
	void run() override;
	~ControllerCLI();
};
}
#endif /* CONSOLEART_CONTROLLERCLI_H_ */

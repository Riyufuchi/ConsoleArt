//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Jan 20, 2025
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

#include "../../other/BinomialDistribution.h"
#include "../../other/ScheduleTracker.h"
#include "MessengerCLI.h"
#include "../../other/OtherUtils.hpp"
#include "../controller/Controller.h"
#include "AsciiPrinter.h"
#include "MenusCLI.h"
#include "../tools/ClientTools.h"
#include "../../imageUtils/ImageToolsCLI.h"


namespace ConsoleArt
{
class ControllerCLI : public Controller
{
protected:
	ConsoleLib::IConsole* console;
	std::string inputImageName() override;
private:
	ConsoleLib::DefaultConsole defaultConsole;
	MenusCLI menuCLI;
	void convertImage(Images::Image* image) override;
	void refreshMenu() override;
	Images::Image* selectImage() override;
	void loadAllImagesAsync();
	void runAsClient(std::string ip);
public:
	ControllerCLI(ConsoleLib::IConsole* console);
	ControllerCLI(std::string path, ConsoleLib::IConsole* console);
	void configure(std::map<std::string, std::vector<std::string>>& config) override;
	void run() override;
	~ControllerCLI();
};
}
#endif /* CONSOLEART_CONTROLLERCLI_H_ */

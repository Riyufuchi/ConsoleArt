//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Oct 25, 2024
// Copyright  : Copyright (c) Riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_CONTROLLERCLI_H_
#define CONSOLEART_CONTROLLERCLI_H_

#include <chrono>
#include <thread>

#include "Controller.h"
#include "../cli/AsciiPrinter.h"
#include "../cli/MenusCLI.h"
#include "../tools/ClientTools.h"
#include "../../imageUtils/ImageToolsCLI.h"
#include "ColorUtils.h"
#include "ConsoleUtils.h"
#include "UnixConsole.h"
#include "DefaultConsole.h"
#include "DataUtils.h"
#include "Library.h"

#include "../../other/BinomialDistribution.h"
#include "../../other/ScheduleTracker.h"
#include "../cli/MessengerCLI.h"
#include "../../other/OtherUtils.hpp"


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
public:
	ControllerCLI(ConsoleLib::IConsole* console);
	ControllerCLI(std::string path, ConsoleLib::IConsole* console);
	void configure(int argc, char** argv) override;
	void run() override;
	ConsoleLib::IConsole* getConsole()
	{
		return console;
	}
	~ControllerCLI();
};
}
#endif /* CONSOLEART_CONTROLLERCLI_H_ */

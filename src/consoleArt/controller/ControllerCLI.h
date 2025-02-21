//==============================================================================
// File       : ControllerCLI.h
// Author     : riyufuchi
// Created on : Dec 18, 2023
// Last edit  : Feb 18, 2025
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

#include "../../math/distributions/BinomialDistribution.h"
#include "../../other/ScheduleTracker.h"
#include "../cli/MessengerCLI.h"
#include "../../other/OtherUtils.hpp"
#include "../../math/MathUtils.hpp"
#include "../controller/Controller.h"
#include "../asciiTools/AsciiPrinter.h"
#include "../cli/MenusCLI.h"
#include "../network/client/ClientTools.h"
#include "../imageTools/ImageTools.h"
#include "../imageTools/Filter.h"


namespace ConsoleArt
{
class ControllerCLI : public Controller
{
protected:
	ConsoleLib::IConsole* console;
	std::string inputImageName() override;
	void convertImage(Images::Image* image) override;
private:
	ConsoleLib::DefaultConsole defaultConsole;
	ConsoleLib::Color warningColor{255, 255, 0};
	MenusCLI menuCLI;
	void refreshMenu() override;
	Images::Image* selectImage() override;
	void loadAllImagesAsync();
	void runAsClient(std::string ip);
	void imageAction();
public:
	ControllerCLI(ConsoleLib::IConsole* console);
	ControllerCLI(std::string path, ConsoleLib::IConsole* console);
	void configure(std::map<std::string, std::vector<std::string>>& config) override;
	void run() override;
	~ControllerCLI();
};
}
#endif /* CONSOLEART_CONTROLLERCLI_H_ */

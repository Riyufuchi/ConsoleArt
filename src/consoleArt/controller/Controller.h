//============================================================================
// Name        : Controller
// Author      : Riyufuchi
// Created on  : Nov 15, 2022
// Last Edit   : Feb 25, 2025
// Description : This class is controller for a main app functionality
//============================================================================

#ifndef _Controller_H_
#define _Controller_H_

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <mutex>
#include <unordered_map>

#include "../../images/Formats.hpp"
#include "../asciiTools/AsciiConverter.h"
#include "../interfaces/IMenu.hpp"
#include "../tools/GeneralTools.hpp"
#include "../abstract/AbstractNotifier.h"
#include "../interfaces/IMenu.hpp"
#include "../abstract/AbstractAsciiPrinter.h"
#include "StateController.h"

namespace ConsoleArt
{
class Controller
{
protected:
	StateController stateController;
	bool isRunnable;
	AbstractNotifier* messenger;
	IMenu* menuInterface;
	AbstractAsciiPrinter* abstractAsciiPrinter;
	Images::Image* selectedImage;
	// Virtual
	void convertImage(Images::Image* image);
public:
	Controller(AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	Controller(std::string path, AbstractNotifier* notifier, IMenu* menu, AbstractAsciiPrinter* asciiPrinter);
	virtual ~Controller();
	virtual void configure(std::map<std::string, std::vector<std::string>>& config) = 0;
	virtual void run() = 0;
	// Setters
	AbstractNotifier& getMessenger()
	{
		return *messenger;
	}
};
}
#endif

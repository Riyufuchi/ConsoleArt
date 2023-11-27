//============================================================================
// Name        : UnixControllerCLI.h
// Author      : Riyufuchi
// Created on  : 22.11.2023
// Last Edit   : 22.11.2023
// Description : This class is Unix CLI controller for the main app
//============================================================================

#ifndef _UnixControllerCLI_H_
#define _UnixControllerCLI_H_

#include "Controller.h"
#include "AsciiPrinter.h"

namespace ConsoleArt
{
class UnixControllerCLI : public Controller
{
private:
	ConsoleUtils::UnixConsole unixConsole;
	void convertImage(Images::Image* image) override;
	void confConsoleColor() override;
	void loadAllImages() override;
	std::string inputImageName() override;
	Images::Image* selectImage() override;
	Images::Image* loadImage(std::string path) override;
public:
	UnixControllerCLI();
	UnixControllerCLI(std::string path);
	void run() override;
	ConsoleUtils::UnixConsole& getUnixConslole()
	{
		return unixConsole;
	}
	~UnixControllerCLI();
};
}
#endif

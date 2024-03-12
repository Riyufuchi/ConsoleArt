//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : 13.07.2020
// Last Edit   : Mar 8, 2024
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>

#include "consoleArt/tools/ConsoleArtTools.hpp"
#include "consoleArt/controller/ControllerCLI.h"
#include "inc/ConsoleUtils.h"
#include "inc/UnixConsole.h"
#include "inc/IConsole.hpp"
#include "inc/DefaultConsole.h"
#include "inc/Server.h"
#include "inc/Client.h"
#ifdef _WIN32
	#include "inc/WindowsConsole.h"
#endif // _WIN32


enum BootAction
{
	ABORT,
	DISPLAY_MANUAL,
	CONFIGURE,
	CONTINUE,
	TEST,
	SERVER,
	CLIENT_OK,
	CLIENT_ERR
};

BootAction checkArgs(int argc, char** argv, int reqArgNum, ConsoleUtility::IConsole& console);

int main(int argc, char** argv)
{
	ConsoleUtility::Color color = ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::APERTURE_ORANGE);
	#if defined(__linux__) || defined(__APPLE__)
		ConsoleUtility::UnixConsole systemConsole;
	#elif defined(_WIN32)
		ConsoleUtility::WindowsConsole systemConsole;
		systemConsole.out(ConsoleUtility::ColorUtils::getColor(ConsoleUtility::ColorPallete::UNIQUE),
			"Disclaimer: Windows in not a primarily targeted platform.\nThis build is experimental and some features might not be available or work correctly.\n");
	#else
		ConsoleUtility::DefaultConsole systemConsole;
	#endif
	systemConsole.setDefaultTextColor(color);
	ConsoleUtility::ConsoleUtils::header("\n    ConsoleArt V2.2\n   ", systemConsole, color);
	ConsoleArt::ControllerCLI consoleArt(&systemConsole);
	switch(checkArgs(argc, argv, 2, *consoleArt.getConsole()))
	{
		case ABORT: return 1;
		case CONTINUE: goto start;
		case CONFIGURE: goto conf;
		case TEST: return 0;
		case DISPLAY_MANUAL: return 0;
		case SERVER: goto finish;
		case CLIENT_OK: goto finish;
		case CLIENT_ERR: goto start;
	}
	conf: consoleArt.configure(argc, argv);
	start: consoleArt.run();
	finish: return 0;
}

BootAction checkArgs(int argc, char** argv, int reqArgNum, ConsoleUtility::IConsole& console)
{
	if(argc == 1) // First argument is always app name
		return BootAction::CONTINUE;
	else if(!strcmp(argv[1], "--man") || !strcmp(argv[1], "--help"))
	{
		ConsoleArt::ConsoleArtTools::createManual();
		return BootAction::DISPLAY_MANUAL;
	}
	else if(!strcmp(argv[1], "--colorTest"))
	{
		ConsoleArt::ConsoleArtTools::colorTest(console);
		return BootAction::TEST;
	}
	else if(!strcmp(argv[1], "--runServer"))
	{
		std::string msg = "ConsoleArt server v0.4\n";
		console.out(msg);
		SufuServer::Server server;
		if (!server.isRunning())
		{
			console.err(server.getServerStatus());
			std::cin.get();
			return BootAction::SERVER;
		}
		console.out(server.getServerStatus());
		console.out(" -> Server is up and running\n");
		console.out("On port: ");
		std::cout << server.getPort() << "\n";
		server.runServer(msg);
		console.out(server.getServerStatus());
		std::cin.get();
		return BootAction::SERVER;
	}
	else if(!strcmp(argv[1], "--runClient"))
	{
		console.out("ConsoleArt client v0.3\n");
		std::string msg = "Test request";
		SufuServer::Client client("127.0.0.1", 12345);
		if (!client.isConnected())
		{
			console.err(client.getClientStatus());
			console.out("Can't connect to ConsoleArt server.\nStarted in off-line mode.\n\n");
			return BootAction::CLIENT_ERR;
		}
		client.sendRequest(msg);
		if (client.listenForResponse(msg))
			console.out(msg + "\n");
		else
			console.err(msg);
		msg = "logout";
		client.sendRequest(msg);
		if (!client.listenForResponse(msg))
			console.out(msg + "\n");
		else
			console.err(msg);
		return BootAction::CLIENT_OK;
	}
	else if(argc < reqArgNum) //If argc is less than minimum then arguments are invalid
	{
		ConsoleArt::ConsoleArtTools::printArgError(argv[1], console);
		return BootAction::ABORT;
	}
	else
		return BootAction::CONFIGURE;
}

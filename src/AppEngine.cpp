#include "AppEngine.h"

void AppEngine::start() {
	bool appStarted = true;
	ConsoleHandler consoleHelp;
	Hotel newHotel;
	std::cout << "Welcome to Hotel FMI. Enjoy your stay." << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "If you want to get started, just type help for list of functions and how to work with them." << std::endl;

	while (appStarted) {
		try {
			String commandName = consoleHelp.readCommand(newHotel);
			if (commandName == "exit")
			{
				std::cout << "Exiting program..." << std::endl;
				appStarted = false;
			}
		}
		catch (const String& error) {
			std::cout << error << std::endl;
		}
	}
}
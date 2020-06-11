#include "ConsoleHandler.h"

void ConsoleHandler::listHelperFunctions()
{
	std::cout << "The following commands are supported: " << std::endl;
	std::cout << "open <file>   opens file" << std::endl;
	std::cout << "close         closes currently opened file" << std::endl;
	std::cout << "save          saves the currently opened file" << std::endl;
	std::cout << "saveas <file> saves the currently opened file in <file>" << std::endl;
	std::cout << "help          prints this information" << std::endl;
	std::cout << "exit          exits the program" << std::endl;
}

String ConsoleHandler::readCommand(Hotel& currentHotel)
{
	Command currentCommand;
	std::cin >> currentCommand;
	return initializeCommand(currentHotel, currentCommand);
}

String ConsoleHandler::initializeCommand(Hotel& currentHotel, const Command& command)
{
	if (command.getName() == "open") {
		if (hotelHandle.isFileOpen())
			throw String("Currently there is a file open");
		if (command.size() != 1)
			throw String("Invalid arguments.");
		hotelHandle.loadFile(currentHotel, command.getParameter(0));
		std::cout << "Successfully read file." << std::endl;
	}
	else if (command.getName() == "close") {
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no file open.");
		if (command.size() > 0)
			throw String("This command doesn't need arguments");
		if (hotelHandle.hasRooms(currentHotel))
		{
			currentHotel.removeData();
		}
		hotelHandle.closeFile();
		std::cout << "Successfully closed the file." << std::endl;
	}
	else if (command.getName() == "save") {
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no open file.");
		if (command.size() > 0)
			throw String("This command doesn't need arguments");
		if (hotelHandle.hasRooms(currentHotel))
			hotelHandle.saveFile(currentHotel);
		std::cout << "Successfully saved current shapes." << std::endl;
	}
	else if (command.getName() == "saveas") {
		if (command.size() != 1)
			throw String("Invalid arguments.");
		if (!hotelHandle.isFileOpen())
			throw String("There are currently no shapes to save.");
		hotelHandle.saveFileAs(currentHotel, command.getParameter(0));
		std::cout << "Successfully saved current hotel into file: " << command.getParameter(0) << std::endl;
	}
	else if (command.getName() == "help") {
		if (command.size() > 0)
			throw String("This command doesn't need arguments.");
		listHelperFunctions();
		std::cout << std::endl;
		currentHotel.listHelperFunctions();
		std::cout << std::endl;
	}
	else if (command.getName() == "checkin")
	{
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no open file");
		hotelHandle.checkIn(currentHotel, command.getParameters());
	}
	else if (command.getName() == "checkout") {
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no open file");
		hotelHandle.checkOut(currentHotel, command.getParameters());
	}
	else if (command.getName() == "availability") {
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no open file");
		hotelHandle.availabilityRooms(currentHotel, command.getParameters());
	}
	else if (command.getName() == "report") {
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no open file");
		hotelHandle.reportRooms(currentHotel, command.getParameters());
	}
	else if (command.getName() == "find") {
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no open file");
		hotelHandle.findRoom(currentHotel, command.getParameters());
	}
	else if (command.getName() == "find!") {
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no open file");
		hotelHandle.findEmergentRoom(currentHotel, command.getParameters());
	}
	else if (command.getName() == "unavailable") {
		if (!hotelHandle.isFileOpen())
			throw String("Currently there is no open file");
		hotelHandle.makeRoomUnavailable(currentHotel, command.getParameters());
	}
	else if (command.getName() == "exit") {
		if (command.size() > 0)
			throw String("This command doesn't need arguments.");
	}
	else {
		throw String("Unsupported command.");
	}
	return command.getName();
}

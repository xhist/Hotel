#pragma once
#include "HotelHandler.h"
#include "Command.h"

class ConsoleHandler
{
	//Handlers
	HotelHandler hotelHandle;
public:
	void listHelperFunctions();
	String readCommand(Hotel& currentHotel);
	String initializeCommand(Hotel& currentHotel, const Command& currentCommand);
};


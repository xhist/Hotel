#include "HotelHandler.h"

String HotelHandler::getFileName(const String& path) {
	int pathSize = path.size();
	int rightSlashIndex = path.lastIndexOf('/');
	int leftSlashIndex = path.lastIndexOf('\\');
	int splitSlashIndex = -1;
	if (rightSlashIndex > -1)
		splitSlashIndex = rightSlashIndex + 1;
	else if (leftSlashIndex > -1)
		splitSlashIndex = leftSlashIndex + 1;
	else
		splitSlashIndex = 0;
	int strSize = pathSize - splitSlashIndex;
	if (!strSize)
		return String();
	String newString(pathSize - splitSlashIndex);
	int currentSize = 0;
	for (int i = splitSlashIndex; i < pathSize; i++)
		newString[currentSize++] = path[i];
	return newString;
}

bool HotelHandler::isFilenameValid(const String& path, const String& extension) {
	int indexExtension = path.lastIndexOf('.') + 1;
	int pathSize = path.size();
	if (indexExtension == -1)
		return false;
	int strSize = pathSize - indexExtension;
	if (strSize != extension.size())
		return false;
	String newString(strSize);
	int currentSize = 0;
	for (int i = indexExtension; i < pathSize; i++)
		newString[currentSize++] = path[i];
	return newString == extension;
}

bool HotelHandler::isLetterInt(char c) const
{
	return (c >= '0' && c <= '9');
}

bool HotelHandler::isStringInt(const String& currentStr) const
{
	int size = currentStr.size();
	int start = 0;
	int dashIndex = currentStr.has('-');
	if (dashIndex > -1 && dashIndex != 0)
		return false;
	if (dashIndex > -1) start++;
	for (int i = start; i < size; i++)
	{
		if (!isLetterInt(currentStr[i]))
			return false;
	}

	return true;
}

String HotelHandler::mergeVectorWords(unsigned start, unsigned end, const Vector<String>& currentVector) const
{
	String currentStr;
	for (int i = start; i < end; i++) 
	{
		if (i != end - 1)
			currentStr += ' ';
		currentStr += currentVector[i];
	}

	return currentStr;
}

void HotelHandler::loadFile(Hotel& currentHotel, const String& path)
{
	try {
		if (currentOpenFile)
			throw String("Currently a file is open.");
		isPathValid(path, "txt");
		currentOpenFile = path;
		std::ifstream currentHotelFile(path.toCharArray());
		currentHotel.loadData(currentHotelFile);
		currentHotelFile.close();
	}
	catch (const String& error) {
		throw error;
	}
}

void HotelHandler::saveFile(Hotel& currentHotel)
{
	try {
		if (!currentOpenFile)
			throw String("Currently there is no open file to save into.");
		std::ofstream currentFile(currentOpenFile.toCharArray(), std::ios::trunc);
		currentHotel.saveData(currentFile);
		currentFile.close();
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

void HotelHandler::saveFileAs(Hotel& currentHotel, const String& path)
{
	try {
		isPathValid(path, "txt");
		std::ofstream currentFile(path.toCharArray(), std::ios::trunc);
		currentHotel.saveData(currentFile);
		currentFile.close();
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

bool HotelHandler::isPathValid(const String& path, const String& extension) {
	std::ifstream hotelFile(path.toCharArray());
	String fileName = getFileName(path);
	if (!hotelFile.is_open())
	{
		hotelFile.close();
		if (isFilenameValid(fileName, extension))
		{
			std::fstream createFile(path.toCharArray(), std::ios::out);
			createFile.close();
			hotelFile.open(path.toCharArray());
			if (!hotelFile.is_open())
				throw String("The file is invalid.");
			hotelFile.close();
		}
	}
	if (hotelFile.is_open())
		hotelFile.close();

	if (!isFilenameValid(fileName, extension))
		throw String("The filename is invalid.");

	return true;
}

void HotelHandler::checkIn(Hotel& currentHotel, const Vector<String>& parameters)
{
	if (parameters.size() < 4)
		throw String("Invalid arguments.");
	if (!isStringInt(parameters[0]))
		throw String("The room number is not correct.");
	unsigned roomNumber = parameters[0].strToInt();
	if (roomNumber == 0)
		throw String("The room number is not correct.");
	Date startDate = parameters[1];
	Date endDate = parameters[2];
	unsigned guests = 0;
	String note;
	if (parameters.size() > 4 && isStringInt(parameters[parameters.size() - 1]) && parameters[parameters.size() - 1].strToInt() > 0)
	{
		note = mergeVectorWords(3, parameters.size() - 1, parameters);
		guests = parameters[parameters.size() - 1].strToInt();
	}
	else {
		note = mergeVectorWords(3, parameters.size(), parameters);
	}

	currentHotel.checkin(roomNumber, startDate, endDate, note, guests);
}

void HotelHandler::checkOut(Hotel& currentHotel, const Vector<String>& parameters)
{
	if (parameters.size() != 1)
		throw String("Invalid arguments");
	if (!isStringInt(parameters[0]))
		throw String("The room number is not correct.");
	unsigned roomNumber = parameters[0].strToInt();
	if (roomNumber == 0)
		throw String("The room number is not correct.");
	currentHotel.checkout(roomNumber);
}

void HotelHandler::reportRooms(const Hotel& currentHotel, const Vector<String>& parameters) const
{
	if (parameters.size() != 2)
		throw String("Invalid arguments.");
	Date startDate = parameters[0];
	Date endDate = parameters[1];
	currentHotel.report(startDate, endDate);
}

void HotelHandler::availabilityRooms(const Hotel& currentHotel, const Vector<String>& parameters) const
{
	if (parameters.size() > 1)
		throw String("Invalid arguments.");
	Date currentDate;
	if(parameters.size() > 0)
		currentDate = parameters[0];
	else
	{
		std::time_t t = std::time(0);
		std::tm* currentTime = std::localtime(&t);
		currentDate = Date(currentTime->tm_year + 1900, currentTime->tm_mday + 1, currentTime->tm_mday);
	}
	currentHotel.availability(currentDate);
}

void HotelHandler::findRoom(const Hotel& currentHotel, const Vector<String>& parameters) const
{
	if (parameters.size() != 3)
		throw String("Invalid arguments.");
	if (!isStringInt(parameters[0]))
		throw String("The number of beds is not correct.");
	unsigned beds = parameters[0].strToInt();
	if (beds == 0)
		throw String("The number of beds is not correct.");
	Date startDate = parameters[1];
	Date endDate = parameters[2];
	currentHotel.find(beds, startDate, endDate);
}

void HotelHandler::findEmergentRoom(Hotel& currentHotel, const Vector<String>& parameters)
{
	if (parameters.size() != 3)
		throw String("Invalid arguments.");
	if (!isStringInt(parameters[0]))
		throw String("The number of beds is not correct.");
	unsigned beds = parameters[0].strToInt();
	if (beds == 0)
		throw String("The number of beds is not correct.");
	Date startDate = parameters[1];
	Date endDate = parameters[2];
	currentHotel.findEmergent(beds, startDate, endDate);
}

void HotelHandler::makeRoomUnavailable(Hotel& currentHotel, const Vector<String>& parameters)
{
	if (parameters.size() < 4)
		throw String("Invalid arguments.");
	if (!isStringInt(parameters[0]))
		throw String("The room number is not correct.");
	unsigned roomNumber = parameters[0].strToInt();
	if (roomNumber == 0)
		throw String("The room number is not correct.");
	Date startDate = parameters[1];
	Date endDate = parameters[2];
	String note = mergeVectorWords(3, parameters.size(), parameters);
	currentHotel.unavailable(roomNumber, startDate, endDate, note);
}

void HotelHandler::closeFile()
{
	currentOpenFile = "";
}

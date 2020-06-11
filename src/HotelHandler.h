#pragma once
#include "Hotel.h"
#include <ctime>

class HotelHandler
{
	String currentOpenFile;
private:
	bool isPathValid(const String& path, const String& extension);
	String getFileName(const String& path);
	bool isFilenameValid(const String& filename, const String& extension = "txt");
	bool isLetterInt(char c) const;
	bool isStringInt(const String& text) const;
	String mergeVectorWords(unsigned start, unsigned end, const Vector<String>& currentVector) const;
public:
	void loadFile(Hotel& currentHotel, const String& path);
	void saveFile(Hotel& currentHotel);
	void saveFileAs(Hotel& currentHotel, const String& path);
	void checkIn(Hotel& currentHotel, const Vector<String>& parameters);
	void checkOut(Hotel& currentHotel, const Vector<String>& parameters);
	void reportRooms(const Hotel& currentHotel, const Vector<String>& parameters) const;
	void availabilityRooms(const Hotel& currentHotel, const Vector<String>& parameters) const;
	void findRoom(const Hotel& currentHotel, const Vector<String>& parameters) const;
	void findEmergentRoom(Hotel& currentHotel, const Vector<String>& parameters);
	void makeRoomUnavailable(Hotel& currentHotel, const Vector<String>& parameters);
	void closeFile();
public:
	bool hasRooms(const Hotel& currentHotel) const { return currentHotel.roomsNum() > 0; }
	bool isFileOpen() const { return currentOpenFile; }
};
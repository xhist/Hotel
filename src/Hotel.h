#pragma once
#include "Room.h"
#include <fstream>

class Hotel
{
	Vector<Room> rooms;
private:
	bool isLetterInt(char c);
	bool isStringInt(const String& currentStr);
private:
	int findSuitableFreeRoomNumber(unsigned beds, const Date& start, const Date& end, const Vector<Room>& freeRooms) const;
	int findRoomForSpecialGuests(unsigned beds, const Date& start, const Date& end) const;
	int findRoomForNormalGuests(unsigned beds, const Date& start, const Date& end) const;
public:

	void listHelperFunctions() const;
	Vector<Room> getFreeRooms(const Date& start, const Date& end) const;
	Room getRoom(unsigned index) const;
	int roomExists(unsigned roomNumber) const;
	Room getRoomByNumber(unsigned roomNumber) const;
	Room operator[](unsigned index) const;
	unsigned roomsNum() const;

	void loadData(std::ifstream& currentFile);
	void saveData(std::ofstream& currentFile);
	void removeData();
	
	void checkin(unsigned roomNumber, const Date& start, const Date& end, const String& note, unsigned guests);
	void checkout(unsigned roomNumber);
	void availability(const Date& date) const;
	void report(const Date& start, const Date& end) const;
	void find(unsigned beds, const Date& start, const Date& end) const;
	void findEmergent(unsigned beds, const Date& start, const Date& end);
	void unavailable(unsigned roomNumber, const Date& start, const Date& end, const String& note);
};


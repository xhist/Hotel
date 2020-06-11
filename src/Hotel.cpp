#include "Hotel.h"

bool Hotel::isLetterInt(char c) {
	return (c >= '0' && c <= '9');
}

bool Hotel::isStringInt(const String& currentStr) {
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

int Hotel::findSuitableFreeRoomNumber(unsigned beds, const Date& start, const Date& end, const Vector<Room>& freeRooms) const
{
	int sizeFreeRooms = freeRooms.size();
	int minFreeRoomBeds = 0;
	int minFreeRoomBedsSet = false;
	int posFreeRoomNumber = -1;
	for (int j = 0; j < sizeFreeRooms; j++)
	{
		if (freeRooms[j].getBeds() >= beds)
		{
			if (!minFreeRoomBedsSet)
			{
				minFreeRoomBeds = freeRooms[j].getBeds();
				minFreeRoomBedsSet = true;
				posFreeRoomNumber = freeRooms[j].getNumber();
			}
			if (freeRooms[j].getBeds() < minFreeRoomBeds)
			{
				minFreeRoomBeds = freeRooms[j].getBeds();
				posFreeRoomNumber = freeRooms[j].getNumber();
			}
			if (minFreeRoomBeds == beds)
				break;
		}
	}

	return posFreeRoomNumber;
}

int Hotel::findRoomForSpecialGuests(unsigned beds, const Date& start, const Date& end) const
{
	int minBeds = 0;
	bool minBedsAreSet = false;
	int pos = -1;
	int numRooms = roomsNum();
	for (int i = 0; i < numRooms; i++) {
		if (rooms[i].getBeds() >= beds)
		{
			if (!minBedsAreSet)
			{
				minBeds = rooms[i].getBeds();
				pos = i;
				minBedsAreSet = true;
			}
			if (rooms[i].getBeds() < minBeds)
			{
				minBeds = rooms[i].getBeds();
				pos = i;
			}
			if (minBeds == beds)
				break;
		}
	}
	return pos;
}

int Hotel::findRoomForNormalGuests(unsigned beds, const Date& start, const Date& end) const {
	int minBeds = 0;
	bool minBedsAreSet = false;
	int pos = -1;
	int numRooms = roomsNum();
	for (int i = 0; i < numRooms; i++) {
		if (rooms[i].getBeds() >= beds && rooms[i].availableForCurrentReservation(start, end))
		{
			if (!minBedsAreSet)
			{
				minBeds = rooms[i].getBeds();
				pos = i;
				minBedsAreSet = true;
			}
			if (rooms[i].getBeds() < minBeds)
			{
				minBeds = rooms[i].getBeds();
				pos = i;
			}
			if (minBeds == beds)
				break;
		}
	}
	return pos;
}

void Hotel::listHelperFunctions() const
{
	std::cout << "The following commands are supported for working with the hotel:" << std::endl;
	std::cout << "checkin <room> <from> <to> <note> [<guests>] - checks the guests in room <room> for period <from> to <to> | [<guests>] - optional." << std::endl;
	std::cout << "checkout <room> - checks out the guests from room <room>" << std::endl;
	std::cout << "availability [<date>] - checks which rooms are available for future registration for date <date> | [<date>] - optional." << std::endl;
	std::cout << "report <from> <to> - shows all the rooms with the number of days they were used for period <from> to <to>" << std::endl;
	std::cout << "find <beds> <from> <to> - finds a suitable room for guests with at least <beds> beds for period <from> to <to>" << std::endl;
	std::cout << "find! <beds> <from> <to> finds a suitable room for special guests with at least <beds> beds for period <from> to <to>" << std::endl;
	std::cout << "unavailable <room> <from> <to> <note> - makes room <room> unavailable for period <from> to <to>" << std::endl;
}

Vector<Room> Hotel::getFreeRooms(const Date& start, const Date& end) const {
	int numRooms = roomsNum();
	Vector<Room> freeRooms;
	for (int i = 0; i < numRooms; i++)
	{
		if (rooms[i].availableForCurrentReservation(start, end))
			freeRooms.push_back(rooms[i]);
	}

	return freeRooms;
}

Room Hotel::getRoom(unsigned index) const {
	if (!(index >= 0 && index < rooms.size()))
		throw String("The room with this index doesn't exist.");
	return rooms[index];
}

int Hotel::roomExists(unsigned roomNumber) const
{
	int numRooms = roomsNum();
	for (int i = 0; i < numRooms; i++)
		if (rooms[i].getNumber() == roomNumber)
			return i;
	return -1;
}

Room Hotel::getRoomByNumber(unsigned roomNumber) const {
	int numRooms = roomsNum();
	for (int i = 0; i < numRooms; i++)
		if (rooms[i].getNumber() == roomNumber)
			return rooms[i];
	return Room();
}

Room Hotel::operator[](unsigned index) const {
	return getRoom(index);
}

unsigned Hotel::roomsNum() const { return rooms.size(); }

void Hotel::loadData(std::ifstream& currentFile)
{
	try {
		String numberOfRooms;
		currentFile >> numberOfRooms;
		if (!isStringInt(numberOfRooms))
			throw String("The number of rooms is not correct.");
		int numRooms = numberOfRooms.strToInt();
		for (int i = 0; i < numRooms; i++)
		{
			Room currentRoom;
			currentFile >> currentRoom;
			rooms.push_back(currentRoom);
		}
	}
	catch (const String& error) {
		removeData();
		throw error;
	}
}

void Hotel::saveData(std::ofstream& currentFile)
{
	int numRooms = roomsNum();
	currentFile << numRooms << std::endl;
	for (int i = 0; i < numRooms; i++)
		currentFile << rooms[i];
}

void Hotel::removeData() {
	rooms.removeAll();
}

void Hotel::checkin(unsigned roomNumber, const Date& start, const Date& end, const String& note, unsigned guests)
{
	int numRooms = roomsNum();
	for (int i = 0; i < numRooms; i++)
	{
		if (rooms[i].getNumber() == roomNumber)
		{
			if (guests == 0)
				guests = rooms[i].getBeds();
			rooms[i].checkIn(start, end, note, guests);
			std::cout << "The checkin was successful." << std::endl;
			return;
		}
	}
	std::cout << "There is no room with this number." << std::endl;
}

void Hotel::checkout(unsigned roomNumber)
{
	int numRooms = roomsNum();
	for (int i = 0; i < numRooms; i++)
	{
		if (rooms[i].getNumber() == roomNumber)
		{
			if (rooms[i].checkOut() == false)
				throw String("There was a problem with the checkout.");
			std::cout << "The checkout was successful." << std::endl;
			return;
		}
	}

	throw String("There is no room with this number.");
}

void Hotel::availability(const Date& date) const
{
	int numRooms = roomsNum();
	Vector<int> roomsIndex;
	for (int i = 0; i < numRooms; i++) {
		if (rooms[i].availableForFutureReservation(date))
			roomsIndex.push_back(i);
	}

	if (roomsIndex.size() > 0)
	{
		int size = roomsIndex.size();
		std::cout << "Rooms ";
		for (int j = 0; j < size; j++)
		{
			std::cout << rooms[roomsIndex[j]].getNumber();
			if (j != size - 1)
				std::cout << ", ";
		}
		std::cout << " are available on this date." << std::endl;
	}
	else
		std::cout << "There are no available rooms on this date." << std::endl;
}

void Hotel::report(const Date& start, const Date& end) const
{
	int numRooms = roomsNum();
	int countRooms = 0;
	for (int i = 0; i < numRooms; i++)
	{
		int days = rooms[i].getDaysUsed(start, end);
		if (days > 0)
		{
			std::cout << "Room " << rooms[i].getNumber() << " has been used for " << days << " days." << std::endl;
			countRooms++;
		}
	}
	if (!countRooms)
		std::cout << "No room was used in this period of time." << std::endl;
}

void Hotel::find(unsigned beds, const Date& start, const Date& end) const
{
	int suitableRoomIndex = findRoomForNormalGuests(beds, start, end);

	if (suitableRoomIndex == -1)
		throw String("There was no suitable room found.");
	
	std::cout << "Room " << rooms[suitableRoomIndex].getNumber() << " was found." << std::endl;
}

void Hotel::findEmergent(unsigned beds, const Date& start, const Date& end)
{
	int suitableFreeRoomIndex = findRoomForNormalGuests(beds, start, end);

	if (suitableFreeRoomIndex > -1)
	{
		std::cout << "Room " << rooms[suitableFreeRoomIndex].getNumber() << " is free for registration." << std::endl;
		return;
	}

	Vector<Room> freeRooms = getFreeRooms(start, end);
	int sizeFreeRooms = freeRooms.size();
	if (sizeFreeRooms == 0)
		throw String("Sorry, there is no free room.");
	
	int sizeRooms = roomsNum();
	for (int i = 0; i < sizeRooms; i++)
	{
		if (rooms[i].getBeds() >= beds) 
		{
			Room currentRoomOneMove = rooms[i];
			int activeReservationRoomOneMoveIndex = rooms[i].reservationsNum() - 1;
			Reservation activeReservationRoomOneMove = rooms[i].getReservation(activeReservationRoomOneMoveIndex);
			int freeRoomNumber = findSuitableFreeRoomNumber(currentRoomOneMove.getGuests(), activeReservationRoomOneMove.getStartDate(),
				activeReservationRoomOneMove.getEndDate(), freeRooms);
			int posFreeRoom = roomExists(freeRoomNumber);

			if (posFreeRoom > -1)
			{
				rooms[posFreeRoom].checkIn(activeReservationRoomOneMove.getStartDate(), activeReservationRoomOneMove.getEndDate(),
					activeReservationRoomOneMove.getNote(), rooms[i].getGuests());

				rooms[i].removeActiveReservation();
				std::cout << "Room " << rooms[i].getNumber() << " is free for registration." << std::endl;
				return;
			}
		}
	}

	int suitableRoomIndex = findRoomForSpecialGuests(beds, start, end);

	if (suitableRoomIndex == -1)
		throw String("Sorry, there is no suitable room.");
	
	Room currentRoom = rooms[suitableRoomIndex];
	int activeReservationIndex = currentRoom.reservationsNum() - 1;
	Reservation activeReservation = currentRoom.getReservation(activeReservationIndex);

	int freeRoomNumber = findSuitableFreeRoomNumber(currentRoom.getGuests(), activeReservation.getStartDate(),
		activeReservation.getEndDate(), freeRooms);
	int posFreeRoom = roomExists(freeRoomNumber);

	if (posFreeRoom > -1)
	{
		rooms[posFreeRoom].checkIn(activeReservation.getStartDate(), activeReservation.getEndDate(), 
			activeReservation.getNote(), rooms[suitableRoomIndex].getGuests());

		rooms[suitableRoomIndex].removeActiveReservation();
		std::cout << "Room " << rooms[suitableRoomIndex].getNumber() << " is free for registration." << std::endl;
		return;
	}

	int numRooms = roomsNum();
	int minRoomToMove = 0;
	bool minRoomToMoveSet = false;
	int posRoomToMoveTo = -1;
	for (int i = 0; i < numRooms; i++)
	{
		if (rooms[i].getBeds() >= currentRoom.getGuests() && i != suitableRoomIndex)
		{
			Room currentRoomToMove = rooms[i];
			int activeReservationRoomToMoveIndex = rooms[i].reservationsNum() - 1;
			Reservation activeReservationRoomToMove = rooms[i].getReservation(activeReservationRoomToMoveIndex);
			int roomToMoveSuitableFreeRoomNumber = findSuitableFreeRoomNumber(currentRoomToMove.getGuests(), activeReservationRoomToMove.getStartDate(),
				activeReservationRoomToMove.getEndDate(), freeRooms);
			int posRoomToMoveSuitableFreeRoomIndex = roomExists(roomToMoveSuitableFreeRoomNumber);
			if (posRoomToMoveSuitableFreeRoomIndex > -1)
			{
				posRoomToMoveTo = i;
				rooms[posRoomToMoveSuitableFreeRoomIndex].checkIn(activeReservationRoomToMove.getStartDate(),
					activeReservationRoomToMove.getEndDate(), activeReservationRoomToMove.getNote(), currentRoomToMove.getGuests());
				rooms[i].removeActiveReservation();
				break;
			}
		}
	}

	if (posRoomToMoveTo > -1)
	{
		rooms[posRoomToMoveTo].checkIn(activeReservation.getStartDate(), activeReservation.getEndDate(),
			activeReservation.getNote(), currentRoom.getGuests());
		rooms[suitableRoomIndex].removeActiveReservation();
		std::cout << "Room " << rooms[suitableRoomIndex].getNumber() << " is free for registration." << std::endl;
	}
	else
		std::cout << "There is no free room." << std::endl;
}

void Hotel::unavailable(unsigned roomNumber, const Date& start, const Date& end, const String& note)
{
	int numRooms = roomsNum();
	for (int i = 0; i < numRooms; i++)
	{
		if (rooms[i].getNumber() == roomNumber)
		{
			if (rooms[i].availableForCurrentReservation(start, end))
				rooms[i].makeUnavailable(start, end, note);
			else
				throw String("Currently the room is reserved.");
		}
	}
}
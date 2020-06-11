#include "Room.h"

bool Room::isLetterInt(char c) {
	return (c >= '0' && c <= '9');
}

bool Room::isStringInt(const String& currentStr) {
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

bool Room::sortReservations()
{
	if (reservations.size() == 0)
		return false;
	int size = reservations.size();
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (reservations[j].getTerm() < reservations[min].getTerm())
			{
				min = j;
			}
		}
		
		if (i != min)
		{
			Reservation firstReservation = reservations[i];
			reservations[i] = reservations[min];
			reservations[min] = firstReservation;
		}
	}

	return true;
}

Room::Room() {
	this->beds = 0;
	this->number = 0;
	this->guests = 0;
}

Room::Room(int beds, unsigned number)
{
	if (!(beds >= 1 && beds <= MAX_BEDS))
		throw String("The beds must be between 1 and 5.");
	if (number == 0)
		throw String("The room number must be positive number.");
	this->beds = beds;
	this->number = number;
	this->guests = 0;
}

int Room::getBeds() const
{
	return beds;
}

int Room::getGuests() const
{
	return guests;
}

int Room::getNumber() const
{
	return number;
}

Reservation Room::getReservation(unsigned index) const
{
	if (!(index >= 0 && index < reservations.size()))
		throw String("There is no reservation for this index.");
	return reservations[index];
}

Reservation Room::operator[](unsigned index) const
{
	return getReservation(index);
}

unsigned Room::reservationsNum() const
{
	return reservations.size();
}

Reservation Room::getUnavailableReservation() const
{
	return unavailableReservation;
}

bool Room::availableForFutureReservation(const Date& date) const 
{
	if (reservations.size() == 0)
		return true;

	if (date < reservations[reservations.size() - 1].getEndDate())
		return false;

	if (!(date >= unavailableReservation.getEndDate()))
		return false;
	return true;
}

bool Room::availableForCurrentReservation(const Date& from, const Date& to) const
{
	if (from >= to)
		return false;
	if (reservations.size() == 0)
		return true;

	if (reservations.size() > 0)
		if (!reservations[reservations.size() - 1].getFinished())
			return false;

	if (from < reservations[reservations.size() - 1].getEndDate())
		return false;

	if ((from >= unavailableReservation.getStartDate()) && (to <= unavailableReservation.getEndDate()))
		return false;
	return true;
}

bool Room::removeActiveReservation()
{
	if (!hasActiveReservation())
		return false;
	reservations.pop();
	this->guests = 0;
	return true;
}

bool Room::hasActiveReservation() const
{
	int reservationsSize = reservations.size();
	for (int i = 0; i < reservationsSize; i++)
		if (!reservations[i].getFinished())
			return true;
	return false;
}

bool Room::checkIn(const Date& start, const Date& end, const String& note, unsigned guests)
{
	if (!(guests >= 1 && guests <= this->beds))
		throw String("The guests must be between 1 and number of room beds.");
	if (start >= end)
		throw String("The period is not valid.");
	if (!note.size())
		throw String("There must be a note for the reservation.");

	if (!availableForCurrentReservation(start, end))
		throw String("There was a problem with checking in.");
	reservations.push_back(Reservation(Term(start, end), note));
	this->guests = guests;
	return true;
}

bool Room::checkOut()
{
	if (hasActiveReservation() && !reservations[reservations.size() - 1].getFinished())
	{
		reservations[reservations.size() - 1].finish();
		this->guests = 0;
		return true;
	}
	return false;
}

void Room::makeUnavailable(const Date& start, const Date& end, const String& note)
{
	if (start >= end)
		throw String("The period is not correct.");
	if (!note.size())
		throw String("There must be a note for the reason of unavailability.");
	unavailableReservation = Reservation(Term(start, end), note);
	std::cout << "The room is made unavailable for " << note << std::endl;
}

int Room::getDaysUsed(Date from, Date to) const
{
	if (from >= to)
		throw String("The period is not correct.");
	int numReservations = reservationsNum();
	int totalDays = 0;
	for (int i = 0; i < numReservations; i++)
	{
		Date currentReservationStartDate = reservations[i].getStartDate();
		Date currentReservationEndDate = reservations[i].getEndDate();
		if ((currentReservationStartDate >= from) && (currentReservationEndDate <= to))
			totalDays += currentReservationEndDate - currentReservationStartDate;
		if ((from >= currentReservationStartDate && from <= currentReservationEndDate) && to >= currentReservationEndDate)
			totalDays += currentReservationEndDate - from;
		if (from <= currentReservationStartDate && (to >= currentReservationStartDate && to <= currentReservationEndDate))
			totalDays += to - currentReservationStartDate;
		if ((from >= currentReservationStartDate && from <= currentReservationEndDate) &&
			(to >= currentReservationStartDate && to <= currentReservationEndDate))
			totalDays += to - from;
	}

	return totalDays;
}

std::ostream& operator << (std::ostream& out, const Room& currentRoom) {
	int numberReservations = currentRoom.reservationsNum();
	out << currentRoom.getNumber() << std::endl;
	out << currentRoom.getBeds() << std::endl;
	out << numberReservations << std::endl;
	for (int i = 0; i < numberReservations; i++)
		out << currentRoom[i];
	out << currentRoom.getUnavailableReservation();
	out << currentRoom.getGuests() << std::endl;
	return out;
}

std::istream& operator >> (std::istream& in, Room& currentRoom) {
	String roomNumber;
	String roomBeds;
	in >> roomNumber;
	in >> roomBeds;
	if (!currentRoom.isStringInt(roomNumber))
		throw String("The room number is not correct.");
	if (!currentRoom.isStringInt(roomBeds))
		throw String("The number of beds is not correct.");
	currentRoom = Room(roomBeds.strToInt(), roomNumber.strToInt());
	String numberOfReservations;
	in >> numberOfReservations;
	if (!currentRoom.isStringInt(numberOfReservations))
		throw String("The number of reservations is not correct.");
	int reservationsSize = numberOfReservations.strToInt();
	if (reservationsSize < 0)
		throw String("The number of reservations must be a positive number.");
	int countActiveReservations = 0;
	for (int i = 0; i < reservationsSize; i++)
	{
		Reservation currentReservation;
		in >> currentReservation;
		if (currentReservation.getFinished())
			countActiveReservations++;
		if (countActiveReservations > 1)
			throw String("The current room has more than one active reservations.");
		currentRoom.reservations.push_back(currentReservation);
	}
	in >> currentRoom.unavailableReservation;
	String numberGuests;
	in >> numberGuests;
	if (!currentRoom.isStringInt(numberGuests))
		throw String("The number of guests is not correct.");
	if (numberGuests > roomBeds)
		throw String("The number of guests is greater than the number of beds.");
	currentRoom.guests = numberGuests.strToInt();

	for (int j = 0; j < reservationsSize - 1; j++)
	{
		Term currentReservationTerm = currentRoom.reservations[j].getTerm();
		for (int p = j + 1; p < numberOfReservations; p++)
		{
			Term nextReservationTerm = currentRoom.reservations[p].getTerm();
			if (currentReservationTerm.intersectsWithAnotherTerm(nextReservationTerm))
				throw String("The reservations are not correct.");
		}
	}

	currentRoom.sortReservations();
	if (currentRoom.hasActiveReservation() && currentRoom[currentRoom.reservationsNum() - 1].getFinished())
		throw String("The current room's active reservation is not correct.");
	if (currentRoom.hasActiveReservation() && currentRoom.getGuests() == 0)
		throw String("The current room's active reservation is not correct.");
	if (!currentRoom.hasActiveReservation() && currentRoom.getGuests() > 0)
		throw String("The current room's number of guests is not correct.");
	return in;
}
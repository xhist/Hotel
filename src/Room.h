#pragma once
#include "Reservation.h"

const int MAX_BEDS = 5;
class Room
{
	unsigned number;
	Vector<Reservation> reservations;
	Reservation unavailableReservation;
	int guests;
	int beds;
private:
	bool isLetterInt(char c);
	bool isStringInt(const String& currentStr);
	bool sortReservations();
public:
	Room();
	Room(int beds, unsigned number);

	bool availableForFutureReservation(const Date& date) const;
	bool availableForCurrentReservation(const Date& from, const Date& to) const;

	bool removeActiveReservation();
	bool hasActiveReservation() const;
	int getBeds() const;
	int getGuests() const;
	int getNumber() const;
	Reservation getReservation(unsigned index) const;
	Reservation operator[](unsigned index) const;
	unsigned reservationsNum() const;
	Reservation getUnavailableReservation() const;

	bool checkIn(const Date& start, const Date& end, const String& note, unsigned guests);
	bool checkOut();
	void makeUnavailable(const Date& start, const Date& end, const String& note);
	int getDaysUsed(Date from, Date to) const;

	friend std::ostream& operator << (std::ostream& out, const Room& currentRoom);
	friend std::istream& operator >> (std::istream& in, Room& currentRoom);
};

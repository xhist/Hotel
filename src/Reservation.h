#pragma once
#include "Term.h"

class Reservation
{
	Term period;
	bool isFinished;
	String note;
public:
	Reservation() { isFinished = true; }
	Reservation(const Term& currentPeriod, const String& note);

	void finish();
	Term getTerm() const;
	Date getStartDate() const;
	Date getEndDate() const;
	bool getFinished() const;
	String getNote() const;

	friend std::ostream& operator << (std::ostream& out, const Reservation& currentReservation);
	friend std::istream& operator >> (std::istream& in, Reservation& currentReservation);
};


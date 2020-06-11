#include "Reservation.h"

Reservation::Reservation(const Term& currentPeriod, const String& currentNote) {
	period = currentPeriod;
	note = currentNote;
	isFinished = false;
}

void Reservation::finish() {
	isFinished = true;
}

Term Reservation::getTerm() const {
	return period;
}

Date Reservation::getStartDate() const { return period.getStartDate(); }

Date Reservation::getEndDate() const { return period.getEndDate(); }

bool Reservation::getFinished() const { return isFinished; }

String Reservation::getNote() const { return note; }

std::ostream& operator << (std::ostream& out, const Reservation& currentReservation) {
	out << currentReservation.getTerm() << ' ' << ((currentReservation.getFinished()) ? "yes" : "no") << ' ' 
		<< currentReservation.getNote() << std::endl;
	return out;
}

std::istream& operator >> (std::istream& in, Reservation& currentReservation) {
	in >> currentReservation.period;
	String reservationIsFinished;
	reservationIsFinished.readWord(in);
	if (reservationIsFinished == "yes")
		currentReservation.isFinished = true;
	else if (reservationIsFinished == "no")
		currentReservation.isFinished = false;
	else
		throw String("The reservation is not valid.");
	in >> currentReservation.note;
	currentReservation.note.trimWhiteSpaces();
	return in;
}
#include "Term.h"

Term::Term(const Date& start, const Date& end) {
	if (start > end)
		throw String("The period of time is not correct.");
	if (start == end)
	{
		startDate = start;
		endDate = startDate.getNextDay();
	}
	else
	{
		startDate = start;
		endDate = end;
	}
}

Date Term::getStartDate() const { return startDate; }

Date Term::getEndDate() const { return endDate; }

bool Term::operator<(const Term& other) const
{
	return (this->endDate <= other.startDate);
}

bool Term::operator==(const Term& other) const
{
	return (this->startDate == other.startDate && this->endDate == other.endDate);
}

bool Term::operator>(const Term& other) const {
	return (this->startDate >= other.endDate);
}

bool Term::intersectsWithAnotherTerm(const Term& other) const
{
	return ((this->startDate >= other.startDate && this->startDate < other.endDate) || 
		(this->endDate > other.startDate && this->endDate <= other.endDate));
}

std::ostream& operator << (std::ostream& out, const Term& currentTerm) {
	out << currentTerm.getStartDate() << ' ' << currentTerm.getEndDate();
	return out;
}

std::istream& operator >> (std::istream& in, Term& currentTerm) {
	Date startingDate;
	Date endingDate;
	in >> startingDate;
	in >> endingDate;
	currentTerm = Term(startingDate, endingDate);
	return in;
}
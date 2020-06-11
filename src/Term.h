#pragma once
#include "Date.h"

class Term
{
	Date startDate;
	Date endDate;
public:
	Term() {}
	Term(const Date& start, const Date& end);

	Date getStartDate() const;
	Date getEndDate() const;

	bool operator < (const Term& other) const;
	bool operator == (const Term& other) const;
	bool operator > (const Term& other) const;
	bool intersectsWithAnotherTerm(const Term& other) const;

	friend std::ostream& operator << (std::ostream& out, const Term& currentTerm);
	friend std::istream& operator >> (std::istream& in, Term& currentTerm);
};


#pragma once
#include "String.h"
#include "Vector.h"
#include <cmath>
class Date
{
	unsigned year;
	unsigned month;
	unsigned days;
private:
	bool isLetterInt(const char c);
	bool isStringInt(const String& currentStr);
	int	countDateWords(const String& currentStr);
	int extractDateInfo(const String& currentStr, Vector<String>& dateInfo);
	bool isDateValid(unsigned year, unsigned month, unsigned days);
	bool isLeapYear(unsigned year);
	int getMonthDays(unsigned month);
	int getAllDays(const Date& currentDate);
	int getLeapYears(unsigned year, unsigned month);
public:
	Date();
	Date(unsigned year, unsigned month, unsigned days);
	Date(const String& dateString);

	bool operator==(const Date& other) const;
	bool operator<(const Date& other) const;
	bool operator<=(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator>=(const Date& other) const;
	bool operator!=(const Date& other) const;
	int operator-(Date other);

	unsigned getYear() const;
	unsigned getMonth() const;
	unsigned getDays() const;

	Date getNextDay();

	void print() const;

	friend std::ostream& operator<<(std::ostream& out, const Date& currentDate);
	friend std::istream& operator>>(std::istream& in, Date& currentDate);
};


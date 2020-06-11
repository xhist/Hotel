#include "Date.h"

bool Date::isLetterInt(const char c) {
	return (c >= '0' && c <= '9');
}

bool Date::isStringInt(const String& currentStr) {
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

int Date::countDateWords(const String& text) {
	int length = 0;
	int count = 0;
	while (text[length])
	{
		if (text[length] && text[length] != '-')
			++count;
		while (text[length] && text[length] != '-')
			length++;
		while (text[length] && text[length] == '-')
			length++;
	}
	return count;
}

int Date::extractDateInfo(const String& text, Vector<String>& dateInfo) {
	int countWords = countDateWords(text);
	int length = 0;
	for (int i = 0; i < countWords; i++)
	{
		int sizeWord = 0;
		int beginWord = 0;
		if (text[length] && text[length] != '-')
			beginWord = length;

		while (text[length] && text[length] != '-')
		{
			sizeWord++;
			length++;
		}

		while (text[length] && text[length] == '-')
			length++;

		if (sizeWord > 0)
		{
			String currentWord(sizeWord);
			int currentSize = 0;
			for (int j = beginWord; j < length; j++)
			{
				if (text[j] != '-' && currentSize < sizeWord)
					currentWord[currentSize++] = text[j];
			}
			dateInfo.push_back(currentWord);
		}
	}
	return countWords;
}

bool Date::isLeapYear(unsigned year) {
	if (year % 4 == 0) {
		if (year % 400 == 0)
			return true;
		if (year % 100 == 0)
			return false;
		return true;
	}
	return true;
}

bool Date::isDateValid(unsigned year, unsigned month, unsigned day) {
	if (year < 1970)
		throw String("The year is not correct.");
	if (!(month >= 1 && month <= 12))
		throw String("The month is not correct.");
	if (!(day >= 1 && day <= 31))
		throw String("The day is not correct.");
	switch (month) {
	case 2:
		if (isLeapYear(year))
		{
			if (day > 29)
				return false;
		}
		else {
			if (day > 28)
				return false;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (day > 30)
			return false;
		break;
	}

	return true;
}

int Date::getMonthDays(unsigned month)
{
	int days = 0;
	if (!(month >= 1 && month <= 12))
		throw String("The month is not correct.");
	switch (month) {
	case 2:
		days = 28;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		days = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		days = 30;
		break;
	}

	return days;
}

int Date::getLeapYears(unsigned year, unsigned month) {
	if (month <= 2)
		year--;
	return (year / 4) - (year / 100) + (year / 400);
}

int Date::getAllDays(const Date& currentDate) 
{
	int days = currentDate.getYear() * 365 + currentDate.getDays();
	for (int i = 1; i <= currentDate.getMonth() - 1; i++)
		days += getMonthDays(i);
	days += getLeapYears(currentDate.getYear(), currentDate.getMonth());
	return days;
}

Date::Date() {
	year = 1970;
	month = 1;
	days = 1;
}

Date::Date(const String& currentDate) {
	if (currentDate.countSymbol('-') != 2)
		throw String("The current date is not in the format [yyyy]-[mm]-[dd].");
	Vector<String> dateInfo;
	int countWords = extractDateInfo(currentDate, dateInfo);
	if (countWords != 3)
		throw String("The current date is not in the format [yyyy]-[mm]-[dd].");
	if (dateInfo[0].size() != 4 || !isStringInt(dateInfo[0]))
		throw String("The year is not correct.");
	if (dateInfo[1].size() != 2 || !isStringInt(dateInfo[1]))
		throw String("The month is not correct.");
	if (dateInfo[2].size() != 2 || !isStringInt(dateInfo[2]))
		throw String("The day is not correct.");
	int currentYear = dateInfo[0].strToInt();
	int currentMonth = dateInfo[1].strToInt();
	int currentDay = dateInfo[2].strToInt();
	if (!isDateValid(currentYear, currentMonth, currentDay))
		throw String("The date is not valid.");
	year = currentYear;
	month = currentMonth;
	days = currentDay;
}

Date::Date(unsigned _year, unsigned _month, unsigned _day) {
	if (!isDateValid(_year, _month, _day))
		throw String("The date is not valid.");
	year = _year;
	month = _month;
	days = _day;
}

bool Date::operator==(const Date& other) const {
	return (year == other.year && month == other.month && days == other.days);
}

bool Date::operator!=(const Date& other) const {
	return !(*this == other);
}

bool Date::operator<(const Date& other) const {
	int differenceYears = (int)year - (int)other.year;
	int differenceMonths = (int)month - (int)other.month;
	int differenceDays = (int)days - (int)other.days;
	if (differenceYears > 0)
		return false;
	if ((differenceYears == 0) && differenceMonths > 0)
		return false;
	if ((differenceYears == 0) && (differenceMonths == 0) && differenceDays >= 0)
		return false;
	return true;
}

bool Date::operator<=(const Date& other) const {
	return (*this == other || *this < other);
}

bool Date::operator>(const Date& other) const {
	return !(*this <= other);
}

bool Date::operator>=(const Date& other) const {
	return !(*this < other);
}

int Date::operator-(Date other) {
	int firstDateDays = getAllDays(*this);
	int secondDateDays = getAllDays(other);
	return abs(firstDateDays - secondDateDays);
}

unsigned Date::getYear() const { return year; }	

unsigned Date::getMonth() const { return month; }

unsigned Date::getDays() const { return days; }

Date Date::getNextDay()
{
	unsigned currentYear = year;
	unsigned currentMonth = month;
	unsigned currentDays = days;
	unsigned monthDays = getMonthDays(month) + (isLeapYear(currentYear) && month == 2) ? 1 : 0;
	if (currentDays + 1 > monthDays)
	{
		currentDays = 1;
		if (currentMonth == 12)
		{
			currentMonth = 1;
			currentYear++;
		}
		else
			currentMonth++;
	}
	else
		currentDays++;
	return Date(currentYear, currentMonth, currentDays);
}

void Date::print() const {
	std::cout << year << '-';
	if (month < 10)
		std::cout << '0';
	std::cout << month << '-';
	if (days < 10)
		std::cout << '0';
	std::cout << days << std::endl;
}

std::ostream& operator << (std::ostream& out, const Date& date) {
	out << date.getYear() << '-';
	if (date.getMonth() < 10)
		out << '0';
	out << date.getMonth() << '-';
	if (date.getDays() < 10)
		out << '0';
	out << date.getDays();

	return out;
}

std::istream& operator >> (std::istream& in, Date& date) {
	String dateString;
	dateString.readWord(in);
	date = Date(dateString);
	return in;
}
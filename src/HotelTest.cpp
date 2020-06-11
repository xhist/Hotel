#include "HotelTest.h"

void HotelTest::testHotelValidCheckinWithoutActiveReservation()
{
	try {
		std::cout << "Testing hotel checkin......." << std::endl;
		std::ifstream hotelFile("testHotel.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Checkin in room number 4..." << std::endl;
		currentHotel.checkin(4, Date("2020-05-03"), Date("2020-05-06"), "The simpsons", 2);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
		assert(false);
	}
}

void HotelTest::testHotelInvalidCheckinWithActiveReservation()
{
	try {
		std::cout << "Testing hotel checkin......." << std::endl;
		std::ifstream hotelFile("testHotel.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Checkin in room number 2 with active reservation..." << std::endl;
		currentHotel.checkin(2, Date("2020-08-03"), Date("2020-08-10"), "Peter Ivanov", 1);
		assert(false);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

void HotelTest::testHotelValidCheckoutWithActiveReservation()
{
	try {
		std::cout << "Testing hotel checkout......" << std::endl;
		std::ifstream hotelFile("testHotel.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Checkout room number 2 which has active reservation......." << std::endl;
		currentHotel.checkout(2);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
		assert(false);
	}
}

void HotelTest::testHotelInvalidCheckoutWithoutActiveReservation()
{
	try {
		std::cout << "Testing hotel checkout......" << std::endl;
		std::ifstream hotelFile("testHotel.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Checkout room number 2 again but without active reservation......" << std::endl;
		currentHotel.checkout(2);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
		assert(false);
	}
}

void HotelTest::testHotelReport()
{
	std::cout << "Testing hotel report...." << std::endl;
	std::ifstream hotelFile("testHotel.txt");
	Hotel currentHotel;
	currentHotel.loadData(hotelFile);
	hotelFile.close();
	std::cout << "Report rooms' usage by days in period [2020-04-04; 2020-05-05]....." << std::endl;
	currentHotel.report(Date("2020-04-04"), Date("2020-05-05"));
	std::cout << "Report rooms' usage by days in period [2020-08-08; 2020-08-10]....." << std::endl;
	currentHotel.report(Date("2020-08-08"), Date("2020-08-10"));
}

void HotelTest::testHotelAvailability()
{
	std::cout << "Testing hotel rooms availability....." << std::endl;
	std::ifstream hotelFile("testHotel.txt");
	Hotel currentHotel;
	currentHotel.loadData(hotelFile);
	hotelFile.close();
	std::cout << "Availability for date 2020-04-04....." << std::endl;
	currentHotel.availability(Date("2020-04-04"));
}

void HotelTest::testHotelValidFindWithValidBedsAndPeriod()
{
	try {
		std::cout << "Testing hotel find suitable room....." << std::endl;
		std::ifstream hotelFile("testHotel.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Find room with 4 beds for period [2020-06-04; 2020-06-20]...." << std::endl;
		currentHotel.find(4, Date("2020-06-04"), Date("2020-06-20"));
	}
	catch (const String& error) {
		std::cout << error << std::endl;
		assert(false);
	}
}

void HotelTest::testHotelInvalidFindWithInvalidNumberOfBeds()
{
	try {
		std::cout << "Testing hotel find suitable room....." << std::endl;
		std::ifstream hotelFile("testHotel.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Find room with 6 beds(incorrect input) for period [2020-04-04; 2020-04-20]...." << std::endl;
		currentHotel.find(6, Date("2020-04-04"), Date("2020-04-20"));
		assert(false);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

void HotelTest::testHotelFindEmergently()
{
	try {
		std::cout << "Testing hotel command find!....." << std::endl;
		std::ifstream hotelFile("testHotelFind!.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Checkout room number 2 with 1 bed so that it's free...." << std::endl;
		currentHotel.checkout(2);
		std::cout << "Find room of 4 beds for special guests in period [2020-08-02; 2020-08-10]...." << std::endl;
		currentHotel.findEmergent(4, Date("2020-08-02"), Date("2020-08-10"));
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

void HotelTest::testHotelValidUnavailabilityWithoutActiveReservation()
{
	try {
		std::cout << "Testing hotel room unavailability...." << std::endl;
		std::ifstream hotelFile("testHotel.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Make room 4 which has no active reservation unavailable for maintenance in period [2020-06-04; 2020-06-06]...." << std::endl;
		currentHotel.unavailable(4, Date("2020-06-04"), Date("2020-06-06"), "Maintenance");
	}
	catch (const String& error) {
		std::cout << error << std::endl;
		assert(false);
	}
}

void HotelTest::testHotelInvalidUnavailabilityWithActiveReservation()
{
	try {
		std::cout << "Testing hotel room unavailability...." << std::endl;
		std::ifstream hotelFile("testHotel.txt");
		Hotel currentHotel;
		currentHotel.loadData(hotelFile);
		hotelFile.close();
		std::cout << "Make room 2 which has active reservation unavailable for maintenance in period [2020-06-04; 2020-06-10]...." << std::endl;
		currentHotel.unavailable(2, Date("2020-04-04"), Date("2020-04-10"), "Maintenance");
		assert(false);
	}
	catch (const String& error) {
		std::cout << error << std::endl;
	}
}

void HotelTest::testAllHotelFunctions()
{
	std::cout << "Testing all supported functions ....." << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	testHotelValidCheckinWithoutActiveReservation();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelInvalidCheckinWithActiveReservation();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelValidCheckoutWithActiveReservation();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelInvalidCheckoutWithoutActiveReservation();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelReport();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelAvailability();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelValidFindWithValidBedsAndPeriod();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelInvalidFindWithInvalidNumberOfBeds();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelFindEmergently();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelValidUnavailabilityWithoutActiveReservation();
	std::cout << std::endl << "-----------------------------" << std::endl;
	testHotelInvalidUnavailabilityWithActiveReservation();
	std::cout << std::endl << "-----------------------------" << std::endl;
}

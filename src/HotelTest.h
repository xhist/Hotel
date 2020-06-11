#pragma once
#include "Hotel.h"
#include <cassert>

class HotelTest
{
public:
	HotelTest() = delete;

	static void testHotelValidCheckinWithoutActiveReservation();
	static void testHotelInvalidCheckinWithActiveReservation();
	static void testHotelValidCheckoutWithActiveReservation();
	static void testHotelInvalidCheckoutWithoutActiveReservation();
	static void testHotelReport();
	static void testHotelAvailability();
	static void testHotelValidFindWithValidBedsAndPeriod();
	static void testHotelInvalidFindWithInvalidNumberOfBeds();
	static void testHotelFindEmergently();
	static void testHotelValidUnavailabilityWithoutActiveReservation();
	static void testHotelInvalidUnavailabilityWithActiveReservation();
	static void testAllHotelFunctions();
};


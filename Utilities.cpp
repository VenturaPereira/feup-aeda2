#pragma once

#include "Utilities.h"

bool leapYear(const unsigned short int &year)
{
	if ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0))
		return true;
	else return false;
}

unsigned int numberDays(const unsigned short int &year, const unsigned short int &month)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		if (leapYear(year))
			return 29;
		else return 28;
	default:
		return 0;
	}
}
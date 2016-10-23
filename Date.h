#pragma once

#ifndef DATE_H
#define DATE_H


#include <string>
using namespace std;

class Date
{
private:
	//MEMBER VARIABLES
	unsigned short int day, month, year;
	bool valid;
public:
	//MEMBER FUNCTIONS
	Date();
	Date(unsigned short int d, unsigned short int m, unsigned short int y);
	bool verifyDate();
	void printDate() const;
	string dateToString() const;

	//GETS
	unsigned short int getYear() const { return year; }
	unsigned short int getMonth() const { return month; }
	unsigned short int getDay() const { return day; }
	bool getValid() const { return valid; }

	//SETS
	void setYear(unsigned short int y) { year = y; valid = verifyDate(); }
	void setMonth(unsigned short int m)  { month = m; valid = verifyDate(); }
	void setDay(unsigned short int d)  { day = d; valid = verifyDate();	}
	
};

#endif

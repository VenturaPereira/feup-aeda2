#pragma once

#ifndef DATE_H
#define DATE_H


#include <string>
using namespace std;

class Date
{
private:
	unsigned short int day, month, year;
	bool valid;
public:
	Date();
	Date(unsigned short int d, unsigned short int m, unsigned short int y);
	bool verifyDate();
	void printDate() const;
	string dateToString() const;
	unsigned short int getYear() const { return year; }
	unsigned short int getMonth() const { return month; }
	unsigned short int getDay() const { return day; }
	bool getValid() const { return valid; }


};

#endif

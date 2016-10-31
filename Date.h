#pragma once

#ifndef DATE_H
#define DATE_H

#include "Utilities.h"
#include <ctime>
#include <string>
#include <sstream>
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
	Date(string dayMonthYear);
	bool verifyDate();

	//OPERATORS
	friend istream& operator>> (istream &is, Date &date);
	friend ostream& operator<< (ostream &os, Date &date);
	friend bool operator==(const Date &LHS, const Date &RHS);
	friend bool operator<(const Date &LHS, const Date &RHS);
	friend bool operator>(const Date &LHS, const Date &RHS);
	friend bool operator<=(const Date &LHS, const Date &RHS);
	friend bool operator>=(const Date &LHS, const Date &RHS);
	

	//GETS
	unsigned short int getYear() const { return year; }
	unsigned short int getMonth() const { return month; }
	unsigned short int getDay() const { return day; }
	bool getValid() const { return valid; }
	string getDateString() const;

	//SETS
	void setYear(unsigned short int y) { year = y; valid = verifyDate(); }
	void setMonth(unsigned short int m)  { month = m; valid = verifyDate(); }
	void setDay(unsigned short int d)  { day = d; valid = verifyDate();	}
	void setDate(unsigned short int y, unsigned short int m, unsigned short int d);
	void setDate(string dayMonthYear);
};

#endif

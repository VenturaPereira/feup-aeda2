#pragma once

#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

/*
*	Class for Dates
*/
class Date
{
private:
	//MEMBER VARIABLES
	unsigned short int day, month, year;
	bool valid;
public:
	//MEMBER FUNCTIONS
	/*
	*	Date Default Constructor
	*/
	Date();

	/*
	*	Date Constructor with Day, Month and Year
	*/
	Date(unsigned short int d, unsigned short int m, unsigned short int y);

	/*
	*	Date Constructor with a String that as Day, Month and Year
	*/
	Date(string dayMonthYear);

	/*
	*	Date Destructor
	*/
	~Date() {}

	/*
	*	Checks if date is valid
	*/
	bool verifyDate();

	//OPERATORS
	/*
	*	Operator >> for input
	*/
	friend istream& operator>> (istream &is, Date &date);

	/*
	*	Operator << for saving and output
	*/
	friend ostream& operator<< (ostream &os, Date &date);

	/*
	*	Operator == for Comparison
	*/
	friend bool operator==(const Date &LHS, const Date &RHS);

	/*
	*	Operator < for Comparison
	*/
	friend bool operator<(const Date &LHS, const Date &RHS);

	/*
	*	Operator > for Comparison
	*/
	friend bool operator>(const Date &LHS, const Date &RHS);

	/*
	*	Operator <= for Comparison
	*/
	friend bool operator<=(const Date &LHS, const Date &RHS);

	/*
	*	Operator >= for Comparison
	*/
	friend bool operator>=(const Date &LHS, const Date &RHS);
	

	//GETS
	/*
	*	Returns Year
	*/
	unsigned short int getYear() const { return year; }

	/*
	*	Returns Month
	*/
	unsigned short int getMonth() const { return month; }

	/*
	*	Returns Date
	*/
	unsigned short int getDay() const { return day; }

	/*
	*	Returns If Date is Valid
	*/
	bool getValid() const { return valid; }

	/*
	*	Returns Date as String
	*/
	string getDateString() const;

	//SETS
	/*
	*	Sets Year
	*/
	void setYear(unsigned short int y) { year = y; valid = verifyDate(); }

	/*
	*	Sets Month
	*/
	void setMonth(unsigned short int m)  { month = m; valid = verifyDate(); }

	/*
	*	Sets Day
	*/
	void setDay(unsigned short int d)  { day = d; valid = verifyDate();	}

	/*
	*	Sets Year, Month and Day
	*/
	void setDate(unsigned short int y, unsigned short int m, unsigned short int d);

	/*
	*	Sets Year, Month and Day
	*/
	void setDate(string dayMonthYear);
};

#endif

#pragma once

#include "Date.h"

Date::Date()
{
	time_t now = time(0);
	tm timeinfo;
	localtime_s(&timeinfo, &now);
	year = 1900 + timeinfo.tm_year;
	month = 1 + timeinfo.tm_mon;
	day = timeinfo.tm_mday;
	valid = true;
}

Date::Date(unsigned short int d, unsigned short int m, unsigned short int y)
{
	year = y;
	month = m;
	day = d;
	valid = verifyDate();
}

bool Date::verifyDate()
{
	if (month > 12 || month < 1 || day > numberDays(year, month) || day < 1)
		return false;
	else return true;
}

Date::Date(string dayMonthYear)
{
	istringstream iss(dayMonthYear);
	char delimiter;
	iss >> day >> ws >> delimiter >> month >> ws >> delimiter >> year >> ws;
	if (iss.fail() || !iss.eof() || !verifyDate())
		valid = false;
	else valid = true;
}

void Date::setDate(unsigned short int y, unsigned short int m, unsigned short int d)
{
	year = y;
	day = d;
	month = m;
	valid = verifyDate();
}

void Date::setDate(string dayMonthYear)
{
	istringstream iss(dayMonthYear);
	char delimiter;
	iss >> ws >> day >> ws >> delimiter >> ws >> month >> ws >> delimiter >> ws >> year >> ws;
	if (iss.fail() || !iss.eof() || !verifyDate)
		valid = false;
	else valid = true;
}

string Date::getDateString() const
{
	string dateString;
	if (day < 10)
		dateString = dateString + to_string(0);
	dateString = dateString + to_string(day) + '/';
	if (month < 10)
		dateString = dateString + to_string(0);
	dateString = dateString + to_string(month) + '/' + to_string(year);
	return dateString;
}

istream& operator >> (istream &is, Date &date)
{
	string dateString;
	getline(is, dateString);
	date.setDate(dateString);
	is.clear();
	return is;
}

ostream& operator<< (ostream &os, Date &date)
{
	os << date.getDateString();
	return os;
}

bool operator==(const Date &LHS, const Date &RHS)
{
	return (LHS.getDateString() == RHS.getDateString());
}

bool operator<(const Date &LHS, const Date &RHS)
{
	return (LHS.getDateString() < RHS.getDateString());
}

bool operator>(const Date &LHS, const Date &RHS)
{
	return (LHS.getDateString() > RHS.getDateString());
}

bool operator<=(const Date &LHS, const Date &RHS)
{
	return (LHS < RHS || LHS == RHS);
}

bool operator>=(const Date &LHS, const Date &RHS)
{
	return (LHS > RHS || LHS == RHS);
}
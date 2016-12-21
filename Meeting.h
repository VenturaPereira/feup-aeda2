#pragma once

#include "Date.h"

class Student;

class Meeting {
private:
	Date date;
	unsigned int hour, minute;
	Student* student;
	string description;

public:
	Meeting(Date d, Student* su, string des, unsigned int hour, unsigned int minute);

	Date getDate() const { return date; }

	bool hasOccured() const;
	void show() const;
	friend bool operator<(const Meeting &m1, const Meeting &m2);
	friend bool operator==(const Meeting &m1, const Meeting &m2);
};
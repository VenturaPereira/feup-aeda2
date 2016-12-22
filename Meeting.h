#pragma once

#include "Date.h"

class Student;

class Meeting {
private:
	//VARIABLES
	Date date;
	unsigned int hour, minute;
	Student* student;
	string topics, description;

public:
	//CONSTRUCTORS
	Meeting(Date d, Student* su, string top, unsigned int hour, unsigned int minute);

	//GETS
	Date getDate() const { return date; }
	
	//SETS
	void setDescription(string des) { description = des; }

	//FUNCTIONS
	bool hasOccured() const;
	void show() const;
	friend bool operator<(const Meeting &m1, const Meeting &m2);
	friend bool operator==(const Meeting &m1, const Meeting &m2);
};
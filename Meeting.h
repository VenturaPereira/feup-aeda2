#pragma once

#ifndef MEETING_H
#define MEETING_H


#include "Date.h"
#include <vector>

class Student;
class Tutor;

class Meeting {
private:
	//VARIABLES
	Date date;
	unsigned int hour, minute;
	Student* student;
	Tutor* professor;
	vector<string> topics;
	string description;


public:
	//CONSTRUCTORS
	/*!
	*	Meetings Constructor with Date, Student, Tutor, Topics of the Meeting, Hour and Minutes
	*/
	Meeting(Date d, Student* st, Tutor* t, vector<string> &top, unsigned int hour, unsigned int minute);

	//GETS
	/*!
	*	Returns the Date
	*/
	Date getDate() const { return date; }
	
	//SETS
	/*!
	*	Sets a Description for the Meeting
	*/
	void setDescription(string des) { description = des; }

	//FUNCTIONS
	/*!
	*	Returns if the Meeting already occured
	*/
	bool hasOccured() const;

	/*!
	*	Prints a Meeting to the screen
	*/
	void show() const;

	/*!
	*	Operator < for Meetings Comparison
	*/
	friend bool operator<(const Meeting &m1, const Meeting &m2);

	/*!
	*	Operator == for Meetings Comparison
	*/
	friend bool operator==(const Meeting &m1, const Meeting &m2);

	/*!
	*	Operator << for saving Meetings into files
	*/
	ofstream& Meeting::operator<<(ofstream& file);
};

#endif
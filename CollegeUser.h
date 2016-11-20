#pragma once

#ifndef COLLEGEUSER_H
#define COLLEGEUSER_H

#include <string>
#include "Date.h"
using namespace std;

class College;
class Course;

class CollegeUser 
{
protected:
	//MEMBER VARIABLES
	College* college;
	string name;
	string email;
	unsigned long long int ID;
	Date dateOfRegistration, dateOfBirth;
	
public:
	//MEMBER FUNCTIONS
	/*!
	*	College User Constructor with Name, Date of Birth and Course
	*/
	CollegeUser(string n, Date dob, Course& c);
	/*!
	*	College User Destructor
	*/
	virtual ~CollegeUser() {}
	virtual void assignEmail() = 0;
	virtual void assignID() = 0;

	//GETS
	/*!
	*	Returns College User ID
	*/
	unsigned long long int getID() const { return ID; }

	/*!
	*	Returns College User Name
	*/
	string getName() const { return name; }

	/*!
	*	Returns College User Date of Registration
	*/
	Date getDateOfRegistration() const { return dateOfRegistration; }

	/*!
	*	Returns College User Date of Birth
	*/
	Date getDateOfBirth() const { return dateOfBirth; }

	//SETS
	/*!
	*	Sets the College User ID to a given ID
	*/
	void setID(unsigned long long int id) { ID = id; }
	
};

#endif
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
	CollegeUser(string n, Date dob, Course& c);
	virtual void assignEmail() = 0;
	virtual void assignID() = 0;

	//GETS
	unsigned long long int getID() const { return ID; }
	string getName() const { return name; }
	Date getDateOfRegistration() const { return dateOfRegistration; }
	Date getDateOfBirth() const { return dateOfBirth; }

	//SETS
	void setID(unsigned long long int id) { ID = id; }
	
};

#endif
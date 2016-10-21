#pragma once

#ifndef COLLEGEUSER_H
#define COLLEGEUSER_H

#include <string>
#include "Date.h"
using namespace std;

class CollegeUser 
{
protected:
	//MEMBER VARIABLES
	const string name;
	string email;
	unsigned long long int ID;
	const Date dateOfRegistration, dateOfBirth;
	
public:
	//MEMBER FUNCTIONS
	CollegeUser(string n, Date dob) : name(n), dateOfBirth(dob), dateOfRegistration() {}
	virtual void assignEmail() = 0;
	virtual void assignID() = 0;

	//GETS
	string getName() const { return name; }
	Date getDateOfRegistration() const { return dateOfRegistration; }
	Date getDateOfBirth() const { return dateOfBirth; }
	
	//SETS
	void setEmail(string e) { email = e; }
	void setID(unsigned long long int id) { ID = id; }
	
};

#endif
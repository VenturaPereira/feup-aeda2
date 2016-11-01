#pragma once

#ifndef ENROLLMENTSYSTEM_H
#define ENROLLMENTSYSTEM_H

#include "Student.h"

class University;

class EnrollmentSystem
{
private:
	//MEMBER VARIABLES
	const unsigned int MAXIMUM_CREDITS;
	vector<University*> universitiesVector;
		
public:
	//MEMBER FUNCTIONS
	EnrollmentSystem(unsigned int mc) : MAXIMUM_CREDITS(mc) {};

	//HANDLERS (COMMUNICATION WITH THE USER)
	bool addStudentHandler(Course* c);

	//GETS
	unsigned int getMaxCredits() const { return MAXIMUM_CREDITS; }
	vector<University*> getUniversities() const { return universitiesVector; }

};

#endif
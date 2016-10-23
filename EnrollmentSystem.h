#pragma once

#ifndef ENROLLMENTSYSTEM_H
#define ENROLLMENTSYSTEM_H

//#include <vector>
#include "CourseUnit.h"
using namespace std;

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
	//bool assignTeachers(CourseUnit &cu);

	//GETS
	unsigned int getMaxCredits() const { return MAXIMUM_CREDITS; }
	vector<University*> getUniversities() const { return universitiesVector; }

};

#endif
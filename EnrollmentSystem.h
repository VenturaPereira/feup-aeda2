#pragma once

#ifndef ENROLLMENTSYSTEM_H
#define ENROLLMENTSYSTEM_H

#include <vector>
#include "CourseUnit.h"
using namespace std;

class University;

class EnrollmentSystem
{
public:
	const unsigned int MAXIMUM_CREDITS;
	vector<University*> universitiesVector;

	EnrollmentSystem(unsigned int mc) : MAXIMUM_CREDITS(mc) {};
	bool assignTeachers(CourseUnit &cu);

	
protected:
	


};

#endif
#pragma once

#ifndef TUTOR_H
#define TUTOR_H

//#include <vector>
using namespace std;

#include "Course.h"
#include "CourseUnit.h"
#include "CourseUnitClass.h"
class Tutor 
{
private:
	//MEMBER VARIABLES
	Course* course;
	vector<CourseUnit*> ableToTeach, currentlyTeaching;

	virtual void assignEmail();
	virtual void assignID();
public:
	//MEMBER FUNCTIONS
	bool teachClass(CourseUnitClass &c);

	//GETS
	Course* getCourse() const { return course; }
	vector<CourseUnit*> getAbleToTeach() const { return ableToTeach; }
	vector<CourseUnit*>	getCurrentlyTeaching() const { return currentlyTeaching; }
};

#endif


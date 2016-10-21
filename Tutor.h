#pragma once

#ifndef TUTOR_H
#define TUTOR_H

#include <vector>
using namespace std;

#include "Course.h"
#include "CourseUnit.h"
#include "CourseUnitClass.h"
class Tutor 
{
private:
	string name;
	Course* course;
	vector<CourseUnit*> ableToTeach, currentlyTeaching;

	virtual void assignEmail();
	virtual void assignID();
public:
	bool teachClass(CourseUnitClass &c);
};

#endif


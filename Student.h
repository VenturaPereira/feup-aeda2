#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "CollegeUser.h"
#include "Course.h"
#include "CourseUnit.h"
#include "CourseUnitClass.h"
#include "Date.h"

#include <vector>
#include <map>

using namespace std;

class Student : protected CollegeUser
{
protected:
	Course* course;
	map<CourseUnit*, unsigned short int> completedCourseUnits;
	map<CourseUnit*, CourseUnitClass*> classesCurrentlyAtending;

	virtual void assignEmail();
	virtual void assignID();
public:
	bool enrollCourseUnit(CourseUnit &courseUnit);
	bool enrollClass(CourseUnitClass &courseUnitClass);
};

#endif

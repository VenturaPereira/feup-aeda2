#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "Date.h"
#include "CollegeUser.h"
#include "Course.h"
#include "CourseUnitClass.h"
#include "Tutor.h"
#include <map>

using namespace std;

class Student : protected CollegeUser
{
protected:
	//MEMBER VARIABLES
	Course* course;
	map<CourseUnit*, unsigned short int> completedCourseUnits;
	map<CourseUnit*, CourseUnitClass*> classesCurrentlyAtending;
	Tutor* tutor;

	virtual void assignEmail();
	virtual void assignID();
public:
	//MEMBER FUNCTIONS
	Student(string n, Date dob, Course* c);
	bool assignTutor();
	bool enrollCourseUnit(CourseUnit* courseUnit);
	bool enrollClass(CourseUnitClass* courseUnitClass);
	void completedClass(CourseUnit *courseUnit, unsigned short int grade);
	friend int compareID(Student & s1, Student & s2);
	friend bool compareName(Student & s1, Student & s2);
	//GETS
	Course* getCourse() const { return course; }
	map<CourseUnit*, unsigned short int> getCompletedCourseUnits() const {return completedCourseUnits;}
	map<CourseUnit*, CourseUnitClass*> getClassesCurrentlyAtending() const { return classesCurrentlyAtending; }
};

#endif

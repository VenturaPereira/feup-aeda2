#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "CollegeUser.h"
#include "Date.h"
#include <string>
#include <vector>
#include <map>

class Course;
class CourseUnit;
class CourseUnitClass;
class Tutor;

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

	//GETS
	Course* getCourse() const { return course; }
	map<CourseUnit*, unsigned short int> getCompletedCourseUnits() const {return completedCourseUnits;}
	map<CourseUnit*, CourseUnitClass*> getClassesCurrentlyAtending() const { return classesCurrentlyAtending; }
};

#endif

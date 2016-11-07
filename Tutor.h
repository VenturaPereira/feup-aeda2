#pragma once

#ifndef TUTOR_H
#define TUTOR_H

#include "CollegeUser.h"
#include <vector>
using namespace std;

class Course;
class CourseUnit;
class Student;
class CourseUnitClass;

class Tutor : public CollegeUser
{
private:
	//MEMBER VARIABLES
	Course* course;
	vector<CourseUnit*> ableToTeach, currentlyTeaching;
	vector<Student*> students;

	//MEMBER FUNCTIONS
	virtual void assignEmail();
	virtual void assignID();
public:
	//MEMBER FUNCTIONS
	bool teachClass(CourseUnitClass* c);
	void tutorStudent(Student* s);

	//GETS
	Course* getCourse() const { return course; }
	vector<CourseUnit*> getAbleToTeach() const { return ableToTeach; }
	vector<CourseUnit*>	getCurrentlyTeaching() const { return currentlyTeaching; }
	vector<Student*> getStudents() const { return students; }
};

#endif


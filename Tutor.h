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
	Tutor(string n, Date dob, Course* c, vector<CourseUnit*> att);
	bool teachClass(CourseUnitClass* c);
	void tutorStudent(Student* s);

	//COMPARES
	friend bool compareProfessorByName(Tutor* p1, Tutor* p2);
	friend bool compareProfessorByID(Tutor* p1, Tutor* p2);
	friend bool compareProfessorByBirth(Tutor* p1, Tutor* p2);

	//GETS
	Course* getCourse() const { return course; }
	vector<CourseUnit*> getAbleToTeach() const { return ableToTeach; }
	vector<CourseUnit*>	getCurrentlyTeaching() const { return currentlyTeaching; }
	vector<Student*> getStudents() const { return students; }

	//PRINT TO SCREEN
	void show() const;
	
	//OPERATORS
	friend ofstream& operator<<(ofstream& file, const Tutor *t);
};

#endif


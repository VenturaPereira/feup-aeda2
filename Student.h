#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "CollegeUser.h"
#include <string>
#include <vector>
#include <map>

class Course;
class CourseUnit;
class CourseUnitClass;
class Tutor;

using namespace std;

class Student : public CollegeUser
{
protected:
	//MEMBER VARIABLES
	Course* course;
	map<CourseUnit*, unsigned short int> completedCourseUnits;
	map<CourseUnit*, CourseUnitClass*> classesCurrentlyAtending;
	Tutor* tutor;
	unsigned short int year;
	string status; //REGULAR STUDENT, WORKING STUDENT, SPECIAL NEEDS
	double credits; //CREDITS THIS YEAR

	virtual void assignEmail();
	virtual void assignID();
public:
	//MEMBER FUNCTIONS
	Student(string n, Date dob, Course& c);
	Student(string n, Date dob, Course& c, Tutor& t, unsigned short int y, double cr, string s, map<CourseUnit*, unsigned short int> &ccu, map<CourseUnit*, CourseUnitClass*> &cca, unsigned long long int &id);
	bool assignTutor();
	bool enrollCourseUnit(CourseUnit& courseUnit);
	bool enrollClass(CourseUnitClass& courseUnitClass);
	bool completedClass(CourseUnit& courseUnit, unsigned short int grade);
	bool completedAllCourseUnits(unsigned short int y);

	//COMPARES
	friend bool compareStudentByID(Student* s1, Student* s2);
	friend bool compareStudentByName(Student* s1, Student* s2);
	friend bool compareStudentByCouseYear(Student* s1, Student* s2);
	friend bool compareStudentByBirth(Student* s1, Student* s2);
		
	//SETS
	void setStatus(string s) { status = s; }
	void setCredits(double c) { credits = c; }
	void setYear(unsigned short int y) { year = y; }

	//GETS
	Course& getCourse() { return *course; }
	map<CourseUnit*, unsigned short int>& getCompletedCourseUnits() {return completedCourseUnits;}
	map<CourseUnit*, CourseUnitClass*>& getClassesCurrentlyAtending() { return classesCurrentlyAtending; }
	unsigned short int getYear() const { return year; }
	string getStatus() const { return status; }
	double getCredits() const { return credits; }

	//PRINT TO SCREEN
	void show() const;

	//OPERATORS
	friend ofstream& operator<<(ofstream& file, Student *s);
};

#endif

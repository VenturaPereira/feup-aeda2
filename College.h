#pragma once
#ifndef COLLEGE_H
#define COLLEGE_H

#include <string>
#include <vector>

using namespace std;

#include "University.h"

class Course;

class College
{
private:
	//MEMBER VARIABLES
	const string name, acronym;
	vector<Course*> courses;
	University* university;

public:
	//MEMBER FUNCTIONS
	College(string n, string a, University* u) : name(n), acronym(a), university(u) {}
	void addCourse(Course* c);
	void removeCourse(Course* c);

	//GETS
	string getName() const { return name; }
	string getAcronym() const { return acronym; }
	vector<Course*> getCourses() const { return courses; }
	University* getUniversity() const {	return university; }

	
	
};

#endif
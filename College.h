#pragma once
#ifndef COLLEGE_H
#define COLLEGE_H

#include <string>
#include <vector>
using namespace std;

class Course;
class University;

class College
{
private:
	//MEMBER VARIABLES
	const string name, acronym;
	vector<Course*> courses;
	University* university;

public:
	//MEMBER FUNCTIONS
	College(string n, string a, University* u);
	void addCourse(Course* c);
	bool removeCourse(Course* c);
	void show() const;

	//GETS
	string getName() const { return name; }
	string getAcronym() const { return acronym; }
	vector<Course*> getCourses() const { return courses; }
	University* getUniversity() const {	return university; }

	//COMPARES
	friend bool compareCollegeByName(College* c1, College* c2);

	//OPERATORS
	friend ofstream& operator<<(ofstream& file, const College *c);
		
};

#endif
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
	College(string n, string a, University& u);
	void addCourse(Course& c);
	bool removeCourse(Course& c);

	//GETS
	string getName() const { return name; }
	string getAcronym() const { return acronym; }
	vector<Course*>& getCourses() { return courses; }
	University& getUniversity() {	return *university; }

	//COMPARES
	friend bool compareCollegeByName(College* c1, College* c2);

	//PRINT TO SCREEN
	void show() const;

	//OPERATORS
	friend ofstream& operator<<(ofstream& file, College *c);
		
};

#endif
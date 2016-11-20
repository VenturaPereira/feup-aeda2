#pragma once
#ifndef COLLEGE_H
#define COLLEGE_H

#include <string>
#include <vector>
using namespace std;

class Course;
class University;

/*
*	Class for Colleges
*/
class College
{
private:
	//MEMBER VARIABLES
	const string name, acronym;
	vector<Course*> courses;
	University* university;

public:
	//MEMBER FUNCTIONS
	/*!
	*	College Constructor with a given Name, Acronym and University
	*/
	College(string n, string a, University& u);

	/*!
	*	College Destructor
	*/
	~College(){}

	/*!
	*	Adds a Course to the College
	*/
	void addCourse(Course& c);

	/*!
	*	Removes a Course from the College
	*/
	bool removeCourse(Course& c);

	//GETS

	/*!
	*	Returns the name of College
	*/
	string getName() const { return name; }

	/*!
	*	Returns the Acronym of College
	*/
	string getAcronym() const { return acronym; }

	/*!
	*	Returns All Courses from the College
	*/
	vector<Course*>& getCourses() { return courses; }

	/*!
	*	Returns the University from which the College belongs
	*/
	University& getUniversity() {	return *university; }

	//COMPARES

	/*!
	*	Compares Colleges by Name
	*/
	friend bool compareCollegeByName(College* c1, College* c2);

	//PRINT TO SCREEN
	/*!
	*	Prints College in the Screen
	*/
	void show() const;

	//OPERATORS
	/*!
	*	Operator << for saving Data into Files
	*/
	ofstream& operator<<(ofstream& file);
		
};

#endif
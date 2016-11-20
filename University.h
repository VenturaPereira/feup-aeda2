#pragma once
#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <vector>
using namespace std;

class College;
class Course;
class OptionalCourseUnit;

/*
*	Class for Universities
*/
class University
{
private:
	//MEMBER VARIABLES
	const string name, acronym, countryAcronym;
	vector<College*> collegesVector;
	unsigned long long int lastStudentID, lastProfessorID;

public:
	//MEMBER FUNCTIONS
	/*
	*	University Constructor with Name, Acronym and Country Acronym (for email)
	*/
	University(string n, string a, string ca) : name(n), acronym(a), countryAcronym(ca), lastProfessorID(0), lastStudentID(0) {}

	/*
	*	University Constructor with Name, Acronym, Country Acronym (for email), Last Student ID and Last Professor ID
	*/
	University(string n, string a, string ca, unsigned long long int lsid, unsigned long long int lpid) : name(n), acronym(a), countryAcronym(ca), lastProfessorID(lpid), lastStudentID(lsid) {}

	/*
	*	University Destructor
	*/
	~University() {}

	/*
	*	Increments Last Student ID
	*/
	void incrementLastStudentID();

	/*
	*	Increments Last Professor ID
	*/
	void incrementLastProfessorID();

	/*
	*	Adds College to University
	*/
	void addCollege(College& c);

	/*
	*	Removes College from University
	*/
	bool removeCollege(College& c);
	
	//PRINT TO SCREEN
	/*
	*	Prints University in the Screen
	*/
	void show() const;

	/*
	*	Prints All Optional Course Units with the Same Scientific Area, but Not the Same Course Unit as the Argument
	*/
	void showAllOptional(string scientificArea, OptionalCourseUnit& arg) const;
				
	//GETS
	/*
	*	Returns Last Student ID
	*/
	unsigned long long int getLastStudentID() { return lastStudentID; }

	/*
	*	Returns Last Professor ID
	*/
	unsigned long long int getLastProfessorID() { return lastProfessorID; }

	/*
	*	Returns University's Name
	*/
	string getName() const { return name; }

	/*
	*	Returns University's Acronym
	*/
	string getAcronym() const { return acronym; }

	/*
	*	Returns University's Country Acronym
	*/
	string getCountryAcronym() const { return countryAcronym; }

	/*
	*	Returns University's Colleges
	*/
	vector<College*>& getColleges() { return collegesVector; }

	//COMPARES
	/*
	*	Compares Universities by Name
	*/
	friend bool compareUniversityByName(University* u1, University* u2);
	
	//OPERATORS
	/*
	*	Operator << for Saving Purpose
	*/
	ofstream& operator<<(ofstream &file);
};

#endif

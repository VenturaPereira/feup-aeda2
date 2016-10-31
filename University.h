#pragma once
#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <vector>
using namespace std;

class College;

class University
{
private:
	//MEMBER VARIABLES
	const string name, acronym, countryAcronym;
	vector<College*> collegesVector;
	unsigned long long int lastStudentID;

public:
	//MEMBER FUNCTIONS
	University(string n, string a, string ca) : name(n), acronym(a), countryAcronym(ca) { lastStudentID = getLastStudentID(); }
	void incrementLastStudentID();
	void addCollege(College* c);
	void removeCollege(College *c);
		
	//GETS
	unsigned long long int getLastStudentID();
	string getName() const { return name; }
	string getAcronym() const { return acronym; }
	string getCountryAcronym() const { return countryAcronym; }
	vector<College*> getColleges() const { return collegesVector; }
	
};

#endif

#pragma once

#ifndef ENROLLMENTSYSTEM_H
#define ENROLLMENTSYSTEM_H

class University;
class College;
class Course;
class CourseUnit;
class CourseUnitClass;
class Student;
class Tutor;
class Date;

#include <vector>
#include <string>
using namespace std;


class EnrollmentSystem
{
private:
	//MEMBER VARIABLES
	const unsigned int MAXIMUM_CREDITS;
	vector<University*> universitiesVector;

	//SORTING OPTIONS (POINTERS TO THE SORTING FUNCTIONS)
	bool(*universitySortOption)(University* l, University* r);
	bool(*collegeSortOption)(College* l, College* r);
	bool(*courseSortOption)(Course* l, Course* r);
	bool(*courseUnitSortOption)(CourseUnit* l, CourseUnit* r);
	bool(*courseUnitClassSortOption)(CourseUnitClass* l, CourseUnitClass* r);
	bool(*studentsSortOption)(Student* l, Student* r);
	bool(*professorsSortOption)(Tutor* l, Tutor* r);

		
public:
	//MEMBER FUNCTIONS
	EnrollmentSystem(unsigned int mc);
	void addUniversity(University* u) { universitiesVector.push_back(u); }

	//HANDLERS (COMMUNICATION WITH THE USER)
	bool addStudentHandler();

	//TODO - LOAD/SAVE FROM FILES

	//TODO - SORT FUNCTIONS

	//GETS
	unsigned int getMaxCredits() const { return MAXIMUM_CREDITS; }
	vector<University*> getUniversities() const { return universitiesVector; }
	Course* getCourse(string &courseName) const;

};

#endif
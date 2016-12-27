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

/*!
*	Child Class of College User
*/
class Student : public CollegeUser
{
protected:
	//MEMBER VARIABLES
	Course* course;
	map<CourseUnit*, unsigned short int> completedCourseUnits;
	map<CourseUnit*, CourseUnitClass*> classesCurrentlyAtending;
	Tutor* tutor;
	unsigned short int year;
	string personalStatus, collegeStatus;

	/*!
	*	Assign Email to Student
	*/
	virtual void assignEmail();

	/*!
	*	Assign ID to Student
	*/
	virtual void assignID();
public:
	//MEMBER FUNCTIONS
	/*!
	*	Students Constructor with Name, Date of Birth, Course and Status
	*/
	Student(string n, Date dob, Course& c, string s, string ad, unsigned long long int pn);

	/*!
	*	Students Constructor with Name, Date of Birth, Date of Registration, Course, Professor(Tutor), Current Course Year, Credits still Available, Status, Completed Course Units and Course Units Currently Attending
	*/
	Student(string n, Date dob, Date dor, Course& c, Tutor& t, unsigned short int y, string ps, string cs, map<CourseUnit*, unsigned short int> &ccu, map<CourseUnit*, CourseUnitClass*> &cca, unsigned long long int &id, string ad, unsigned long long int pn);
	
	/*!
	*	Students Destructor
	*/
	virtual ~Student() {}

	/*!
	*	Assigns a Tutor to a Student
	*/
	bool assignTutor();

	/*!
	*	Check if Student Completed a Course Unit with a given grade
	*/
	bool completedClass(CourseUnit& courseUnit, unsigned short int grade);
	/*!
	*	Checks if Students Completed all Course Units from that year (given as parameter)
	*/
	bool completedAllCourseUnits(unsigned short int y);

	//COMPARES
	/*!
	*	Compares Students by ID
	*/
	friend bool compareStudentByID(Student* s1, Student* s2);

	/*!
	*	Compares Students by Name
	*/
	friend bool compareStudentByName(Student* s1, Student* s2);

	/*!
	*	Compares Students by Course Year
	*/
	friend bool compareStudentByCouseYear(Student* s1, Student* s2);

	/*!
	*	Compares Students by Birth (Age)
	*/
	friend bool compareStudentByBirth(Student* s1, Student* s2);

	/*!
	*	Compares Students by Date of Registration
	*/
	friend bool compareStudentByRegistration(Student* s1, Student* s2);
		
	//SETS
	/*!
	*	Sets the Personal Status of a Student
	*/
	void setPersonalStatus(string s) { personalStatus = s; }

	/*!
	*	Sets the College Status of a Student
	*/
	void setCollegeStatus(string s) { collegeStatus = s; }

	/*!
	*	Sets the Student Year
	*/
	void setYear(unsigned short int y) { year = y; }

	//GETS
	/*!
	*	Returns the Student's Course
	*/
	Course& getCourse() { return *course; }

	/*!
	*	Returns the Student's Completed Course Units
	*/
	map<CourseUnit*, unsigned short int>& getCompletedCourseUnits() {return completedCourseUnits;}

	/*!
	*	Returns the Student's Currently Atending Classes
	*/
	map<CourseUnit*, CourseUnitClass*>& getClassesCurrentlyAtending() { return classesCurrentlyAtending; }

	/*!
	*	Returns the Student's Currently Atending Course Units
	*/
	vector<CourseUnit*> getCourseUnitsAttending();

	/*!
	*	Returns the Student's Year
	*/
	unsigned short int getYear() const { return year; }

	/*!
	*	Returns the Student' Personal Status
	*/
	string getPersonalStatus() const { return personalStatus; }
	
	/*!
	*	Returns the Student' College Status
	*/
	string getCollegeStatus() const { return collegeStatus; }

	//PRINT TO SCREEN
	/*!
	*	Prints Student to the Screen
	*/
	void show() const;

	/*!
	*	Prints Student In Detail to the Screen
	*/
	void showInDetail() const;

	//OPERATORS
	/*!
	*	Operator << for saving Student into Files
	*/
	ofstream& operator<<(ofstream& file);
};

#endif

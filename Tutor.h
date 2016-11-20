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

/*!
 *	Child Class of Parent CollegeUser. Class for Professors
 */
class Tutor : public CollegeUser
{
private:
	//MEMBER VARIABLES
	Course* course;
	vector<CourseUnit*> ableToTeach, currentlyTeaching;
	vector<Student*> students;

	//MEMBER FUNCTIONS
	/*!
	 *	Assigns Email To Professor
	 */
	virtual void assignEmail();

	/*!
	*	Assigns ID to Professor
	*/
	virtual void assignID();
public:
	//MEMBER FUNCTIONS
	/*!
	 *	Tutor Constructor with Name, Date of Birth, Course and Course Units Able to Teach
	 */
	Tutor(string n, Date dob, Course& c, vector<CourseUnit*>& att);

	/*!
	*	Tutor Constructor with Name, Date of Birth, Date of Registration, Course, ID, Course Units Currently Teaching and Course Units Able to Teach
	*/
	Tutor(string n, Date dob, Date dor, Course& c, unsigned long long int &ID, vector<CourseUnit*> &ct, vector<CourseUnit*> &att); 
	
	/*!
	*	Tutor Destructor
	*/
	virtual ~Tutor() {}

	/*!
	*	Sets Professor Teaching this Course Unit Class unless He/She isn't able to teach this Course Unit
	*/
	bool teachClass(CourseUnitClass& c);

	/*!
	*	Sets Professor as a Tutor for the given Student
	*/
	void tutorStudent(Student& s);

	//COMPARES

	/*!
	*	Compares Professors by Name
	*/
	friend bool compareProfessorByName(Tutor* p1, Tutor* p2);

	/*!
	*	Compares Professors by ID
	*/
	friend bool compareProfessorByID(Tutor* p1, Tutor* p2);

	/*!
	*	Compares Professors by Age (Date of Birth)
	*/
	friend bool compareProfessorByBirth(Tutor* p1, Tutor* p2);

	/*!
	*	Compares Professors by Date of Registration
	*/
	friend bool compareProfessorByRegistration(Tutor* p1, Tutor* p2);

	//GETS

	/*!
	*	Returns Professor's Course
	*/
	Course& getCourse() { return *course; }

	/*!
	*	Returns Professor's Able to Teach Course Units
	*/
	vector<CourseUnit*>& getAbleToTeach() { return ableToTeach; }

	/*!
	*	Returns Professor's Currently Teaching Course Units
	*/
	vector<CourseUnit*>& getCurrentlyTeaching() { return currentlyTeaching; }

	/*!
	*	Returns Professor's Students
	*/
	vector<Student*>& getStudents() { return students; }

	//PRINT TO SCREEN
	/*!
	*	Prints Professor in the Screen
	*/
	void show() const;
	
	//OPERATORS
	/*!
	*	Operator << for saving purposes
	*/
	ofstream& operator<<(ofstream& file);
};

#endif


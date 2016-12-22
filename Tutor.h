#pragma once

#ifndef TUTOR_H
#define TUTOR_H

#include "CollegeUser.h"
#include "Meeting.h"
#include <vector>
#include <set>
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
	set<Meeting> meetings;

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

	bool isTutorOf(Student& s);

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

	//MEETINGS
	/*!
	*	Tries to add a meeting. Returns the success/failure.
	*/
	bool addMeeting(Meeting &m);

	/*!
	*	Tries to remove a meeting. Returns the success/failure.
	*/
	bool removeMeeting(Meeting &m);

	/*!
	*	Prints all the occured meetings
	*/
	void showMeetingsOccured() const;

	/*!
	*	Prints all the upcoming meetings
	*/
	void showMeetingsUpcoming() const;

	/*!
	*	Prints all the upcoming meetings in a period of time
	*/
	void showMeetingsUpcoming(const Date &begin, const Date &end) const;


};

#endif


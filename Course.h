#pragma once
#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>
using namespace std;

class College;
class Tutor;
class CourseUnit;
class Student;

/*
*	Class for Course
*/
class Course
{
private:
	//MEMBER VARIABLES
	const string name, acronym;
	vector<CourseUnit*> courseUnits;
	vector<Student*> students;
	vector<Tutor*> professors;
	College* college;

public:
	//MEMBER FUNCTIONS
	/*!
	*	Course Constructor with Name, Acronym and College
	*/
	Course(string n, string a, College& c);

	/*!
	*	Course Destructor
	*/
	~Course() {}

	/*!
	*	Adds Course Unit to Course
	*/
	void addCourseUnit(CourseUnit& cu);

	/*!
	*	Removes Course Unit from Course
	*/
	bool removeCourseUnit(CourseUnit& cu);

	/*!
	*	Adds Student to Course
	*/
	void addStudent(Student& s);

	/*!
	*	Removes Student from Course
	*/
	bool removeStudent(Student& s);

	/*!
	*	Adds Professor to Course
	*/
	void addProfessor(Tutor& p);

	/*!
	*	Removes Professor from Course
	*/
	bool removeProfessor(Tutor& p);

	//COMPARES
	/*!
	*	Compares Courses by Name
	*/
	friend bool compareCourseByName(Course* c1, Course* c2);


	//GETS
	/*!
	*	Returns the Course Name
	*/
	string getName() const { return name; }

	/*!
	*	Returns the Course Acronym
	*/
	string getAcronym() const { return acronym; }

	/*!
	*	Returns the Course Units from the Course
	*/
	vector<CourseUnit*>& getCourseUnits() { return courseUnits; }

	/*!
	*	Returns the Course' Students
	*/
	vector<Student*>& getStudents() { return students; }

	/*!
	*	Returns the Course' Professors
	*/
	vector<Tutor*>& getProfessors() { return professors; }

	/*!
	*	Returns the Course' College
	*/
	College& getCollege() { return *college; }

	/*!
	*	Returns the Course Units of the Course from a given year
	*/
	vector<CourseUnit*> getCourseUnits(unsigned short int y);

	/*!
	*	Returns the Course Units not Completed from a Student in a given year
	*/
	vector<CourseUnit*> getCourseUnitsNotCompleted(Student& s, unsigned short int y);

	//PRINT TO SCREEN

	/*!
	*	Prints a Course into the Screen
	*/
	void show() const;
	
	//OPERATORS
	/*!
	*	Operator << for saving purposes
	*/
	ofstream& operator<<(ofstream &file);
};

#endif
#pragma once
#ifndef COURSEUNITCLASS_H
#define COURSEUNITCLASS_H

#include <vector>
#include <string>
using namespace std;

class CourseUnit;
class Tutor;
class Student;

/*!
*	Class for Course Units Classes
*/
class CourseUnitClass 
{
private:
	//MEMBER VARIABLES
	const unsigned short int classNumber;
	vector<Student*> studentsInClass;
	CourseUnit* courseUnit;
	Tutor* professor;

	/*!
	*	Assigns Professor to Class
	*/
	void assignTeacher();
public:
	//MEMBER FUNCTIONS
	/*!
	*	Course Unit Class Constructor with Class Number and Course Unit
	*/
	CourseUnitClass(unsigned short int cn, CourseUnit& cu);

	/*!
	*	Course Unit Class Constructor with Class Number, Course Unit and Professor(Tutor)
	*/
	CourseUnitClass(unsigned short int cn, CourseUnit& cu, Tutor& t);
	
	/*!
	*	Course Unit Class Destructor
	*/
	~CourseUnitClass() {}

	/*!
	*	Add Student to Class
	*/
	void addStudent(Student& s);

	/*!
	*	Remove Student from Class
	*/
	bool removeStudent(Student& s);

	/*!
	*	Sets Professor to Class
	*/
	void setProfessor(Tutor& t);

	//COMPARES
	/*!
	*	Compares Classes by Class Number
	*/
	friend bool compareCourseUnitClassByNumber(CourseUnitClass* cuc1, CourseUnitClass* cuc2);

	/*!
	*	Compares Classes by Number of Students
	*/
	friend bool compareCourseUnitClassByNumberStudents(CourseUnitClass* cuc1, CourseUnitClass* cuc2);

	//GETS
	/*!
	*	Returns Number of Students in Class
	*/
	unsigned short int getNumberOfStudents() const { return studentsInClass.size(); }

	/*!
	*	Returns Class Number
	*/
	unsigned short int getClassNumber() const { return classNumber; }

	/*!
	*	Returns Students in Class
	*/
	vector<Student*>& getStudentsInClass() { return studentsInClass; }

	/*!
	*	Returns Course Unit
	*/
	CourseUnit& getCourseUnit() {return *courseUnit;}

	//OPERATORS
	/*!
	*	Operator << for Saving purposes
	*/
	ofstream& operator<<(ofstream& file);

	//PRINT TO SCREEN
	/*!
	*	Prints Class to the Screen
	*/
	void show() const;
};

#endif

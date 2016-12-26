#pragma once

#ifndef COURSEUNIT_H
#define COURSEUNIT_H

#include <string>
#include <vector>
#include <queue>

class Course;
class Student;
class Tutor;
class CourseUnitClass;

using namespace std;

/*!
*	Parent Class Course Unit -> Childs: Mandatory and Optional
*/
class CourseUnit
{
protected:
	//MEMBER VARIABLES
	const unsigned short int year, semester;
	const string name, acronym;
	const double credits;
	Course* course;
	vector<Student*> studentsCurrentlyInCourseUnit;
	vector<Tutor*> courseUnitProfessors;
	priority_queue<CourseUnitClass*> classes;

public:
	//MEMBER FUNCTIONS
	/*!
	*	Course Unit Constructor with Name, Acronym, Course, Year, Semester and Credits 
	*/
	CourseUnit(string n, string a, Course& c, unsigned short int y, unsigned short int s, double credits);

	/*!
	*	Course Unit Destructor
	*/
	virtual ~CourseUnit() {}

	/*!
	*	Adds Student to Course Unit
	*/
	void addStudent(Student& s);

	/*!
	*	Removes Student from Course Unit
	*/
	bool removeStudent(Student& s);

	/*!
	*	Add Professor to Course Unit
	*/
	void addProfessor(Tutor& t);

	/*!
	*	Removes Professor from Course Unit
	*/
	bool removeProfessor(Tutor& t);

	/*!
	*	Adds Class to Course Unit
	*/
	void addCourseUnitClass(CourseUnitClass& cuc);

	/*!
	*	Removes Class from Course Unit
	*/
	bool removeCourseUnitClass(CourseUnitClass& cuc);

		
	//COMPARES
	/*!
	*	Compares Course Units by Number of Students
	*/
	friend bool compareCourseUnitByNumberStudents(CourseUnit* cu1, CourseUnit* cu2);

	/*!
	*	Compares Course Units by Name
	*/
	friend bool compareCourseUnitByName(CourseUnit* cu1, CourseUnit* cu2);

	/*!
	*	Compares Course Units by Position in the Plan of the Course
	*/
	friend bool compareCourseUnitByTime(CourseUnit* cu1, CourseUnit* cu2);
	
	//GETS
	/*!
	*	Returns Number of Students in the Course Unit
	*/
	unsigned int getNumberOfStudents() const {return studentsCurrentlyInCourseUnit.size();}

	/*!
	*	Returns Number of Classes in the Course Unit
	*/
	unsigned short int getNumberClasses() const { return classes.size(); }

	/*!
	*	Returns Year of the Course Unit
	*/
	unsigned short int getYear() const { return year; }

	/*!
	*	Returns Semester of the Course Unit
	*/
	unsigned short int getSemester() const { return semester; }

	/*!
	*	Returns Credits of the Course Unit
	*/
	double getCredits() const { return credits; }

	/*!
	*	Returns Name of Course Unit
	*/
	string getName() const { return name; }

	/*!
	*	Returns Acronym of Course Unit
	*/
	string getAcronym() const { return acronym; }

	/*!
	*	Returns Classes in the Course Unit
	*/
	priority_queue<CourseUnitClass*>& getClasses() { return classes; }

	/*!
	*	Returns Students in the Course Unit
	*/
	vector<Student*>& getStudentsCurrentlyInCourseUnit() { return studentsCurrentlyInCourseUnit; }

	/*!
	*	Returns Professors in the Course Unit
	*/
	vector<Tutor*>& getCourseUnitProfessors() { return courseUnitProfessors; }

	/*!
	*	Returns Course of the Course Unit
	*/
	Course& getCourse() { return *course; }

	//PRINT TO SCREEN
	/*!
	*	Prints Course Unit to Screen -> Variants in Child Classes
	*/
	virtual void show() const = 0;

	/*!
	*	Prints Course Unit to Screen In Detail -> Variants in Child Classes
	*/
	virtual void showInDetail() const = 0;

	//OPERATORS
	/*!
	*	Operator << for Saving Purposes -> Variants in Child Classes
	*/
	virtual ofstream& operator<<(ofstream& file) = 0;

	/*!
	*	Checks if it's Possible for a Student to Enroll this Course Unit
	*/
	virtual bool possibleToEnroll() = 0;

	/*!
	*	Enrolls a Student in this Course Unit (and in a class with free room)
	*/
	virtual void enrollStudent(Student &s) = 0;
};

/*!
*	Child Class of Course Unit for Optional Course Units
*/
class OptionalCourseUnit : public CourseUnit
{
private:
	//MEMBER VARIABLES
	const string scientificArea;
	const unsigned short int MAXIMUM_NUMBER_OF_STUDENTS;

public:
	//MEMBER FUNCTIONS
	/*!
	*	Optional Course Unit Constructor with Maximum Number of Students, Name, Acronym, Course, Year, Semester, Scientif Area and Credits
	*/
	OptionalCourseUnit(unsigned int mnos, string n, string a, Course& c, unsigned short int y, unsigned short int s, string sa, double cred);

	/*!
	*	Optional Course Units Destructor
	*/
	virtual ~OptionalCourseUnit() {}

	//GETS
	/*!
	*	Returns Maximum Students of the Course Unit
	*/
	unsigned short int getMaxStudents() const { return MAXIMUM_NUMBER_OF_STUDENTS; }

	/*!
	*	Returns Scientific Area of the Course Unit
	*/
	string getScientificArea() const { return scientificArea; }

	//OPERATORS
	/*!
	*	Operator << for saving purposes
	*/
	virtual ofstream& operator<<(ofstream& file);

	//PRINT TO SCREEN
	/*!
	*	Prints Optional Course Unit in the Screen
	*/
	virtual void show() const;

	/*!
	*	Prints Optional Course Unit to Screen In Detail
	*/
	virtual void showInDetail() const;

	/*!
	*	Checks if it's Possible for a Student to Enroll this Course Unit
	*/
	virtual bool possibleToEnroll();

	/*!
	*	Enrolls a Student in this Course Unit (and in a class with free room)
	*/
	virtual void enrollStudent(Student &s);
};

/*!
*	Child Class of Course Unit for Mandatory Course Units
*/
class MandatoryCourseUnit : public CourseUnit
{
private:
	//MEMBER VARIABLES
	const unsigned int MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS;

public:
	//MEMBER FUNCTIONS
	/*!
	*	Mandatory Course Unit Constructor with Maximum Number of Students per Class, Name, Acronym, Course, Year, Semester and Credits
	*/
	MandatoryCourseUnit(unsigned int mnospc, string n, string a, Course& c, unsigned short int y, unsigned short int s, double cred);

	/*!
	*	Mandatory Course Unit Destructor
	*/
	virtual ~MandatoryCourseUnit() {}

	//GETS
	/*!
	*	Returns Maximum Students per Class of the Course Unit
	*/
	unsigned int getMaxStudentsPerClass() const { return MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS; }

	//OPERATORS
	/*!
	*	Operator << for Saving purposes
	*/
	virtual ofstream& operator<<(ofstream& file);

	//PRINT TO SCREEN
	/*!
	*	Prints Mandatory Course Unit in the Screen
	*/
	virtual void show() const;

	/*!
	*	Prints Mandatory Course Unit to Screen In Detail
	*/
	virtual void showInDetail() const;

	/*!
	*	Checks if it's Possible for a Student to Enroll this Course Unit
	*/
	virtual bool possibleToEnroll();

	/*!
	*	Enrolls a Student in this Course Unit (and in a class with free room)
	*/
	virtual void enrollStudent(Student &s);
};

#endif


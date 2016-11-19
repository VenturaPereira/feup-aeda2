#pragma once

#ifndef COURSEUNIT_H
#define COURSEUNIT_H

#include <string>
#include <vector>

class Course;
class Student;
class Tutor;
class CourseUnitClass;

using namespace std;

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
	vector<CourseUnitClass*> classes;

public:
	//MEMBER FUNCTIONS
	CourseUnit(string n, string a, Course& c, unsigned short int y, unsigned short int s, double credits);
	virtual bool addStudent(Student& s) = 0;
	bool removeStudent(Student& s);
	void addProfessor(Tutor& t);
	bool removeProfessor(Tutor& t);
	void addCourseUnitClass(CourseUnitClass& cuc);
	bool removeCourseUnitClass(CourseUnitClass& cuc);
	void addStudentWithoutCheck(Student& s);
			
	//COMPARES
	friend bool compareCourseUnitByNumberStudents(CourseUnit* cu1, CourseUnit* cu2);
	friend bool compareCourseUnitByName(CourseUnit* cu1, CourseUnit* cu2);
	friend bool compareCourseUnitByTime(CourseUnit* cu1, CourseUnit* cu2);
	
	//GETS
	unsigned int getNumberOfStudents() const {return studentsCurrentlyInCourseUnit.size();}
	unsigned short int getNumberClasses() const { return classes.size(); }
	unsigned short int getYear() const { return year; }
	unsigned short int getSemester() const { return semester; }
	double getCredits() const { return credits; }
	string getName() const { return name; }
	string getAcronym() const { return acronym; }
	vector<CourseUnitClass*>& getClasses() { return classes; }
	vector<Student*>& getStudentsCurrentlyInCourseUnit() { return studentsCurrentlyInCourseUnit; }
	vector<Tutor*>& getCourseUnitProfessors() { return courseUnitProfessors; }
	Course& getCourse() { return *course; }

	//PRINT TO SCREEN
	virtual void show() const = 0;

	//OPERATORS
	virtual ofstream& operator<<(ofstream& file) = 0;
};



class OptionalCourseUnit : public CourseUnit
{
private:
	//MEMBER VARIABLES
	const string scientificArea;
	const unsigned short int MAXIMUM_NUMBER_OF_STUDENTS;

public:
	//MEMBER FUNCTIONS
	OptionalCourseUnit(unsigned int mnos, string n, string a, Course& c, unsigned short int y, unsigned short int s, string sa, double cred);
	virtual bool addStudent(Student& s);

	//GETS
	unsigned short int getMaxStudents() const { return MAXIMUM_NUMBER_OF_STUDENTS; }
	string getScientificArea() const { return scientificArea; }

	//OPERATORS
	virtual ofstream& operator<<(ofstream& file);

	//PRINT TO SCREEN
	virtual void show() const;
};


class MandatoryCourseUnit : public CourseUnit
{
private:
	//MEMBER VARIABLES
	const unsigned int MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS;

public:
	//MEMBER FUNCTIONS
	MandatoryCourseUnit(unsigned int mnospc, string n, string a, Course& c, unsigned short int y, unsigned short int s, double cred);
	virtual bool addStudent(Student& s);

	//GETS
	unsigned int getMaxStudentsPerClass() const { return MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS; }

	//OPERATORS
	virtual ofstream& operator<<(ofstream& file);

	//PRINT TO SCREEN
	virtual void show() const;
};

#endif


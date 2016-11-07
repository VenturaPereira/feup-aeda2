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
	Course* course;
	vector<Student*> studentsCurrentlyInCourseUnit;
	vector<Tutor*> courseUnitProfessors;
	vector<CourseUnitClass*> classes;

public:
	//MEMBER FUNCTIONS
	CourseUnit(string n, string a, Course* c, unsigned short int y, unsigned short int s);
	virtual bool addStudent(Student* s) = 0;
	bool removeStudent(Student* s);
	void addProfessor(Tutor* t);
	bool removeProfessor(Tutor* t);
	void addCourseUnitClass(CourseUnitClass* cuc);
	bool removeCourseUnitClass(CourseUnitClass* cuc);
			

	//GETS
	unsigned int getNumberOfStudents() const {return studentsCurrentlyInCourseUnit.size();}
	unsigned short int getNumberClasses() const { return classes.size(); }
	string getName() const { return name; }
	vector<CourseUnitClass*> getClasses() const { return classes; }
	vector<Student*> getStudentsCurrentlyInCourseUnit() const { return studentsCurrentlyInCourseUnit; }
	vector<Tutor*> getCourseUnitProfessors() const { return courseUnitProfessors; }
	Course* getCourse() const { return course; }

};



class OptionalCourseUnit : public CourseUnit
{
private:
	//MEMBER VARIABLES
	const string scientificArea;
	const unsigned short int MAXIMUM_NUMBER_OF_STUDENTS;

public:
	//MEMBER FUNCTIONS
	OptionalCourseUnit(unsigned int mnos, string n, string a, Course* c, unsigned short int y, unsigned short int s, string sa);
	virtual bool addStudent(Student* s);

	//GETS
	unsigned short int getMaxStudents() const { return MAXIMUM_NUMBER_OF_STUDENTS; }

};


class MandatoryCourseUnit : public CourseUnit
{
private:
	//MEMBER VARIABLES
	const unsigned int MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS;

public:
	//MEMBER FUNCTIONS
	MandatoryCourseUnit(unsigned int mnospc, string n, string a, Course* c, unsigned short int y, unsigned short int s);
	virtual bool addStudent(Student* s);

	//GETS
	unsigned int getMaxStudentsPerClass() const { return MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS; }

};

#endif


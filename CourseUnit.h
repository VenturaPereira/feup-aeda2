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
private:
	//MEMBER VARIABLES
	const unsigned short int MAXIMUM_NUMBER_OF_STUDENTS, MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS;
	const string name, acronym;
	unsigned short int numberOfStudents;
	Course* course;
	vector<Student*> studentsCurrentlyInCourseUnit;
	vector<Tutor*> courseUnitProfessors;
	vector<CourseUnitClass*> classes;

public:
	//MEMBER FUNCTIONS
	CourseUnit(unsigned short int mnos, unsigned short int mnospc, string n, string a, Course* c) :
		MAXIMUM_NUMBER_OF_STUDENTS(mnos),
		MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS(mnospc),
		name(n),
		acronym(a),
		course(c) {}
	void addStudent(Student* s);
	bool removeStudent(Student* s);
	void addProfessor(Tutor* t);
	bool removeProfessor(Tutor* t);
	void addCourseUnitClass(CourseUnitClass* cuc);
	bool removeCourseUnitClass(CourseUnitClass* cuc);
	friend int compareNumberStudents(CourseUnit & Cu1, CourseUnit & Cu2);
	friend bool compareCourseUnitName(CourseUnit & Cu1, CourseUnit & Cu2);
	//GETS
	unsigned short int getMaxStudents() const { return MAXIMUM_NUMBER_OF_STUDENTS; }
	unsigned short int getMaxStudentsPerClass() const { return MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS; }
	unsigned short int getNumberOfStudents() const {return numberOfStudents;}
	unsigned short int getNumberClasses() const { return classes.size(); }
	vector<CourseUnitClass*> getClasses() const { return classes; }
	vector<Student*> getStudentsCurrentlyInCourseUnit() const { return studentsCurrentlyInCourseUnit; }
	vector<Tutor*> getCourseUnitProfessors() const { return courseUnitProfessors; }
	Course* getCourse() const { return course; }

};
#endif


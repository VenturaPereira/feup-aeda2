#pragma once

#ifndef COURSEUNIT_H
#define COURSEUNIT_H

#include <string>
#include <vector>

class Course;
class Student;
class Tutor;

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
	CourseUnit(unsigned short int mnos, unsigned short int mnospc, string n, string a, Course* c);
	bool addStudent(Student* s);
	void removeStudent(Student* s);
	void addProfessor(Tutor* t);
	void removeProfessor(Tutor* t);
	void addCourseUnitClass(CourseUnitClass* cuc);
	void removeCourseUnitClass(CourseUnitClass* cuc);
			

	//GETS
	unsigned short int getMaxStudents() const { return MAXIMUM_NUMBER_OF_STUDENTS; }
	unsigned short int getMaxStudentsPerClass() const { return MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS; }
	vector<CourseUnitClass*> getClasses() const { return classes; }
	vector<Student*> getStudentsCurrentlyInCourseUnit() const { return studentsCurrentlyInCourseUnit; }
	vector<Tutor*> getCourseUnitProfessors() const { return courseUnitProfessors; }
	Course* getCourse() const { return course; }

};
#endif


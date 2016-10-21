#pragma once

#ifndef COURSEUNIT_H
#define COURSEUNIT_H

#include <string>

class Course;
class Student;
class Tutor;

using namespace std;

class CourseUnit
{
	friend class Student;
	friend class Course;
	friend class CourseUnitClass;

	const unsigned short int MAXIMUM_NUMBER_OF_STUDENTS; 
	const unsigned short int MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS;
	unsigned short int numberOfStudents;
	string courseUnitName, courseUnitAcronym;
	Course* course;
	vector<Student*> studentsCurrentlyInCourseUnit;
	vector<Tutor*> courseUnitProfessors;
	vector<CourseUnitClass*> classes;
public:
	unsigned short int getMaxStudents() const { return MAXIMUM_NUMBER_OF_STUDENTS; }
	unsigned short int getMaxStudentsPerClass() const { return MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS; }
	vector<CourseUnitClass*> getClasses() const { return classes; }
};
#endif


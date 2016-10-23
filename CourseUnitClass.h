#pragma once
#ifndef COURSEUNITCLASS_H
#define COURSEUNITCLASS_H

#include "CourseUnit.h"

class CourseUnitClass : public CourseUnit
{
private:
	//MEMBER VARIABLES
	const unsigned short int classNumber;
	unsigned short int numberOfStudents;
	vector<Student*> studentsInClass;
	CourseUnit* courseUnit;
	
public:
	//MEMBER FUNCTIONS
	CourseUnitClass(CourseUnit* cu, unsigned short int cn);
	void addStudent(Student* s);
	bool removeStudent(Student* s);


	//GETS
	unsigned short int getNumberOfStudents() const { return numberOfStudents; }
	unsigned short int getClassNumber() const { return classNumber; }
	vector<Student*> getStudentsInClass() const { return studentsInClass; }
	CourseUnit* getCourseUnit() const { return courseUnit;}
};

#endif

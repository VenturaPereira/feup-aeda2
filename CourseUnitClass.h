#pragma once
#ifndef COURSEUNITCLASS_H
#define COURSEUNITCLASS_H

#include "CourseUnit.h"

class CourseUnitClass : public CourseUnit
{
	unsigned short int classNumber, numberOfStudents;
	vector<Student*> studentsInClass;
	CourseUnit* courseUnit;

public:
	CourseUnitClass(CourseUnit* cu, unsigned short int cn);
	unsigned short int getNumberOfStudents() const;
	vector<Student*> getStudentsInClass() const;
	void addStudent(const Student* s); 
};

#endif

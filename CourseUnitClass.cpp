#pragma once

#include "CourseUnitClass.h"

void CourseUnitClass::addStudent(const Student* s)
{
	studentsInClass.push_back(s);
	numberOfStudents = studentsInClass.size();
}




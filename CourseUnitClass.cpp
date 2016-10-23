#pragma once

#include "CourseUnitClass.h"


void CourseUnitClass::addStudent(Student* s)
{
	studentsInClass.push_back(s);
	numberOfStudents = studentsInClass.size();
}

bool CourseUnitClass::removeStudent(Student* s) {
	for (vector<Student *> ::const_iterator it = studentsInClass.begin(); it != studentsInClass.end(); it++) {
		if ((*it) == s) {
			studentsInClass.erase(it);
			return true;
		}
	}
	return false;
}


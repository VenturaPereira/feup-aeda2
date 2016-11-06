#pragma once

#include "CourseUnitClass.h"


void CourseUnitClass::addStudent(Student* s)
{
	studentsInClass.push_back(s);
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

void CourseUnitClass::setProfessor(Tutor* t)
{
	professor = t;
}


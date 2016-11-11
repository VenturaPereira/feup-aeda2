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

void CourseUnitClass::setProfessor(Tutor* t)
{
	professor = t;
}
int compareClassCrowd(CourseUnitClass & cc1, CourseUnitClass cc2) {
	int result = cc1.getNumberOfStudents() - cc2.getNumberOfStudents();
	if (result == 0) {
		return 0; // mesmo numero de alunos
	}
	else if (result > 0) {
		return 1;
	}
	else {
		return -1;
	}
}

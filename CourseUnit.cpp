#pragma once

#include "CourseUnit.h"

void CourseUnit::addStudent(Student* s)
{
	studentsCurrentlyInCourseUnit.push_back(s);
}

bool CourseUnit::removeStudent(Student* s)
{
	for (vector<Student *> ::const_iterator it = studentsCurrentlyInCourseUnit.begin();
		it != studentsCurrentlyInCourseUnit.end();
		it++)
	{
		if ((*it) == s)
		{
			studentsCurrentlyInCourseUnit.erase(it);
			return true;
		}
	}
	return false;
}

void CourseUnit::addProfessor(Tutor* t)
{
	courseUnitProfessors.push_back(t);
}

bool CourseUnit::removeProfessor(Tutor* t)
{
	for (vector<Tutor *> ::const_iterator it = courseUnitProfessors.begin();
		it != courseUnitProfessors.end();
		it++)
	{
		if ((*it) == t)
		{
			courseUnitProfessors.erase(it);
			return true;
		}
	}
	return false;
}

void CourseUnit::addCourseUnitClass(CourseUnitClass* cuc)
{
	classes.push_back(cuc);
}

bool CourseUnit::removeCourseUnitClass(CourseUnitClass* cuc)
{
	for (vector<CourseUnitClass *> ::const_iterator it = classes.begin();
		it != classes.end();
		it++)
	{
		if ((*it) == cuc)
		{
			classes.erase(it);
			return true;
		}
	}
	return false;
}
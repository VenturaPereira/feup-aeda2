#pragma once

#include "Course.h"

void Course::addCourseUnit(CourseUnit* cu)
{
	courseUnits.push_back(cu);
}

bool Course::removeCourseUnit(CourseUnit* cu)
{
	for (vector<CourseUnit *> ::const_iterator it = courseUnits.begin();
		it != courseUnits.end();
		it++)
	{
		if ((*it) == cu)
		{
			courseUnits.erase(it);
			return true;
		}
	}
	return false;
}

void Course::addStudent(Student* s)
{
	students.push_back(s);
}

bool Course::removeStudent(Student* s)
{
	for (vector<Student *> ::const_iterator it = students.begin();
		it != students.end();
		it++)
	{
		if ((*it) == s)
		{
			students.erase(it);
			return true;
		}
	}
	return false;
}

void Course::addProfessor(Tutor* p)
{
	professors.push_back(p);
}

bool Course::removeProfessor(Tutor* p)
{
	for (vector<Tutor *> ::const_iterator it = professors.begin();
		it != professors.end();
		it++)
	{
		if ((*it) == p)
		{
			professors.erase(it);
			return true;
		}
	}
	return false;
}
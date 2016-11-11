#pragma once

#include "Course.h"
#include "Student.h"
#include "CourseUnit.h"
#include "Utilities.h"

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

vector<CourseUnit*> Course::getCourseUnits(unsigned short int y)
{
	vector<CourseUnit*> courseUnits;

	if (y >= 1 && y <= 5)
	{
		//GATHER ALL THE COURSE UNITS FROM THE YEAR 
		vector<CourseUnit*>::const_iterator cuIt;
		for (cuIt = courseUnits.begin();
			cuIt != courseUnits.end();
			cuIt++)
		{
			if ((*cuIt)->getYear() == y) //SAME YEAR AS ARGUMENT
			{
				courseUnits.push_back(*cuIt);
			}
		}
	}

	return courseUnits;
}

vector<CourseUnit*> Course::getCourseUnitsNotCompleted(Student* s, unsigned short int y)
{
	vector<CourseUnit*> courseUnitsFromYear, notCompleted;
	
	if (y >= 1 && y <= 5)
	{
		//GATHER ALL THE COURSE UNITS FROM THE YEAR 
		courseUnitsFromYear = getCourseUnits(y);
		
		//CHECK WHAT COURSE UNITS HAVE NOT BEEN COMPLETED
		vector<CourseUnit*>::const_iterator cuIt;
		for (cuIt = courseUnitsFromYear.begin();
			cuIt != courseUnitsFromYear.end();
			cuIt++)
		{
			if (//CHECK IF ALREADY ATENDING THE COURSE UNIT OR IF THE STUDENT HAS ALREADY COMPLETED THE COURSE UNIT
				s->getClassesCurrentlyAtending().find((*cuIt)) == s->getClassesCurrentlyAtending().end()					
				&& s->getCompletedCourseUnits().find((*cuIt)) == s->getCompletedCourseUnits().end()
				)
			{
				notCompleted.push_back(*cuIt); //IF NOT TO BOTH, ADD TO NOTCOMPLETED
			}
		}

	}

	return notCompleted;
}

bool compareCourseByName(Course* c1, Course* c2) 
{
	return (c1->getName() < c2->getName());
}

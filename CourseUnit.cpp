#pragma once

#include <iostream>
#include "CourseUnit.h"
#include "Course.h"
#include "College.h"
#include "University.h"

CourseUnit::CourseUnit(string n, string a, Course* c, unsigned short int y, unsigned short int s, double credits)
	: name(n), acronym(a), year(y), semester(s), credits(credits), course(c)
{
	c->addCourseUnit(this);
}

OptionalCourseUnit::OptionalCourseUnit(unsigned int mnos, string n, string a, Course* c, unsigned short int y, unsigned short int s, string sa, unsigned int cred)
	: CourseUnit(n,a,c,y,s,cred), MAXIMUM_NUMBER_OF_STUDENTS(mnos), scientificArea(sa)
{

}

MandatoryCourseUnit::MandatoryCourseUnit(unsigned int mnospc, string n, string a, Course* c, unsigned short int y, unsigned short int s, unsigned int cred)
	: CourseUnit(n, a, c, y, s, cred), MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS(mnospc)
{

}

bool OptionalCourseUnit::addStudent(Student* s)
{
	if (getNumberOfStudents() >= MAXIMUM_NUMBER_OF_STUDENTS) {
		return false;
	}
	studentsCurrentlyInCourseUnit.push_back(s);
	return true;
}

bool MandatoryCourseUnit::addStudent(Student* s)
{
	studentsCurrentlyInCourseUnit.push_back(s);
	return true;
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

void OptionalCourseUnit::show() const
{
	cout << name << '\t'
		<< acronym << '\t'
		<< "Optional" << '\t'
		<< scientificArea << '\t'
		<< this->getNumberOfStudents()  << '/' << MAXIMUM_NUMBER_OF_STUDENTS << '\n';
		
}

void MandatoryCourseUnit::show() const
{
	cout << name << '\t'
		<< acronym << '\t'
		<< "Mandatory" << '\n';
}

bool compareCourseUnitByNumberStudents(CourseUnit* cu1, CourseUnit* cu2)
{
	return (cu1->getNumberOfStudents() < cu2->getNumberOfStudents());
}

bool compareCourseUnitByName(CourseUnit* cu1, CourseUnit* cu2)
{
	return (cu1->name < cu2->name);
}

bool compareCourseUnitByTime(CourseUnit* cu1, CourseUnit* cu2)
{
	if (cu1->year < cu2->year)
		return true;
	else if (cu1->year > cu2->year)
		return false;
	else return (cu1->semester < cu2->semester);
}
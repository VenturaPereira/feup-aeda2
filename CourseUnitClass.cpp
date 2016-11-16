#pragma once

#include "CourseUnitClass.h"
#include "CourseUnit.h"
#include "College.h"
#include "Course.h"
#include "University.h"
#include "Tutor.h"
#include <fstream>

CourseUnitClass::CourseUnitClass(unsigned short int cn, CourseUnit* cu) : courseUnit(cu), classNumber(cn) {
	cu->addCourseUnitClass(this);
}

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

bool compareCourseUnitClassByNumber(CourseUnitClass* cuc1, CourseUnitClass* cuc2)
{
	return (cuc1->classNumber < cuc2->classNumber);
}

bool compareCourseUnitClassByNumberStudents(CourseUnitClass* cuc1, CourseUnitClass* cuc2)
{
	return (cuc1->getNumberOfStudents() < cuc2->getNumberOfStudents());
}

ofstream& operator<<(ofstream& file, const CourseUnitClass *cuc)
{
	file << cuc->getCourseUnit()->getCourse()->getCollege()->getUniversity()->getAcronym()
		<< ';'
		<< cuc->getCourseUnit()->getCourse()->getCollege()->getAcronym()
		<< ';'
		<< cuc->getCourseUnit()->getCourse()->getAcronym()
		<< ';'
		<< cuc->getCourseUnit()->getAcronym()
		<< ';'
		<< cuc->classNumber
		<< ';'
		<< cuc->professor->getID()
		<< endl;

	return file;
}
#pragma once

#include "Student.h"

void Student::assignEmail()
{
	email = getCourse()->getCollege()->getUniversity()->getAcronym()
		+ to_string(ID)
		+ '@'
		+ getCourse()->getCollege()->getAcronym()
		+ '.'
		+ getCourse()->getCollege()->getUniversity()->getAcronym()
		+ '.'
		+ getCourse()->getCollege()->getUniversity()->getCountryAcronym();
}

void Student::assignID()
{
	ID = dateOfRegistration.getYear() * 100000 + 1 + getCourse()->getCollege()->getUniversity()->getLastStudentID();
	getCourse()->getCollege()->getUniversity()->incLastStudentID();
}

bool Student::enrollClass(CourseUnitClass* courseUnitClass)
{
	if (courseUnitClass->getNumberOfStudents() >= courseUnitClass->getMaxStudentsPerClass()) //CHECK IF CLASS IS FULL
		return false;
	else
	{
		courseUnitClass->addStudent(this); //ADD STUDENT TO CLASS
		return true;
	}
}

bool Student::enrollCourseUnit(CourseUnit* courseUnit) 
{
	//FIND THE ARGUMENT IN THE VECTOR OF COURSE UNITS
	vector<CourseUnit*>::iterator itOfCourseUnit;
	for (itOfCourseUnit = getCourse()->getCourseUnits().begin();		
		itOfCourseUnit != getCourse()->getCourseUnits().end();
		itOfCourseUnit++)
	{
		if (*itOfCourseUnit == courseUnit)
			break;
	}

	if (itOfCourseUnit == getCourse()->getCourseUnits().end()) //THERE IS NO COURSE UNIT IN THE VECTOR THAT MATCHES THE ARGUMENT 
		return false;

	if ((*itOfCourseUnit)->getNumberOfStudents() >= (*itOfCourseUnit)->getMaxStudents()) //COURSE UNIT IS FULL
		return false;

	vector<CourseUnitClass*>::iterator itCourseUnitClass;
	for (itCourseUnitClass = (*itOfCourseUnit)->getClasses().begin();
		itCourseUnitClass != (*itOfCourseUnit)->getClasses().end();
		itCourseUnitClass++)
	{
		if (enrollClass((*itCourseUnitClass)))
			return true;
	}
	return false;
}

void Student::completedClass(CourseUnit* courseUnit, unsigned short int grade)
{
	//CHECK IF GRADE IS ACCEPTABLE
	if (grade < 10)
		throw lowGrade(grade);

	//CHECK IF STUDENT HAS COMPLETED THAT COURSE UNIT BEFORE
	for (map<CourseUnit*, unsigned short int>::iterator it = completedCourseUnits.begin();
		it != completedCourseUnits.end();
		it++)
	{
		if (it->first == courseUnit) //STUDENT COMPLETED THE COURSE UNIT BEFORE
		{
			if (grade > it->second)  //WITH A LOWER GRADE
			{
				it->second = grade;
				return;
			}
			else return; //WITH THE SAME OR HIGHER GRADE
		}
	}

	completedCourseUnits.insert(pair<CourseUnit*, unsigned int>(courseUnit, grade)); //STUDENT COMPLETED THE COURSE UNIT FOR THE FIRST TIME
	
}
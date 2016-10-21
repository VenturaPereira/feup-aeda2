#pragma once

#include "Student.h"

void Student::assignEmail()
{
	email = course->college->university->acronym
		+ to_string(ID)
		+ '@'
		+ course->college->acronym
		+ '.'
		+ course->college->university->acronym
		+ '.'
		+ course->college->university->countryAcronym;
}
void Student::assignID()
{
	ID = dateOfRegistration.getYear() * 100000 + 1 + course->college->university->lastStudentID;
	course->college->university->lastStudentID++;
}

bool Student::enrollClass(CourseUnitClass &courseUnitClass)
{
	if (courseUnitClass.getNumberOfStudents() >= courseUnitClass.getMaxStudentsPerClass()) //CHECK IF CLASS IS FULL
		return false;
	else
	{
		courseUnitClass.addStudent(this); //ADD STUDENT TO CLASS
		return true;
	}
}

bool Student::enrollCourseUnit(CourseUnit &courseUnit) 
{
	//FIND THE INDEX IN THE VECTOR OF COURSE UNITS
	unsigned int indexOfCourseUnit = 0;
	for (; indexOfCourseUnit < this->course->courseUnits.size(); indexOfCourseUnit++)
	{
		if (this->course->courseUnits[indexOfCourseUnit] == courseUnit)
			break;
	}
	if(indexOfCourseUnit == this->course->courseUnits.size()) //THERE IS NO COURSE UNIT IN THE VECTOR THAT MATCHES THE ARGUMENT 
		return false
	//if(this->course->courseUnits[indexOfCourseUnit]) //CHECKS IF COURSE UNIT IS FULL


/*
	for (unsigned int i = 0; i < this->course->courseUnits->getClasses.size(); i++)
	{
		if (enrollClass(*(this->course->courseUnits->getClasses[i])))
			return true;
	}
	*/
}


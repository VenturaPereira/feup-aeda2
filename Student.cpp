#pragma once

#include "Student.h"

Student::Student(string n, Date dob, Course* c) : CollegeUser(n, dob, c->getCollege())
{
	course = c;
	assignID();
	assignEmail();
	assignTutor();
}

bool Student::assignTutor()
{
	vector<Tutor*>::iterator it = course->getProfessors().begin();
	vector<Tutor*>::iterator minimumStudents = it;
	if (course->getProfessors().size() == 0)
		return false;
	for (;it != course->getProfessors().end();it++)
	{
		if ((*it)->getStudents().size() < (*minimumStudents)->getStudents.size())
			minimumStudents = it;
	}
	(*minimumStudents)->tutorStudent(this);
	tutor = *minimumStudents;
	return true;
}

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
	course->getCollege()->getUniversity()->incrementLastStudentID();
}

bool Student::enrollClass(CourseUnitClass* courseUnitClass)
{
	if (courseUnitClass->getNumberOfStudents() >= courseUnitClass->getCourseUnit()->getMaxStudentsPerClass()) //CHECK IF CLASS IS FULL
		return false;
	else
	{
		courseUnitClass->getCourseUnit()->addStudent(this);
		courseUnitClass->addStudent(this); //ADD STUDENT TO CLASS
		classesCurrentlyAtending.insert(pair<CourseUnit*, CourseUnitClass*>(courseUnitClass->getCourseUnit(), courseUnitClass));
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
		if (enrollClass((*itCourseUnitClass))) //TRY TO ENROLL IN THAT CLASS
		{
			return true;
		}
	}

	//ALL CLASSES WERE FULL - CREATE A NEW CLASS AND ADD THE STUDENT
	CourseUnitClass* newClass = new CourseUnitClass(courseUnit->getNumberClasses() + 1, courseUnit);
	courseUnit->addCourseUnitClass(newClass);
	enrollClass(newClass);
	return true;
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
				it->second = grade; //REPLACE GRADE
				return;
			}
			else return; //WITH THE SAME OR HIGHER GRADE
		}
	}

	completedCourseUnits.insert(pair<CourseUnit*, unsigned int>(courseUnit, grade)); //STUDENT COMPLETED THE COURSE UNIT FOR THE FIRST TIME
	
}
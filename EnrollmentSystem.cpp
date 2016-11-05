#pragma once

#include "EnrollmentSystem.h"


EnrollmentSystem::EnrollmentSystem(unsigned int mc) : MAXIMUM_CREDITS(mc)
{
	//TODO - ADD THE SORTING OPTIONS
}

Course* EnrollmentSystem::getCourse(string &courseName) const
{
	vector<University*>::const_iterator uniIt;
	vector<College*>::const_iterator colIt;
	vector<Course*>::const_iterator courseIt;

	for (uniIt = universitiesVector.begin();
		uniIt != universitiesVector.end();
		uniIt++)
	{
		for (colIt = (*uniIt)->getColleges().begin();
			colIt != (*uniIt)->getColleges().end();
			colIt++)
		{
			for (courseIt = (*colIt)->getCourses().begin();
				courseIt != (*colIt)->getCourses().end();
				courseIt++)
			{
				if ((*courseIt)->getName() == courseName)
					return *courseIt;
			}
		}
	}
	throw NotFound<Course*>(courseName);
}

bool EnrollmentSystem::addStudentHandler()
{
	Student* student;
	Date* dateOfBirth;
	Course* course;
	string studentName, courseName;

	try
	{
		studentName = enterString("\nAdd Student\n\n", "Enter the name of the student [CTRL+Z to cancel] : ");
		while (true)
		{
			dateOfBirth = new Date(enterString("\nAdd Student\n\n", "Enter the date of birth (DD-MM-YYYY) [CTRL+Z to cancel] : "));
			if (dateOfBirth->getValid())
				break;
			cout << "\nInvalid Date!\n";
			system("PAUSE");
		}
		courseName = enterString("\nAdd Student\n\n", "Enter the name of the course [CTRL+Z to cancel] : ");
		course = getCourse(courseName);
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		return false;
	}
	catch (NotFound<Course*> &nf)
	{
		cout << "Course " << nf.getName() << " not found!\n";
		return false;
	}
	
	student = new Student(studentName, *dateOfBirth, course);
	
	course->addStudent(student);

	return true;
}


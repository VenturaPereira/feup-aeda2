#pragma once

#include "EnrollmentSystem.h"
#include "Utilities.h"
#include "University.h"
#include "College.h"
#include "Course.h"
#include "CourseUnit.h"
#include "Date.h"
#include "Student.h"


EnrollmentSystem::EnrollmentSystem(unsigned int mc) : MAXIMUM_CREDITS(mc)
{
	//TODO - ADD THE SORTING OPTIONS
}

Course* EnrollmentSystem::getCourse(string &courseName)
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

bool addStudentHandler(EnrollmentSystem& s)
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
		course = s.getCourse(courseName);
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

bool removeStudentHandler(EnrollmentSystem& s)
{
	Student* student;
	unsigned long long int ID;

	try
	{
		ID = enterInput<unsigned long long int>("\nRemove Student\n\n", "Enter the ID of the student [CTRL+Z to cancel] : ");
		student = s.getStudent(ID);
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		return false;
	}
	catch (NotFound<Student*> &nfs)
	{
		cout << "Student " << ID << " not found!\n";
		return false;
	}
	
	student->getCourse()->removeStudent(student);

	return true;
}

bool enrollmentHandler(EnrollmentSystem& s)
{
	Student* student;
	unsigned long long int ID;

	try
	{
		ID = enterInput<unsigned long long int>("\nEnrollment System\n\n", "Enter the ID of the student [CTRL+Z to cancel] : ");
		student = s.getStudent(ID);
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		return false;
	}
	catch (NotFound<Student*> &nfs)
	{
		cout << "Student " << ID << " not found!\n";
		return false;
	}
	
		vector<CourseUnit*> courseUnitsToShow = student->getCourse()->getCourseUnitsNotCompleted(student, student->getYear());
		unsigned short int answer = 0;
		try 
		{
			while (answer != (courseUnitsToShow.size() + 1) || courseUnitsToShow.size() == 0) //EXIT
			{
				system("CLS");
				for (size_t i = 0; i < courseUnitsToShow.size(); i++) //SHOW AS MENU
				{
					cout << (i + 1) << ". ";
					courseUnitsToShow[i]->show();
				}
				answer = enterInput<unsigned short int>(); //READ SELECTION
				if (answer >= 1 && answer <= courseUnitsToShow.size()) 
				{
					student->enrollCourseUnit(courseUnitsToShow[answer - 1]);
					courseUnitsToShow = student->getCourse()->getCourseUnitsNotCompleted(student, student->getYear()); //REFRESH MENU
				}
			}
		}
		catch (EndOfFile &eof)
		{
			cout << "Enrollment Canceled!\n";
			return false;
		}
	
	return courseUnitsToShow.size() == 0;
}
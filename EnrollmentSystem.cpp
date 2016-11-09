#pragma once

#include "EnrollmentSystem.h"
#include "Utilities.h"
#include "University.h"
#include "College.h"
#include "Course.h"
#include "CourseUnit.h"
#include "Date.h"
#include "Student.h"
#include "CourseUnitClass.h"


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
	throw NotFound<Course*, string>(courseName);
}

Student* EnrollmentSystem::getStudent(unsigned long long int &ID)
{
	vector<University*>::iterator unIt;
	for (unIt = universitiesVector.begin();
		unIt != universitiesVector.end();
		unIt++
		)
	{
		vector<College*>::iterator colIt;
		for (colIt = (*unIt)->getColleges().begin();
			colIt != (*unIt)->getColleges().end();
			colIt++
			)
		{
			vector<Course*>::iterator courseIt;
			for (courseIt = (*colIt)->getCourses().begin();
				courseIt != (*colIt)->getCourses().end();
				courseIt++
				)
			{
				vector<Student*>::iterator sIt; 
				for (sIt = (*courseIt)->getStudents().begin();
					sIt != (*courseIt)->getStudents().end();
					sIt++
					)
				{
					if ((*sIt)->getID() == ID)
						return (*sIt);

				}
			}
		}
	}
	throw NotFound<Student*, unsigned long long int>(ID);
}

CourseUnit* EnrollmentSystem::getCourseUnit(string &courseUnitName)
{
	vector<University*>::iterator unIt;
	for (unIt = universitiesVector.begin();
		unIt != universitiesVector.end();
		unIt++
		)
	{
		vector<College*>::iterator colIt;
		for (colIt = (*unIt)->getColleges().begin();
			colIt != (*unIt)->getColleges().end();
			colIt++
			)
		{
			vector<Course*>::iterator courseIt;
			for (courseIt = (*colIt)->getCourses().begin();
				courseIt != (*colIt)->getCourses().end();
				courseIt++
				)
			{
				vector<CourseUnit*>::iterator cuIt;
				for (cuIt = (*courseIt)->getCourseUnits().begin();
					cuIt != (*courseIt)->getCourseUnits().end();
					cuIt++
					)
				{
					if ((*cuIt)->getName() == courseUnitName)
						return (*cuIt);
				}
			}
		}
	}
	throw NotFound<CourseUnit*, string>(courseUnitName);
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
	catch (NotFound<Course*, string> &nf)
	{
		cout << "Course " << nf.getMember() << " not found!\n";
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
	catch (NotFound<Student*, unsigned long long int> &nfs)
	{
		cout << "Student " << nfs.getMember() << " not found!\n";
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
	catch (NotFound<Student*, unsigned long long int> &nfs)
	{
		cout << "Student " << nfs.getMember() << " not found!\n";
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
					if (student->getCredits() + courseUnitsToShow[answer - 1]->getCredits() <= s.getMaxCredits())
					{
						student->enrollCourseUnit(courseUnitsToShow[answer - 1]);
						courseUnitsToShow = student->getCourse()->getCourseUnitsNotCompleted(student, student->getYear()); //REFRESH MENU
						student->setCredits(student->getCredits() + courseUnitsToShow[answer - 1]->getCredits());
					}
					else cout << "Student cannot enroll this course unit. Maximum credits have been exceeded";
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

bool studentFinishedCourseUnitHandler(EnrollmentSystem& s) 
{
	Student* student;
	unsigned long long int ID;
	CourseUnit* courseUnit;
	string courseUnitName;
	unsigned short int grade;

	try
	{
		ID = enterInput<unsigned long long int>("\nFinish Course Unit\n\n", "Enter the ID of the student [CTRL+Z to cancel] : ");
		student = s.getStudent(ID);
		courseUnitName = enterString("\nFinish Course Unit\n\n", "Enter the name of the course unit [CTRL+Z to cancel] : ");
		courseUnit = s.getCourseUnit(courseUnitName);
		grade = enterInput<unsigned short int>("\nFinish Course Unit\n\n", "Enter the grade of the student to this course unit [CTRL+Z to cancel] : ");
		student = s.getStudent(ID);
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		return false;
	}
	catch (NotFound<Student*, unsigned long long int> &nfs)
	{
		cout << "Student " << nfs.getMember() << " not found!\n";
		return false;
	}
	catch (NotFound<CourseUnit*, string> &nfcu)
	{
		cout << "Course Unit " << nfcu.getMember() << " not found!\n";
		return false;
	}

	student->completedClass(courseUnit, grade);
	CourseUnitClass* courseUnitClass = student->getClassesCurrentlyAtending().at(courseUnit);
	courseUnitClass->removeStudent(student); 
	courseUnit->removeStudent(student);
	
	//CHECK IF STUDENT HAS COMPLETED ALL THE COURSE UNITS OF THE CURRENT YEAR
	if (student->completedAllCourseUnits(student->getYear()))
	{
		//GET READY FOR NEXT YEAR
		student->setCredits(0);
		student->setYear(student->getYear() + 1);
	}

	return true;
}
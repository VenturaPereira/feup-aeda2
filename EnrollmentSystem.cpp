#pragma once

#include "EnrollmentSystem.h"

bool EnrollmentSystem::addStudentHandler(Course* c)
{
	Student* student = NULL;
	try
	{
		string name = enterString("\nAdd Student\n\n", "Enter the name of the student [CTRL+Z to cancel] : ");
		Date* dateOfBirth = NULL;
		while (true)
		{
			dateOfBirth = new Date(enterInput<Date>("", "Enter the date of birth (DD-MM-YYYY) [CTRL+Z to cancel] : "));
			if (dateOfBirth->getValid())
				break;
			cout << "\nInvalid Date!\n";
			system("PAUSE");
		}
		student = new Student(name, *dateOfBirth, c);
	}
	catch (EndOfFile eof)
	{
		cout << "\nAddition canceled!\n";
		return false;
	}	
	
	c->addStudent(student);
	return true;
}


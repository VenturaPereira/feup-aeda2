#pragma once

#include "Menu.h"
#include "Utilities.h"
#include "EnrollmentSystem.h"

unsigned int menuOption(string badInput, string normalInput, vector<string> tryAgain, unsigned int min, unsigned int max){
	unsigned int option;
	while(true)
	{
		option = enterInput<unsigned int>(normalInput, tryAgain);
		if (option >= min && option <= max)
			return option;
	} 
}

bool mainMenu(EnrollmentSystem &sys){
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "==============================",
			"WELCOME", "",
			"1 - Students              ",
			"2 - Professors            ", 
			"3 - Information           " ,
			"4 - Options               ", "",
			"5 - Exit                  ",
			"==============================" }, 1, 5);
		switch (option)
		{
		case 1:
			studentsMenu(sys);
			break;
		case 2:
			professorsMenu(sys);
			break;
		case 3:
			infoMenu(sys);
			break;
		case 4:
			optionsMenu(sys);
			break;
		case 5:
			cout << "\nAre you sure you want to exit? (Y/N)\n";
			if (yesNoAnswer()){
				sys.saveHandler();
				return true;
			}
			else
				break;
		}
	}
}

bool studentsMenu(EnrollmentSystem &sys){
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "==============================",
			"Enrollment System", "",
			"1 - Add Student           ",
			"2 - Remove Student        ", 
			"3 - Enroll                " , 
			"4 - Back                  ", 
			"==============================" }, 1, 4);
		switch (option)
		{
		case 1:
			addStudentHandler(sys);
				return true;
		case 2:
			removeStudentHandler(sys);
			return true;
		case 3:
			enrollmentHandler(sys);
				return true;
		case 4:
			return false;

		}
	}
}

bool professorsMenu(EnrollmentSystem &sys){
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "-------------------------------------",
			"Professors", "",
			"1 - Grade Students               ", "",
			"2 - Back                         ",
			"-------------------------------------" }, 1, 2);
		switch (option)
		{
			/*
		case 1:
			addProfessorHandler(sys);
			//system("pause");
			return true;
		case 2:
			removeProfessorHandler(sys);
			//system("pause");
			return true; */
		case 1:
			studentFinishedCourseUnitHandler(sys);
			return true;
		case 2:
			return false;
		}
	}
}

bool infoMenu(EnrollmentSystem &sys){
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "---------------------------------------",
			"Information", "",
			"1  - Read all Universities         ",
			"2  - Read all Colleges             ",
			"3  - Read all Courses              ",
			"4  - Read all Course Units         ",
			"5  - Read a Course Unit in Detail  "
			"6  - Read all Course Unit Classes  ",
			"7  - Read all Students             ",
			"8  - Read a Student in Detail      ",
			"9  - Read all Professors           ", "",
			"10 - Back                          ",
			"---------------------------------------" }, 1, 10);

		switch (option)
		{
		case 1:
			sys.showUniversities();
			system("pause");
			return true;
		case 2:
			sys.showColleges();
			system("pause");
			return true;
		case 3:
			sys.showCourses();
			system("pause");
			return true;
		case 4:
			sys.showCourseUnits();
			system("pause");
			return true;
		case 5:
			sys.showCourseUnitInDetail();
			system("pause");
			return true;
		case 6:
			sys.showCourseUnitClasses();
			system("pause");
			return true;
		case 7:
			sys.showStudents();
			system("pause");
			return true;
		case 8:
			sys.showStudentInDetail();
			system("pause");
			return true;
		case 9:
			sys.showProfessors();
			system("pause");
			return true;
		case 10:
			return false;
		}
	}
}

bool optionsMenu(EnrollmentSystem &sys)
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "--------------------------------------------------",
			"Options", "",
			"1 - Change Students sorting options          ",
			"2 - Change Professors sorting options        ",
			"3 - Change Course Units sorting options      ",
			"4 - Change Course Units Class sorting options", "",
			"5 - Back                                     ",
			"-------------------------------------------------", }, 1, 5);
		

		switch (option)
		{
		case 1:
			sortingStudentsMenu(sys);
			return true;
		case 2:
			sortingProfessorsMenu(sys);
			return true;
		case 3:
			sortingCourseUnitMenu(sys);
			return true;
		case 4:
			sortingCourseUnitClassMenu(sys);
			return true;
		case 5:
			return false;
		}
	}
}

bool sortingStudentsMenu(EnrollmentSystem &sys) {
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "--------------------------------------------",
			"Students Sorting Options", "",
			"1 - Sort by ID                         ",
			"2 - Sort by Name                       ",
			"3 - Sort by Age                        ",
			"4 - Sort by Course Year                ",
			"5 - Sort by Registration Date          ", "",
			"6 - Back                               ",
			"--------------------------------------------", }, 1, 6);


		switch (option)
		{
		case 1:
			sys.changeStudentsSortOption(option);
			return true;
		case 2:
			sys.changeStudentsSortOption(option);
			return true;
		case 3:
			sys.changeStudentsSortOption(option);
			return true;
		case 4:
			sys.changeStudentsSortOption(option);
			return true;
		case 5:
			sys.changeStudentsSortOption(option);
			return true;
		case 6: 
			return false;
		}
	}
}

bool sortingProfessorsMenu(EnrollmentSystem &sys) {
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "--------------------------------------------",
			"Professors Sorting Options", "",
			"1 - Sort by ID                         ",
			"2 - Sort by Name                       ",
			"3 - Sort by Age                        ",
			"4 - Sort by Registration Date          ", "",
			"5 - Back                               ",
			"--------------------------------------------", }, 1, 5);


		switch (option)
		{
		case 1:
			sys.changeProfessorsSortOption(option);
			return true;
		case 2:
			sys.changeProfessorsSortOption(option);
			return true;
		case 3:
			sys.changeProfessorsSortOption(option);
			return true;
		case 4:
			sys.changeProfessorsSortOption(option);
			return true;
		case 5:
			return false;
		}
	}
}

bool sortingCourseUnitMenu(EnrollmentSystem &sys) {
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "--------------------------------------------",
			"Course Unit Sorting Options", "",
			"1 - Sort by Name                       ",
			"2 - Sort by Number of Students         ",
			"3 - Sort by Time                       ", "",     //TODO CHANGE THIS AND ?? ADD SORTING BY CREDITS ???
			"4 - Back                               ",
			"--------------------------------------------", }, 1, 4);


		switch (option)
		{
		case 1:
			sys.changeCourseUnitSortOption(option);
			return true;
		case 2:
			sys.changeCourseUnitSortOption(option);
			return true;
		case 3:
			sys.changeCourseUnitSortOption(option);
			return true;
		case 4:
			return false;
		}
	}
}

bool sortingCourseUnitClassMenu(EnrollmentSystem &sys) {
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "--------------------------------------------",
			"Course Unit Sorting Options", "",
			"1 - Sort by Number                     ",
			"2 - Sort by Number of Students         ", "", 
			"3 - Back                               ",
			"--------------------------------------------", }, 1, 3);


		switch (option)
		{
		case 1:
			sys.changeCourseUnitSortOption(option);
			return true;
		case 2:
			sys.changeCourseUnitSortOption(option);
			return true;
		case 3:
			return false;
		}
	}
}


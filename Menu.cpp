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

bool adminMenu(EnrollmentSystem &sys) {
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "-------------------------------------",
			"Administration", "",
			"1 - Add Class                    ",
			"2 - Remove Class                 ", "",
			"3 - Back                         ",
			"-------------------------------------" }, 1, 3);
		switch (option)
		{
		case 1:
			sys.addClass();
			return true;
		case 2:
			sys.removeClass();
			return true;
		case 3:
			return false;
		}
	}
}

bool modifyStudentMenu(EnrollmentSystem &sys) {
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "-------------------------------------",
			"Modify Student Data", "",
			"1 - Change Address               ",
			"2 - Change Phone Number          ", "",
			"3 - Back                         ",
			"-------------------------------------" }, 1, 3);
		switch (option)
		{
		case 1:
			sys.changeStudentAddress();
			return true;
		case 2:
			sys.changeStudentContact();
			return true;
		case 3:
			return false;
		}
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
			"3 - Information           ",
			"4 - Administration        ",
			"5 - Options               ", "",
			"6 - Exit                  ",
			"==============================" }, 1, 6);
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
			adminMenu(sys);
			break;
		case 5:
			optionsMenu(sys);
			break;
		case 6:
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
			"2 - Suspend Course        ", 
			"3 - Enroll                " ,
			"4 - Update Data           ","",
			"5 - Back                  ", 
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
			modifyStudentMenu(sys);
			return true;
		case 5:
			return false;

		}
	}
}

bool showMeetingsMenu(EnrollmentSystem &sys) {
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "--------------------------------------------",
			"Show Meetings", "",
			"1 - Show All Meetings                   ",
			"2 - Show All Occured Meetings           ",
			"3 - Show Occured Meetings between Dates ",
			"4 - Show All Upcoming Meetings          ",
			"5 - Show Upcoming Meetings between Dates", "",
			"6 - Back                                ",
			"--------------------------------------------" }, 1, 6);
		switch (option)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			sys.showMeetingsHandler(option);
			return true;
		case 6:
			return false;
		}
	}
}

bool meetingsMenu(EnrollmentSystem &sys) {
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "-----------------------------------",
			"Meetings", "",
			"1 - Add Meeting                ",
			"2 - Cancel Meeting             ",
			"3 - Modify Meeting Description ",
			"4 - Show Meetings              ", "",
			"5 - Back                       ",
			"-----------------------------------" }, 1, 5);
		switch (option)
		{
		case 1:
			sys.addMeetingHandler();
			return true;
		case 2:
			sys.removeMeetingHandler();
			return true;
		case 3:
			sys.changeMeetingDescriptionHandler();
			return true;
		case 4:
			showMeetingsMenu(sys);
			return true;
		case 5:
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
			"1 - Grade Students               ",
			"2 - Meetings                     ", "",
			"3 - Back                         ",
			"-------------------------------------" }, 1, 3);
		switch (option)
		{
		case 1:
			studentFinishedCourseUnitHandler(sys);
			return true;
		case 2:
			meetingsMenu(sys);
			return true;
		case 3:
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
			"1  - Read all Universities             ",
			"2  - Read all Colleges                 ",
			"3  - Read all Courses                  ",
			"4  - Read all Course Units             ",
			"5  - Read a Course Unit in Detail      ",
			"6  - Read all Course Unit Classes      ",
			"7  - Read a Course Unit Class in Detail",
			"8  - Read all Students                 ",
			"9  - Read a Student in Detail          ",
			"10 - Read all Professors               ", 
			"11 - Read a Professor in Detail        ",	"",
			"12 - Back                              ",
			"---------------------------------------" }, 1, 12);

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
			sys.showCourseUnitClassInDetail();
			system("pause");
			return true;
		case 8:
			sys.showStudents();
			system("pause");
			return true;
		case 9:
			sys.showStudentInDetail();
			system("pause");
			return true;
		case 10:
			sys.showProfessors();
			system("pause");
			return true;
		case 11:
			sys.showProfessorInDetail();
			system("pause");
			return true;
		case 12:
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
		case 2:
		case 3:
		case 4:
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
		case 2:
		case 3:
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
			"3 - Sort by Program Plan Schedule      ", "",     
			"4 - Back                               ",
			"--------------------------------------------", }, 1, 4);


		switch (option)
		{
		case 1:
		case 2:
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
			"2 - Sort by Number of Students         ",
			"3 - Sort by Space Available            ","", 
			"4 - Back                               ",
			"--------------------------------------------", }, 1, 4);


		switch (option)
		{
		case 1:
		case 2:
		case 3:
			sys.changeCourseUnitSortOption(option);
			return true;
		case 4:
			return false;
		}
	}
}


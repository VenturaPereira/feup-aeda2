#pragma once

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
using namespace std;

class EnrollmentSystem;

/*!
*	Handler for Menus to print on screen and check if the input is valid
*/
unsigned int menuOption(string badInput, string normalInput, vector<string> tryAgain, unsigned int min, unsigned int max);

/*!
*	Main Menu 
*/
bool mainMenu(EnrollmentSystem &sys);

/*!
*	Menu to Add, Remove or Enroll Students
*/
bool studentsMenu(EnrollmentSystem &sys);

/*!
*	Menu to Grade Students and Manage Meetings
*/
bool professorsMenu(EnrollmentSystem &sys);

/*!
*	Menu to see Information about all the System
*/
bool infoMenu(EnrollmentSystem &sys);

/*!
*	Menu for Options (Sorting Options)
*/
bool optionsMenu(EnrollmentSystem &sys);

/*!
*	Menu for Students Sorting Options
*/
bool sortingStudentsMenu(EnrollmentSystem &sys);

/*!
*	Menu for Professors Sorting Options
*/
bool sortingProfessorsMenu(EnrollmentSystem &sys);

/*!
*	Menu for Course Units Sorting Options
*/
bool sortingCourseUnitMenu(EnrollmentSystem &sys);

/*!
*	Menu for Classes Sorting Options
*/
bool sortingCourseUnitClassMenu(EnrollmentSystem &sys); 

/*!
*	Menu for Meetings
*/
bool meetingsMenu(EnrollmentSystem &sys);

/*!
*	Menu to Show Meetings
*/
bool showMeetingsMenu(EnrollmentSystem &sys);

#endif

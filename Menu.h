#pragma once

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
using namespace std;

class EnrollmentSystem;

unsigned int menuOption(string badInput, string normalInput, vector<string> tryAgain, unsigned int min, unsigned int max);
bool mainMenu(EnrollmentSystem &sys);
bool studentsMenu(EnrollmentSystem &sys);
bool professorsMenu(EnrollmentSystem &sys);
bool infoMenu(EnrollmentSystem &sys);
bool optionsMenu(EnrollmentSystem &sys);
bool sortingStudentsMenu(EnrollmentSystem &sys);
bool sortingProfessorsMenu(EnrollmentSystem &sys);
bool sortingCourseUnitMenu(EnrollmentSystem &sys);
bool sortingCourseUnitClassMenu(EnrollmentSystem &sys); 

#endif

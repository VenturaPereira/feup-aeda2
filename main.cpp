#include "EnrollmentSystem.h"
#include "University.h"
#include "College.h"
#include "Course.h"
#include "Menu.h"
#include "CourseUnit.h"
#include "Utilities.h"


#define MAX_CREDITS 75

int run()
{
<<<<<<< HEAD
	EnrollmentSystem sys(75); //INITIALIZE SYSTEM

	University* UP = new University("Universidade do Porto", "up", "pt");
	sys.addUniversity(UP); //ADD UP

	College* FEUP = new College("Faculdade de Engenharia da Universidade do Porto", "FEUP", UP);
	sys.getUniversities()[0]->addCollege(FEUP); //ADD FEUP

	Course* MIEIC = new Course("Mestrado Integrado em Engenharia Informatica e Computacao", "MIEIC", FEUP);
	sys.getUniversities()[0]->getColleges()[0]->addCourse(MIEIC); //ADD MIEIC

	//bool(*adh)(EnrollmentSystem&) = addStudentHandler;
	mainMenu(sys);
=======
	//START SYSTEM
	EnrollmentSystem system(MAX_CREDITS); //INITIALIZE SYSTEM
	University* UP = new University("Universidade do Porto", "up", "pt");
	system.addUniversity(UP); //ADD UP
	College* FEUP = new College("Faculdade de Engenharia da Universidade do Porto", "FEUP", UP);
	system.getUniversities()[0]->addCollege(FEUP); //ADD FEUP
	Course* MIEIC = new Course("Mestrado Integrado em Engenharia Informática e Computação", "MIEIC", FEUP);
	system.getUniversities()[0]->getColleges()[0]->addCourse(MIEIC); //ADD MIEIC

	//LOAD MENUS
	/*
	vector<string> mainMenuStrings;
	vector<void(*)()> mainMenuFunctions;
	Menu mainMenu("Main Menu", mainMenuStrings, mainMenuFunctions);
	
	vector<string> mainMenuStrings;
	vector<void(*)()> mainMenuFunctions;
	Menu mainMenu("Main Menu", mainMenuStrings, mainMenuFunctions);

	vector<string> startMenuStrings = {
		"New System", 
		"Load Files"
		"Exit",
	};
	vector<void(*)(void)> startMenuFunctions;
	
	Menu startMenu("Start Menu", startMenuStrings, startMenuFunctions);*/

>>>>>>> refs/remotes/origin/RendoirBranch
	return 0;
}

int main()
{
	run();

	return 0;
}
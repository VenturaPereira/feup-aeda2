#include "EnrollmentSystem.h"
#include "University.h"
#include "College.h"
#include "Course.h"
#include "Menu.h"
#include "CourseUnit.h"
#include "Utilities.h"

//#define MNOSPC 30 //MAXIMUM NUMBER OF STUDENTS PER CLASS

int run()
{
	EnrollmentSystem system(75); //INITIALIZE SYSTEM

	University* UP = new University("Universidade do Porto", "up", "pt");
	system.addUniversity(UP); //ADD UP

	College* FEUP = new College("Faculdade de Engenharia da Universidade do Porto", "FEUP", UP);
	system.getUniversities()[0]->addCollege(FEUP); //ADD FEUP

	Course* MIEIC = new Course("Mestrado Integrado em Engenharia Informática e Computação", "MIEIC", FEUP);
	system.getUniversities()[0]->getColleges()[0]->addCourse(MIEIC); //ADD MIEIC

	//bool(*adh)(EnrollmentSystem&) = addStudentHandler;
	
	return 0;
}

int main()
{
	run();
	
	return 0;
}
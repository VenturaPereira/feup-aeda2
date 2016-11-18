#include "EnrollmentSystem.h"
#include "University.h"
#include "College.h"
#include "Course.h"
#include "Menu.h"
#include "CourseUnit.h"
#include "Utilities.h"
#include "Student.h"


#define MAX_CREDITS 75

int run()
{

	//START SYSTEM 
	EnrollmentSystem sys(MAX_CREDITS); //INITIALIZE SYSTEM
	/*University* UP = new University("Universidade do Porto", "up", "pt");
	College* FEUP = new College("Faculdade de Engenharia da Universidade do Porto", "FEUP", UP);
	Course* MIEIC = new Course("Mestrado Integrado em Engenharia Informática e Computação", "MIEIC", FEUP);*/
	
	mainMenu(sys);	

	return 0;
}

int main()
{

	run();

	return 0;
}
#include "EnrollmentSystem.h"
#include "Course.h"

int main()
{
	EnrollmentSystem system(75); //INITIALIZE SYSTEM
	
	University* UP = new University("Universidade do Porto", "up", "pt");
	system.getUniversities().push_back(UP); //ADD UP
	
	College* FEUP = new College("Faculdade de Engenharia da Universidade do Porto", "FEUP", UP);
	system.getUniversities()[0]->addCollege(FEUP); //ADD FEUP
	
	Course* MIEIC = new Course("Mestrado Integrado em Engenharia Informática e Computação", "MIEIC", FEUP);
	system.getUniversities()[0]->getColleges()[0]->addCourse(MIEIC); //ADD MIEIC


	return 0;
}
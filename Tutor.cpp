#include "Tutor.h"

void Tutor::tutorStudent(Student* s)
{
	students.push_back(s);
}

bool Tutor::teachClass(CourseUnitClass* c)
{
	if (find(currentlyTeaching.begin(), currentlyTeaching.end(), c->getCourseUnit()) != currentlyTeaching.end()) //ALREADY TEACHING
		return false;
	if (find(ableToTeach.begin(), ableToTeach.end(), c->getCourseUnit()) == ableToTeach.end()) //NOT ABLE TO TEACH
		return false;
	
	c->setProfessor(this);
	c->getCourseUnit()->addProfessor(this);
	currentlyTeaching.push_back(c->getCourseUnit());
	return true;
}

void Tutor::assignEmail()
{
	string inicials;
	for (size_t i = 0; i < name.size(); i++)
	{
		if (isupper(name[i]))
			inicials += name[i];
	}
	if (inicials.size() == 0)
		email = name;
	else email = inicials;
	email += '@'
		+ getCourse()->getCollege()->getAcronym()
		+ '.'
		+ getCourse()->getCollege()->getUniversity()->getAcronym()
		+ '.'
		+ getCourse()->getCollege()->getUniversity()->getCountryAcronym();
}

void Tutor::assignID()
{
	ID = course->getCollege()->getUniversity()->getLastStudentID() + 1;
	course->getCollege()->getUniversity()->incrementLastProfessorID();
}
bool compareTutorName(Tutor & t1, Tutor & t2) {
	if (((t1.getName()).compare(t2.getName())) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
int compareTutorID(Tutor & t1, Tutor & t2) {
	int result = t1.ID - t2.ID;
	if (result == 0) {
		return 0; //sao iguais
	}
	else if (result > 0) {
		return 1; // id de t1 e maior
	}
	else {
		return -1;
	}
}
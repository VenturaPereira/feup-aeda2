#include "Tutor.h"
#include "CourseUnitClass.h"
#include "Course.h"
#include "College.h"
#include "CourseUnit.h"
#include "University.h"
#include <fstream>
#include "Student.h"

Tutor::Tutor(string n, Date dob, Course* c, vector<CourseUnit*> att)
	: CollegeUser(n, dob, c->getCollege()), course(c)
{
	c->addProfessor(this);
}

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
	ID = course->getCollege()->getUniversity()->getLastProfessorID() + 1;
	course->getCollege()->getUniversity()->incrementLastProfessorID();
}

bool compareProfessorByName(Tutor* p1, Tutor* p2) 
{
	return p1->name < p2->name;
}

bool compareProfessorByID(Tutor* p1, Tutor* p2)
{
	return p1->ID < p2->ID;
}

bool compareProfessorByBirth(Tutor* p1, Tutor* p2)
{
	return p1->dateOfBirth < p2->dateOfBirth;
}

ofstream& operator<<(ofstream& file, const Tutor *t)
{
	file << t->getCourse()->getCollege()->getUniversity()->getAcronym()
		<< ';'
		<< t->getCourse()->getCollege()->getAcronym()
		<< ';'
		<< t->getCourse()->getAcronym()
		<< ';'
		<< t->name
		<< ';'
		<< t->getDateOfBirth().getDateString()
		<< ';'
		<< '{';

	for (unsigned int i = 0; i < t->ableToTeach.size(); i++) {
		file << t->ableToTeach[i]->getAcronym();
		if (i != t->ableToTeach.size() - 1)
			file << ',';
	}

	file << '}'
		<< ';'
		<< '{';

	for (unsigned int i = 0; i < t->currentlyTeaching.size(); i++) {
		file << t->currentlyTeaching[i]->getAcronym();
		if (i != t->ableToTeach.size() - 1)
			file << ',';
	}

	file << '}';
		/*<< ';'
		<< '{';

	for (unsigned int i = 0; i < t->students.size(); i++) {
		file << t->students[i]->getID();
		if (i != t->students.size() - 1)
			file << ',';
	}

	file << '}'*/
	file << endl;

	return file;
}
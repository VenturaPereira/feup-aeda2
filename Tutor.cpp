#include "Tutor.h"
#include "CourseUnitClass.h"
#include "Course.h"
#include "College.h"
#include "CourseUnit.h"
#include "University.h"
#include <fstream>
#include "Student.h"
#include "Utilities.h"

Tutor::Tutor(string n, Date dob, Course* c, vector<CourseUnit*> att)
	: CollegeUser(n, dob, c->getCollege()), course(c),
	ableToTeach(att)
{
	assignID();
	assignEmail();
	c->addProfessor(this);
}

Tutor::Tutor(string n, Date dob, Course* c, unsigned long long int &ID, vector<CourseUnit*> &ct, vector<CourseUnit*> &att)
	: CollegeUser(n, dob, c->getCollege()), course(c),
	ableToTeach(att), currentlyTeaching(ct)
{
	setID(ID);
	assignEmail();
	c->addProfessor(this);
}

void Tutor::tutorStudent(Student* s)
{
	students.push_back(s);
}

bool Tutor::teachClass(CourseUnitClass* c)
{
	if (find(ableToTeach.begin(), ableToTeach.end(), c->getCourseUnit()) == ableToTeach.end()) //NOT ABLE TO TEACH
		return false;
		
	c->setProfessor(this);

	if (find(currentlyTeaching.begin(), currentlyTeaching.end(), c->getCourseUnit()) == currentlyTeaching.end()) //NOT TEACHING
	{
		c->getCourseUnit()->addProfessor(this);
		currentlyTeaching.push_back(c->getCourseUnit());
	}
		
	return true;
}

void Tutor::assignEmail()
{
	string inicials;
	for (int i = 0; i < name.size(); i++)
	{
		if(iswalpha(name[i]))
			if (iswupper(name[i]))
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

ofstream& operator<<(ofstream& file, Tutor *t)
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
		<< t->ID
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

void Tutor::show() const {
	cout << course->getCollege()->getAcronym()
		<< setw(CONSOLE_WIDTH * 0.5 - course->getCollege()->getAcronym().size())
		<< course->getAcronym()
		<< setw(CONSOLE_WIDTH * 0.5 - course->getAcronym().size())
		<< name
		<< setw(CONSOLE_WIDTH * 1.5 - name.size())
		<< ID
		<< endl;
}
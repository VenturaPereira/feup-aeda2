#include "Tutor.h"
#include "CourseUnitClass.h"
#include "Course.h"
#include "College.h"
#include "CourseUnit.h"
#include "University.h"
#include <fstream>
#include "Student.h"
#include "Utilities.h"

Tutor::Tutor(string n, Date dob, Course& c, vector<CourseUnit*>& att)
	: CollegeUser(n, dob, c), course(&c),
	ableToTeach(att)
{
	assignID();
	assignEmail();
	c.addProfessor(*this);
}

Tutor::Tutor(string n, Date dob, Date dor, Course& c, unsigned long long int &ID, vector<CourseUnit*> &ct, vector<CourseUnit*> &att)
	: CollegeUser(n, dob, c), course(&c),
	ableToTeach(att), currentlyTeaching(ct)
{
	setID(ID);
	assignEmail();
	c.addProfessor(*this);
	dateOfRegistration = dor;
}

void Tutor::tutorStudent(Student& s)
{
	students.push_back(&s);
}

bool Tutor::teachClass(CourseUnitClass& c)
{
	if (find(ableToTeach.begin(), ableToTeach.end(), &(c.getCourseUnit())) == ableToTeach.end()) //NOT ABLE TO TEACH
		return false;

	if (find(currentlyTeaching.begin(), currentlyTeaching.end(), &(c.getCourseUnit())) == currentlyTeaching.end()) //NOT TEACHING
	{
		c.getCourseUnit().addProfessor(*this);
		currentlyTeaching.push_back(&(c.getCourseUnit()));
	}

	return true;
}

void Tutor::assignEmail()
{
	string inicials;
	for (int i = 0; i < name.size(); i++)
	{
		if (iswalpha(name[i]))
			if (iswupper(name[i]))
				inicials += name[i];
	}
	if (inicials.size() == 0)
		email = name;
	else email = inicials;
	email += '@'
		+ course->getCollege().getAcronym()
		+ '.'
		+ course->getCollege().getUniversity().getAcronym()
		+ '.'
		+ course->getCollege().getUniversity().getCountryAcronym();
}

void Tutor::assignID()
{
	ID = course->getCollege().getUniversity().getLastProfessorID() + 1;
	course->getCollege().getUniversity().incrementLastProfessorID();
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

bool compareProfessorByRegistration(Tutor* p1, Tutor* p2)
{
	return p1->dateOfRegistration < p2->dateOfRegistration;
}

ofstream& Tutor::operator<<(ofstream& file)
{
	file << this->getCourse().getCollege().getUniversity().getAcronym()
		<< ';'
		<< this->getCourse().getCollege().getAcronym()
		<< ';'
		<< this->getCourse().getAcronym()
		<< ';'
		<< this->name
		<< ';'
		<< this->getDateOfBirth().getDateString()
		<< ';'
		<< this->getDateOfRegistration().getDateString()
		<< ';'
		<< this->ID
		<< ';'
		<< '{';

	for (unsigned int i = 0; i < this->ableToTeach.size(); i++) {
		file << this->ableToTeach[i]->getAcronym();
		if (i != this->ableToTeach.size() - 1)
			file << ',';
	}

	file << '}'
		<< ';'
		<< '{';

	for (unsigned int i = 0; i < this->currentlyTeaching.size(); i++) {
		file << this->currentlyTeaching[i]->getAcronym();
		if (i != this->currentlyTeaching.size() - 1)
			file << ',';
	}

	file << '}'
		<< endl;

	return file;
}

void Tutor::show() const {
	cout
		<< left
		<< setw(CONSOLE_WIDTH * 0.5)
		<< name
		<< ID
		<< '\t'
		<< setw(CONSOLE_WIDTH * 0.2)
		<< course->getAcronym()
		<< setw(CONSOLE_WIDTH * 0.2)
		<< course->getCollege().getAcronym()
		<< right
		<< endl
		<< '\t'
		<< dateOfBirth.getDateString()
		<< '\t'
		<< dateOfRegistration.getDateString()
		<< endl;
}

bool Tutor::addMeeting(Meeting &m) {
	pair<set<Meeting>::iterator, bool> result = meetings.insert(m);
	return result.second;
}

bool Tutor::removeMeeting(Meeting &m) {
	set<Meeting>::iterator it;

	for (it = meetings.begin();
		it != meetings.end();
		it++) {
		if (*it == m) {
			meetings.erase(it);
			return true;
		}
	}

	return false;
}

void Tutor::showAllMeetings() const {
	if (meetings.size() != 0) {

		cout << "\nMeetings:\n\n";

		set<Meeting>::iterator it;

		for (it = meetings.begin();
			it != meetings.end();
			it++) {
			it->show();
			cout << endl;
		}
	}
	else cout << "\nThere are no meetings\n\n";
}

void Tutor::showMeetingsOccured() const {

	cout << "\nOccured Meetings:\n\n";
	bool empty = true;
	set<Meeting>::iterator it;

	for (it = meetings.begin();
		it != meetings.end();
		it++) {
		if (it->hasOccured()) {
			empty = false;
			it->show();
			cout << endl;
		}
	}

	if (empty)
		cout << "There were no past meetings\n\n";
}

void Tutor::showMeetingsOccured(const Date &begin, const Date &end) const {
	cout << "\nOccured Meetings from " << begin.getDateString() << " to " << end.getDateString() << ':' << endl << endl;
	bool empty = true;
	set<Meeting>::iterator it;

	for (it = meetings.begin();
		it != meetings.end();
		it++) {
		if (it->hasOccured() && (it->getDate() >= begin) && (it->getDate() <= end)) {
			empty = false;
			it->show();
			cout << endl;
		}
	}
	if (empty)
		cout << "\nThere are no occured meetings from " << begin.getDateString() << " to " << end.getDateString() << endl << endl;
}

void Tutor::showMeetingsUpcoming() const {
	cout << "\nUpcoming Meetings:\n\n";
	bool empty = true;
	set<Meeting>::iterator it;

	for (it = meetings.begin();
		it != meetings.end();
		it++) {
		if (!(it->hasOccured())) {
			empty = false;
			it->show();
			cout << endl;
		}
	}
	if (empty)
		cout << "There are no upcoming meetings\n\n";
}

void Tutor::showMeetingsUpcoming(const Date &begin, const Date &end) const {
	cout << "\nUpcoming Meetings from " << begin.getDateString() << " to " << end.getDateString() << ':' << endl << endl;
	bool empty = true;
	set<Meeting>::iterator it;

	for (it = meetings.begin();
		it != meetings.end();
		it++) {
		if (!(it->hasOccured()) && (it->getDate() >= begin) && (it->getDate() <= end)) {
			empty = false;
			it->show();
			cout << endl;
		}
	}
	if (empty)
		cout << "\nThere are no upcoming meetings from " << begin.getDateString() << " to " << end.getDateString() << endl << endl;
}

bool Tutor::isTutorOf(Student& s) {
	for (size_t i = 0; i < students.size(); i++) {
		if (&s == students[i])
			return true;
	}
	return false;
}

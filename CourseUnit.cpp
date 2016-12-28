#pragma once

#include <iostream>

#include "CourseUnitClass.h"
#include "CourseUnit.h"
#include "Course.h"
#include "College.h"
#include "University.h"
#include "Utilities.h"
#include <fstream>
#include "Student.h"
#include "Tutor.h"

CourseUnit::CourseUnit(string n, string a, Course& c, unsigned short int y, unsigned short int s, double credits)
	: name(n), acronym(a), year(y), semester(s), credits(credits), course(&c)
{
}

OptionalCourseUnit::OptionalCourseUnit(unsigned int mnos, string n, string a, Course& c, unsigned short int y, unsigned short int s, string sa, double cred)
	: CourseUnit(n,a,c,y,s,cred), MAXIMUM_NUMBER_OF_STUDENTS(mnos), scientificArea(sa)
{
	c.addCourseUnit(*this);
}

MandatoryCourseUnit::MandatoryCourseUnit(unsigned int mnospc, string n, string a, Course& c, unsigned short int y, unsigned short int s, double cred)
	: CourseUnit(n, a, c, y, s, cred), MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS(mnospc)
{
	c.addCourseUnit(*this);
}

void CourseUnit::addStudent(Student& s)
{
	studentsCurrentlyInCourseUnit.push_back(&s);
}

bool CourseUnit::removeStudent(Student& s)
{
	for (vector<Student *> ::const_iterator it = studentsCurrentlyInCourseUnit.begin();
		it != studentsCurrentlyInCourseUnit.end();
		it++)
	{
		if ((*it) == &s)
		{
			studentsCurrentlyInCourseUnit.erase(it);
			return true;
		}
	}
	return false;
}

void CourseUnit::addProfessor(Tutor& t)
{
	courseUnitProfessors.push_back(&t);
}

bool CourseUnit::removeProfessor(Tutor& t)
{
	for (vector<Tutor *> ::const_iterator it = courseUnitProfessors.begin();
		it != courseUnitProfessors.end();
		it++)
	{
		if ((*it) == &t)
		{
			courseUnitProfessors.erase(it);
			return true;
		}
	}
	return false;
}

void CourseUnit::addCourseUnitClass(CourseUnitClass& cuc)
{
	classes.push(&cuc);
}

bool CourseUnit::removeCourseUnitClass(CourseUnitClass& cuc)
{
	bool found = false;
	priority_queue<CourseUnitClass*, vector<CourseUnitClass*>, CourseUnitClass::courseUnitCompare> pqTemp;
	while (!classes.empty()) {
		CourseUnitClass * cucTemp = classes.top();
		if (cucTemp->getClassNumber() == cuc.getClassNumber())
			found = true;
		else pqTemp.push(cucTemp);
		classes.pop();
	}
	classes = pqTemp;
	return found;
}

void OptionalCourseUnit::show() const
{
	cout 
		<< left
		<< setw(CONSOLE_WIDTH)
		<< name
		<< setw(CONSOLE_WIDTH * 0.2)
		<< acronym
		<< setw(CONSOLE_WIDTH * 0.2)
		<< course->getAcronym() 
		<< "Opt" << "\t" 
		<< year << "\t"
		<< semester << "\t"
		<< credits
		<< right
		<< endl;

}

void MandatoryCourseUnit::show() const
{
	cout
		<< left
		<< setw(CONSOLE_WIDTH)
		<< name
		<< setw(CONSOLE_WIDTH * 0.2)
		<< acronym
		<< setw(CONSOLE_WIDTH * 0.2)
		<< course->getAcronym()
		<< "Mand" << "\t"
		<< year << "\t"
		<< semester << "\t"
		<< credits
		<< right
		<< endl;
}

bool compareCourseUnitByNumberStudents(CourseUnit* cu1, CourseUnit* cu2)
{
	return (cu1->getNumberOfStudents() < cu2->getNumberOfStudents());
}

bool compareCourseUnitByName(CourseUnit* cu1, CourseUnit* cu2)
{
	return (cu1->name < cu2->name);
}

bool compareCourseUnitByTime(CourseUnit* cu1, CourseUnit* cu2)
{
	if (cu1->year < cu2->year)
		return true;
	else if (cu1->year > cu2->year)
		return false;
	else return (cu1->semester < cu2->semester);
}

ofstream& OptionalCourseUnit::operator<<(ofstream& file)
{
	file << this->getCourse().getCollege().getUniversity().getAcronym()
		<< ';'
		<< this->getCourse().getCollege().getAcronym()
		<< ';'
		<< this->getCourse().getAcronym()
		<< ';'
		<< this->name
		<< ';'
		<< this->acronym
		<< ';'
		<< "Optional"
		<< ';'
		<< this->MAXIMUM_NUMBER_OF_STUDENTS
		<< ';'
		<< this->scientificArea
		<< ';'
		<< this->year
		<< ';'
		<< this->semester
		<< ';'
		<< this->credits
		<< endl;

	return file;
}

ofstream& MandatoryCourseUnit::operator<<(ofstream& file)
{

	file << this->getCourse().getCollege().getUniversity().getAcronym()
		<< ';'
		<< this->getCourse().getCollege().getAcronym()
		<< ';'
		<< this->getCourse().getAcronym()
		<< ';'
		<< this->name
		<< ';'
		<< this->acronym
		<< ';'
		<< "Mandatory"
		<< ';'
		<< this->MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS
		<< ';'
		<< this->year
		<< ';'
		<< this->semester
		<< ';'
		<< this->credits
		<< endl;

	return file;
}

void MandatoryCourseUnit::showInDetail() const
{
	cout
		<< "Name: " << name << endl << endl
		<< "Acronym: " << acronym << endl << endl
		<< "Course: " << course->getAcronym() << endl << endl
		<< "College: " << course->getCollege().getAcronym() << endl << endl
		<< "University: " << course->getCollege().getUniversity().getAcronym() << endl << endl
		<< "Year: " << year << endl << endl
		<< "Semester: " << semester << endl << endl
		<< "Credits: " << credits << endl << endl
		<< "Type: Mandatory" << endl << endl
		<< "Maximum number of students per class: " << MAXIMUM_NUMBER_OF_STUDENTS_PER_CLASS << endl << endl
		<< "Number of classes: " << classes.size() << endl << endl;
	
	if (studentsCurrentlyInCourseUnit.size() != 0) {
		cout << "\nStudents:\n";
		for (unsigned int i = 0; i < studentsCurrentlyInCourseUnit.size(); i++)
			cout << '\t'
			<< studentsCurrentlyInCourseUnit[i]->getName()
			<< endl;			
	}
	else cout << "\nThere are no students in this course unit\n\n";
	
	if (courseUnitProfessors.size() != 0) {
		cout << "\nProfessors:\n";
		for (unsigned int i = 0; i < courseUnitProfessors.size(); i++)
			cout << '\t'
			<< courseUnitProfessors[i]->getName()
			<< endl;
	}
	else cout << "\nThere are no professors teaching this course unit\n\n";
}

void OptionalCourseUnit::showInDetail() const
{
	cout
		<< "Name: " << name << endl << endl
		<< "Acronym: " << acronym << endl << endl
		<< "Course: " << course->getAcronym() << endl << endl
		<< "College: " << course->getCollege().getAcronym() << endl << endl
		<< "University: " << course->getCollege().getUniversity().getAcronym() << endl << endl
		<< "Year: " << year << endl << endl
		<< "Semester: " << semester << endl << endl
		<< "Credits: " << credits << endl << endl
		<< "Type: Optional" << endl << endl
		<< "Maximum number of students: " << MAXIMUM_NUMBER_OF_STUDENTS << endl << endl
		<< "Scientific Area: " << scientificArea << endl << endl;
	if (studentsCurrentlyInCourseUnit.size() != 0) {
		cout << "\nStudents:\n";
		for (unsigned int i = 0; i < studentsCurrentlyInCourseUnit.size(); i++)
			cout << '\t'
			<< studentsCurrentlyInCourseUnit[i]->getName()
			<< endl;
	}
	else cout << "\nThere are no students in this course unit\n\n";

	if (courseUnitProfessors.size() != 0) {
		cout << "\nProfessors:\n";
		for (unsigned int i = 0; i < courseUnitProfessors.size(); i++)
			cout << '\t'
			<< courseUnitProfessors[i]->getName()
			<< endl;
	}
	else cout << "\nThere are no professors teaching this course unit\n\n";
}

bool MandatoryCourseUnit::possibleToEnroll() {
	return true;
}

bool OptionalCourseUnit::possibleToEnroll() {
	return this->getNumberOfStudents() < this->getMaxStudents();
}

void MandatoryCourseUnit::enrollStudent(Student &s) {
	this->addStudent(s);
	
	priority_queue<CourseUnitClass*, vector<CourseUnitClass*>, CourseUnitClass::courseUnitCompare> pqTemp;
	bool enrolled = false;
	unsigned short int classNumber = 0;
	while (!classes.empty()) {
		CourseUnitClass* cucTemp = classes.top();
		if (cucTemp->getClassNumber() > classNumber)
			classNumber = cucTemp->getClassNumber();
		if (!enrolled) {
			if (cucTemp->hasSpace()) {
				cucTemp->addStudent(s);
				s.addToCurrentlyAttending(*this, *cucTemp);
				enrolled = true;
			}
		}
		pqTemp.push(cucTemp);
		classes.pop();
	}
	classes = pqTemp;
	classNumber++;

	if (!enrolled) {
		CourseUnitClass* newCUC = new CourseUnitClass(classNumber, *this);
		newCUC->addStudent(s);
		s.addToCurrentlyAttending(*this, *newCUC);
	}
}

void OptionalCourseUnit::enrollStudent(Student &s) {
	this->addStudent(s);

	if (classes.empty()) {
		CourseUnitClass* newCUC = new CourseUnitClass(1, *this);
		newCUC->addStudent(s);
		s.addToCurrentlyAttending(*this, *newCUC);
	}
	else {
		priority_queue<CourseUnitClass*, vector<CourseUnitClass*>, CourseUnitClass::courseUnitCompare> pqTemp;
		CourseUnitClass* cucTemp = classes.top();
		cucTemp->addStudent(s);
		pqTemp.push(cucTemp);
		classes = pqTemp;
		s.addToCurrentlyAttending(*this, *cucTemp);
	}
}
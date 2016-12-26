#pragma once

#include "Student.h"
#include "Course.h"
#include "College.h"
#include "University.h"
#include "CourseUnit.h"
#include "CourseUnitClass.h"
#include "Tutor.h"
#include "Utilities.h"


Student::Student(string n, Date dob, Course& c, string s) 
	: CollegeUser(n, dob, c)
{
	personalStatus = s;
	collegeStatus = "Frequenting";
	course = &c;
	year = 1;
	assignID();
	assignEmail();
	assignTutor();
	c.addStudent(*this);
}

Student::Student(string n, Date dob, Date dor, Course& c, Tutor& t, unsigned short int y, string ps, string cs, map<CourseUnit*, unsigned short int> &ccu, map<CourseUnit*, CourseUnitClass*> &cca, unsigned long long int &id)
	: CollegeUser(n, dob, c),
	tutor(&t), year(y),  personalStatus(ps), collegeStatus(cs), completedCourseUnits(ccu), classesCurrentlyAtending(cca)
{
	course = &c;
	dateOfRegistration = dor;
	setID(id);
	assignEmail();
	map<CourseUnit*, CourseUnitClass*>::iterator mapIt;
	for (mapIt = cca.begin();
		mapIt != cca.end();
		mapIt++) {
		mapIt->first->addStudent(*this);
		mapIt->second->addStudent(*this);
	}
	t.tutorStudent(*this);
	if (this->collegeStatus == "Completed" || this->collegeStatus == "Suspended")
		c.addStudentToHashTable(*this);
	else
		c.addStudent(*this);
}

bool Student::assignTutor()
{
	vector<Tutor*>::iterator it = course->getProfessors().begin();
	vector<Tutor*>::iterator minimumStudents = it;
	if (course->getProfessors().size() == 0)
		return false;
	for (; it != course->getProfessors().end(); it++)
	{
		if ((*it)->getStudents().size() < (*minimumStudents)->getStudents().size())
			minimumStudents = it;
	}
	(*minimumStudents)->tutorStudent(*this);
	tutor = *minimumStudents;
	return true;
}

void Student::assignEmail()
{
	email = course->getCollege().getUniversity().getAcronym()
		+ to_string(ID)
		+ '@'
		+ course->getCollege().getAcronym()
		+ '.'
		+ course->getCollege().getUniversity().getAcronym()
		+ '.'
		+ course->getCollege().getUniversity().getCountryAcronym();
}

void Student::assignID()
{
	ID = dateOfRegistration.getYear() * 100000 + 1 + course->getCollege().getUniversity().getLastStudentID();
	course->getCollege().getUniversity().incrementLastStudentID();
}

bool Student::completedClass(CourseUnit& courseUnit, unsigned short int grade)
{
	if (grade >= 0 && grade <= 20) {
		//CHECK IF STUDENT IS TAKING THAT CLASS
		for (map<CourseUnit*, CourseUnitClass*>::iterator it = classesCurrentlyAtending.begin();
			it != classesCurrentlyAtending.end();
			it++)
		{
			if (it->first->getAcronym() == courseUnit.getAcronym())  //STUDENTS IS TAKING THE CLASS
			{
				if (grade >= 10) {
					completedCourseUnits.insert(pair<CourseUnit*, unsigned int>(&courseUnit, grade)); //STUDENT COMPLETED THE COURSE UNIT FOR THE FIRST TIME
				}

				this->classesCurrentlyAtending.at(&courseUnit)->removeStudent(*this);

				courseUnit.removeStudent(*this);

				classesCurrentlyAtending.erase(it);

				return true;
			}
		}	
	}

	return false;

	/*
	//CHECK IF STUDENT HAS COMPLETED THAT COURSE UNIT BEFORE
	for (map<CourseUnit*, unsigned short int>::iterator it = completedCourseUnits.begin();
		it != completedCourseUnits.end();
		it++)
	{
		if (it->first == &courseUnit) //STUDENT COMPLETED THE COURSE UNIT BEFORE
		{
			if (grade > it->second)  //WITH A LOWER GRADE
			{
				it->second = grade; //REPLACE GRADE
				return true;
			}
			else return true; //WITH THE SAME OR HIGHER GRADE
		}
	}*/

	
}

bool Student::completedAllCourseUnits(unsigned short int y)
{
	vector<CourseUnit*> courseUnitsYear = this->getCourse().getCourseUnits(y);
	double optionalCredits = 0.0;

	vector<CourseUnit*>::const_iterator cuIt;
	for (cuIt = courseUnitsYear.begin();
		cuIt != courseUnitsYear.end();
		cuIt++)
	{
		//MANDATORY
		MandatoryCourseUnit* mcu = dynamic_cast<MandatoryCourseUnit*>((*cuIt));
		if (mcu != NULL) {
			if (completedCourseUnits.find((*cuIt)) == completedCourseUnits.end()) {
				return false;
			}
		}
		//OPTIONAL
		else if (year != 4 && year != 5) 
		{
			 if (completedCourseUnits.find((*cuIt)) != completedCourseUnits.end())
				optionalCredits += (*cuIt)->getCredits();
		}
	}

	//MIEIC ONLY
	if (year != 4 && year != 5)
		return true;
	else if (year == 4 && optionalCredits >= 18)
		return true;
	else if (year == 5 && optionalCredits >= 24)
		return true;
	else return false;
}

vector<CourseUnit*> Student::getCourseUnitsAttending()
{
	vector<CourseUnit*> courseUnitsAttending;
	map<CourseUnit*, CourseUnitClass*>::iterator it;
	for (it = classesCurrentlyAtending.begin();
		it != classesCurrentlyAtending.end();
		it++
		)
	{
		courseUnitsAttending.push_back(it->first);
	}
	return courseUnitsAttending;
}

bool compareStudentByID(Student* s1, Student* s2)
{
	return s1->ID < s2->ID;
}

bool compareStudentByName(Student* s1, Student* s2)
{
	return s1->name < s2->name;
}

bool compareStudentByCouseYear(Student* s1, Student* s2)
{
	return s1->year < s2->year;
}

bool compareStudentByBirth(Student* s1, Student* s2)
{
	return s1->dateOfBirth < s2->dateOfBirth;
}

bool compareStudentByRegistration(Student* s1, Student* s2)
{
	return s1->dateOfRegistration < s2->dateOfRegistration;
}

ofstream& Student::operator<<(ofstream& file)
{
	file << this->course->getCollege().getUniversity().getAcronym()
		<< ';'
		<< this->course->getCollege().getAcronym()
		<< ';'
		<< this->course->getAcronym()
		<< ';'
		<< this->name
		<< ';'
		<< this->getDateOfBirth().getDateString()
		<< ';'
		<< this->getDateOfRegistration().getDateString()
		<< ';'
		<< this->personalStatus
		<< ';'
		<< this->collegeStatus
		<< ';'
		<< this->year
		<< ';'
		<< this->ID
		<< ';'
		<< this->tutor->getID()
		<< ';'
		<< '{';

	map<CourseUnit*, unsigned short>::const_iterator ccuIt;
	for (ccuIt = this->completedCourseUnits.begin();
		ccuIt != this->completedCourseUnits.end();
		ccuIt++)
	{
		file << '(' << ccuIt->first->getAcronym() << ',' << ccuIt->second << ')';
		map<CourseUnit*, unsigned short>::const_iterator it = this->completedCourseUnits.end();
		it--;
		if (ccuIt != it)
			file << ',';
	}

	file << '}'
		<< ';'
		<< '{';

	map<CourseUnit*, CourseUnitClass*>::const_iterator ccaIt;
	for (ccaIt = this->classesCurrentlyAtending.begin();
		ccaIt != this->classesCurrentlyAtending.end();
		ccaIt++)
	{
		file << '(' << ccaIt->first->getAcronym() << ',' << ccaIt->second->getClassNumber() << ')';
		map<CourseUnit*, CourseUnitClass*>::const_iterator it = this->classesCurrentlyAtending.end();
		it--;
		if (ccaIt != it)
			file << ',';
	}

	file << '}'
		<< endl;

	return file;
}

void Student::show() const{
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
		<< setw(CONSOLE_WIDTH * 0.5)
		<< tutor->getName()
		<< setw(CONSOLE_WIDTH * 0.3)
		<< year
		<< right
		<< endl
		<< '\t'
		<< dateOfBirth.getDateString()
		<< '\t'
		<< dateOfRegistration.getDateString()
		<< '\t'
		<< personalStatus
		<< '\t'
		<< collegeStatus
		<< endl;
}

void Student::showInDetail() const {
	cout
		<< "Name: " << name << endl << endl
		<< "ID: " << ID << endl << endl
		<< "Date of Birth: " << dateOfBirth.getDateString() << endl << endl
		<< "Date of Registration: " << dateOfRegistration.getDateString() << endl << endl
		<< "Year: " << year << endl << endl
		<< "Personal status: " << personalStatus << endl << endl
		<< "College status: " << collegeStatus << endl << endl
		<< "Course: " << course->getAcronym()
		<< " in " << course->getCollege().getAcronym() << " (" << course->getCollege().getUniversity().getAcronym() << ")" << endl << endl
		<< "Tutor: " << tutor->getName() << endl;
	
	if (completedCourseUnits.size() != 0) {
		cout << "\nCompleted course units:" << endl;
		map<CourseUnit*, unsigned short int>::const_iterator ccIt;
		for (ccIt = completedCourseUnits.begin();
			ccIt != completedCourseUnits.end();
			ccIt++) {
			cout << '\t'
				<< ccIt->first->getAcronym()
				<< setw(CONSOLE_WIDTH*0.5 - ccIt->first->getAcronym().size())
				<< ccIt->second << endl;
		}
	}
	else cout << "\nStudent has not completed any course units yet!\n";
	
		if (classesCurrentlyAtending.size() != 0) {
			map<CourseUnit*, CourseUnitClass*>::const_iterator caIt;
			cout << "\nClasses currently attending:" << endl;
			for (caIt = classesCurrentlyAtending.begin();
				caIt != classesCurrentlyAtending.end();
				caIt++) {
				cout << '\t'
					<< caIt->first->getAcronym()
					<< setw(CONSOLE_WIDTH*0.5 - caIt->first->getAcronym().size())
					<< caIt->second->getClassNumber() << endl;
			}
		}
		else cout << "\nStudent is not attending any classes!\n";
	
	cout << endl << endl;
}



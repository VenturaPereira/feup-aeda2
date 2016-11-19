#pragma once

#include "Student.h"
#include "Course.h"
#include "College.h"
#include "University.h"
#include "CourseUnit.h"
#include "CourseUnitClass.h"
#include "Tutor.h"
#include "Utilities.h"


Student::Student(string n, Date dob, Course& c) 
	: CollegeUser(n, dob, c)
{
	course = &c;
	year = 1;
	credits = double(0);
	assignID();
	assignEmail();
	assignTutor();
	c.addStudent(*this);
}

Student::Student(string n, Date dob, Course& c, Tutor& t, unsigned short int y, double cr, string s, map<CourseUnit*, unsigned short int> &ccu, map<CourseUnit*, CourseUnitClass*> &cca, unsigned long long int &id)
	: CollegeUser(n, dob, c),
	tutor(&t), year(y), credits(cr), status(s), completedCourseUnits(ccu), classesCurrentlyAtending(cca)
{
	course = &c;
	setID(id);
	assignEmail();
	map<CourseUnit*, CourseUnitClass*>::iterator mapIt;
	for (mapIt = cca.begin();
		mapIt != cca.end();
		mapIt++) 
	{
		mapIt->first->addStudentWithoutCheck(*this);
		mapIt->second->addStudent(*this);
	}
	t.tutorStudent(*this);
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

bool Student::enrollClass(CourseUnitClass& courseUnitClass)
{
	MandatoryCourseUnit* castIt = dynamic_cast<MandatoryCourseUnit*>(&(courseUnitClass.getCourseUnit()));
	if (castIt != NULL) //IT'S MANDATORY
	{
		//CHECK IF CLASS IS FULL
		if (courseUnitClass.getNumberOfStudents() < castIt->getMaxStudentsPerClass())
		{
			courseUnitClass.addStudent(*this);
			classesCurrentlyAtending.insert(pair<CourseUnit*, CourseUnitClass*>(&(courseUnitClass.getCourseUnit()), &courseUnitClass));
			return true;
		}
		else return false;
	}
	//IT'S OPTIONAL ADD THE STUDENT
	courseUnitClass.addStudent(*this); //ADD STUDENT TO CLASS
	classesCurrentlyAtending.insert(pair<CourseUnit*, CourseUnitClass*>(&(courseUnitClass.getCourseUnit()), &courseUnitClass));
	return true;

}

bool Student::enrollCourseUnit(CourseUnit& courseUnit)
{
	//FIND THE ARGUMENT IN THE VECTOR OF COURSE UNITS
	vector<CourseUnit*>::iterator itOfCourseUnit;
	for (itOfCourseUnit = course->getCourseUnits().begin();
		itOfCourseUnit != course->getCourseUnits().end();
		itOfCourseUnit++)
	{
		if (*itOfCourseUnit == &courseUnit)
			break;
	}

	if (itOfCourseUnit == course->getCourseUnits().end()) //THERE IS NO COURSE UNIT IN THE VECTOR THAT MATCHES THE ARGUMENT 
		throw NotFound<CourseUnit*, string>(courseUnit.getName());

	if (courseUnit.addStudent(*this)) //TRY TO ADD STUDENT TO COURSE UNIT
	{
		vector<CourseUnitClass*>::iterator itCourseUnitClass;
		for (itCourseUnitClass = (*itOfCourseUnit)->getClasses().begin();
			itCourseUnitClass != (*itOfCourseUnit)->getClasses().end();
			itCourseUnitClass++)
		{
			if (enrollClass(*(*itCourseUnitClass))) //TRY TO ADD STUDENT TO CLASS
				return true;
		}
	}
	else return false; //NOT POSSIBLE TO ADD STUDENT TO COURSE UNIT (COURSE UNIT IS OPTIONAL)


	//ALL CLASSES WERE FULL - CREATE A NEW CLASS AND ADD THE STUDENT
	MandatoryCourseUnit* castIt = dynamic_cast<MandatoryCourseUnit*>(&courseUnit);
	if (castIt != NULL) //IT'S MANDATORY
	{
		CourseUnitClass* newClass = new CourseUnitClass(courseUnit.getNumberClasses() + 1, courseUnit);
		courseUnit.addCourseUnitClass(*newClass);
		enrollClass(*newClass);
		return true;
	}
	else //IT'S OPTIONAL
	{
		OptionalCourseUnit* castIt = dynamic_cast<OptionalCourseUnit*>(&courseUnit);
		if (castIt->getClasses().size() == 0) //THERE ARE NO CLASSES, CREATE ONE
		{
			CourseUnitClass* newClass = new CourseUnitClass(courseUnit.getNumberClasses() + 1, courseUnit);
			courseUnit.addCourseUnitClass(*newClass);
			enrollClass(*newClass);
			return true;
		}
		else return false; //THERE IS A CLASS AND IT'S FULL
	}
}

bool Student::completedClass(CourseUnit& courseUnit, unsigned short int grade)
{
	//CHECK IF GRADE IS ACCEPTABLE
	if (grade < 10)
		return false;
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
	}

	completedCourseUnits.insert(pair<CourseUnit*, unsigned int>(&courseUnit, grade)); //STUDENT COMPLETED THE COURSE UNIT FOR THE FIRST TIME
	return true;
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

ofstream& operator<<(ofstream& file, Student *s)
{
	file << s->course->getCollege().getUniversity().getAcronym()
		<< ';'
		<< s->course->getCollege().getAcronym()
		<< ';'
		<< s->course->getAcronym()
		<< ';'
		<< s->name
		<< ';'
		<< s->getDateOfBirth().getDateString()
		<< ';'
		<< s->status
		<< ';'
		<< s->credits
		<< ';'
		<< s->year
		<< ';'
		<< s->ID
		<< ';'
		<< s->tutor->getID()
		<< ';'
		<< '{';

	map<CourseUnit*, unsigned short>::const_iterator ccuIt;
	for (ccuIt = s->completedCourseUnits.begin();
		ccuIt != s->completedCourseUnits.end();
		ccuIt++)
	{
		file << '(' << ccuIt->first->getAcronym() << ',' << ccuIt->second << ')';
		map<CourseUnit*, unsigned short>::const_iterator it = s->completedCourseUnits.end();
		it--;
		if (ccuIt != it)
			file << ',';
	}

	file << '}'
		<< ';'
		<< '{';

	map<CourseUnit*, CourseUnitClass*>::const_iterator ccaIt;
	for (ccaIt = s->classesCurrentlyAtending.begin();
		ccaIt != s->classesCurrentlyAtending.end();
		ccaIt++)
	{
		file << '(' << ccaIt->first->getAcronym() << ',' << ccaIt->second->getClassNumber() << ')';
		map<CourseUnit*, CourseUnitClass*>::const_iterator it = s->classesCurrentlyAtending.end();
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
		<< status
		<< endl;
}


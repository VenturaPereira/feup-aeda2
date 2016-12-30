#pragma once

#include "CourseUnitClass.h"
#include "CourseUnit.h"
#include "College.h"
#include "Course.h"
#include "University.h"
#include "Tutor.h"
#include "Utilities.h"
#include "Student.h"

CourseUnitClass::CourseUnitClass(unsigned short int cn, CourseUnit& cu) : courseUnit(&cu), classNumber(cn) {
	assignTeacher();
	cu.addCourseUnitClass(*this);
}

void CourseUnitClass::assignTeacher()
{
	vector<Tutor*>::iterator it;
	for (it = getCourseUnit().getCourse().getProfessors().begin();
		it != getCourseUnit().getCourse().getProfessors().end();
		it++
		)
	{
		if ((*it)->teachClass(*this)) {
			setProfessor(*(*it));
			return;
		}
	}

}

CourseUnitClass::CourseUnitClass(unsigned short int cn, CourseUnit& cu, Tutor& t)
	: courseUnit(&cu), classNumber(cn)
{
	professor = &t;
	cu.addCourseUnitClass(*this);
}

void CourseUnitClass::addStudent(Student& s)
{
	studentsInClass.push_back(&s);
}

bool CourseUnitClass::removeStudent(Student& s) {
	for (vector<Student *> ::const_iterator it = studentsInClass.begin(); it != studentsInClass.end(); it++) {
		if ((*it) == &s) {
			studentsInClass.erase(it);
			return true;
		}
	}
	return false;
}

void CourseUnitClass::setProfessor(Tutor& t)
{
	professor = &t;
}

bool compareCourseUnitClassByNumber(CourseUnitClass* cuc1, CourseUnitClass* cuc2)
{
	return (cuc1->classNumber < cuc2->classNumber);
}

bool compareCourseUnitClassByNumberStudents(CourseUnitClass* cuc1, CourseUnitClass* cuc2)
{
	return (cuc1->getNumberOfStudents() < cuc2->getNumberOfStudents());
}

bool compareCourseUnitClassBySpace(CourseUnitClass* cuc1, CourseUnitClass* cuc2) {
	MandatoryCourseUnit* castMl = dynamic_cast<MandatoryCourseUnit*>(&cuc1->getCourseUnit());
	MandatoryCourseUnit* castMr = dynamic_cast<MandatoryCourseUnit*>(&cuc2->getCourseUnit());
	if (castMl == castMr) {
		if (castMr != NULL && castMl != NULL) { //IT'S MANDATORY
			return
				(castMl->getMaxStudentsPerClass() - cuc1->getNumberOfStudents())
				< (castMr->getMaxStudentsPerClass() - cuc2->getNumberOfStudents());
		}
		else {
			OptionalCourseUnit* castOl = dynamic_cast<OptionalCourseUnit*>(&cuc1->getCourseUnit());
			OptionalCourseUnit* castOr = dynamic_cast<OptionalCourseUnit*>(&cuc2->getCourseUnit());
			if (castMl == castMr) {
				if (castMr != NULL && castMl != NULL) { //IT'S OPTIONAL
					return
						(castOl->getMaxStudents() - cuc1->getNumberOfStudents())
						< (castOr->getMaxStudents() - cuc2->getNumberOfStudents());
				}
				else return false;
			}
			else return false;
		}
	}
	else return false;
}

ofstream& CourseUnitClass::operator<<(ofstream& file)
{
	file << this->getCourseUnit().getCourse().getCollege().getUniversity().getAcronym()
		<< ';'
		<< this->getCourseUnit().getCourse().getCollege().getAcronym()
		<< ';'
		<< this->getCourseUnit().getCourse().getAcronym()
		<< ';'
		<< this->getCourseUnit().getAcronym()
		<< ';'
		<< this->classNumber
		<< ';'
		<< this->professor->getID()
		<< endl;

	return file;
}

void CourseUnitClass::show() const
{
	cout
		<< left
		<< setw(CONSOLE_WIDTH * 0.5)
		<< courseUnit->getName()
		<< '\t'
		<< classNumber
		<< '\t'
		<< setw(CONSOLE_WIDTH * 0.5)
		<< professor->getName()
		<< '\t'
		<< getNumberOfStudents()
		<< right
		<< endl;
}

bool CourseUnitClass::courseUnitCompare::operator()(CourseUnitClass *l, CourseUnitClass *r) {
	MandatoryCourseUnit* castMl = dynamic_cast<MandatoryCourseUnit*>(&l->getCourseUnit());
	MandatoryCourseUnit* castMr = dynamic_cast<MandatoryCourseUnit*>(&r->getCourseUnit());
	if (castMl == castMr) {
		if (castMr != NULL && castMl != NULL) { //IT'S MANDATORY
			return
				(castMl->getMaxStudentsPerClass() - l->getNumberOfStudents())
				< (castMr->getMaxStudentsPerClass() - r->getNumberOfStudents());
		}
		else {
			OptionalCourseUnit* castOl = dynamic_cast<OptionalCourseUnit*>(&l->getCourseUnit());
			OptionalCourseUnit* castOr = dynamic_cast<OptionalCourseUnit*>(&r->getCourseUnit());
			if (castMl == castMr) {
				if (castMr != NULL && castMl != NULL) { //IT'S OPTIONAL
					return
						(castOl->getMaxStudents() - l->getNumberOfStudents())
						< (castOr->getMaxStudents() - r->getNumberOfStudents());
				}
				else return false;
			}
			else return false;
		}
	}
	else return false;
}

bool CourseUnitClass::hasSpace() {
	MandatoryCourseUnit* castM = dynamic_cast<MandatoryCourseUnit*>(&this->getCourseUnit());
	if (castM != NULL) { //IT'S MANDATORY
		return
			(castM->getMaxStudentsPerClass() - this->getNumberOfStudents()) > 0;
	}
	else {
		OptionalCourseUnit* castO = dynamic_cast<OptionalCourseUnit*>(&this->getCourseUnit());
		if (castO != NULL) { //IT'S OPTIONAL
			return
				(castO->getMaxStudents() - this->getNumberOfStudents()) > 0;
		}
		else return false;
	}
}

unsigned int CourseUnitClass::getSpaceAvailable() {
	MandatoryCourseUnit* castM = dynamic_cast<MandatoryCourseUnit*>(&this->getCourseUnit());
	if (castM != NULL) { //IT'S MANDATORY
		return
			(castM->getMaxStudentsPerClass() - this->getNumberOfStudents());
	}
	else {
		OptionalCourseUnit* castO = dynamic_cast<OptionalCourseUnit*>(&this->getCourseUnit());
		if (castO != NULL) { //IT'S OPTIONAL
			return
				(castO->getMaxStudents() - this->getNumberOfStudents());
		}
	}
	return 0;
}

void CourseUnitClass::showInDetail() {
	
	cout << "Course Unit: " << this->courseUnit->getAcronym() << endl
		<< "Class Number: " << this->classNumber << endl
		<< "Professor: " << this->professor->getName() << endl
		<< "Number of Students: " << this->getNumberOfStudents() << endl
		<< "Space available: " << this->getSpaceAvailable() << endl;
	if (getNumberOfStudents() > 0) {
		cout << "Students in Class:\n";
		for (size_t i = 0; i < getNumberOfStudents(); i++)
			cout << '\t' << this->studentsInClass[i]->getName();
	}
	cout << endl;
}
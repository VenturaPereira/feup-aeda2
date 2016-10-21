#pragma once
#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>

#include "College.h"
using namespace std;

class Tutor;
class CourseUnit;
class Student;

//ADICIONAR MESTRADO/LICENCIATURAS/DOUTURAMENTOS COMO CLASSES DERIVADAS


class Course
{
private:
	//MEMBER VARIABLES
	const string name, acronym;
	vector<CourseUnit*> courseUnits;
	vector<Student*> students;
	vector<Tutor*> professors;
	College* college;

public:
	//MEMBER FUNCTIONS
	Course(string n, string a, College* c) : name(n), acronym(a), college(c) {}
	void addCourseUnit(CourseUnit* cu);
	void removeCourseUnit(CourseUnit* cu);
	void addStudent(Student* s);
	void removeStudent(Student* s);
	void addProfessor(Tutor* s);
	void removeProfessor(Tutor* s);

	//GETS
	string getName() const { return name; }
	string getAcronym() const { return acronym; }
	vector<CourseUnit*> getCourseUnits() const { return courseUnits; }
	vector<Student*> getStudents() const { return students; }
	vector<Tutor*> getProfessors() const { return professors; }
	College* getCollege() const { return college; }

};

#endif
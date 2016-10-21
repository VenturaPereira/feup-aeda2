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
	friend class Student;
	friend class CourseUnit;
public:
	string name, acronym;
	vector<CourseUnit*> courseUnits;
	vector<Student*> students;
	vector<Tutor*> professors;
	College* college;

	Course(string n, string a) : name(n), acronym(a) {}
};

#endif
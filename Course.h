#pragma once
#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>
using namespace std;

class College;
class Tutor;
class CourseUnit;
class Student;
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
	Course(string n, string a, College* c);
	void addCourseUnit(CourseUnit* cu);
	bool removeCourseUnit(CourseUnit* cu);
	void addStudent(Student* s);
	bool removeStudent(Student* s);
	void addProfessor(Tutor* p);
	bool removeProfessor(Tutor* p);

	//COMPARES
	friend bool compareCourseByName(Course* c1, Course* c2);


	//GETS
	string getName() const { return name; }
	string getAcronym() const { return acronym; }
	vector<CourseUnit*> getCourseUnits() const { return courseUnits; }
	vector<Student*> getStudents() const { return students; }
	vector<Tutor*> getProfessors() const { return professors; }
	College* getCollege() const { return college; }
	vector<CourseUnit*> getCourseUnits(unsigned short int y);
	vector<CourseUnit*> getCourseUnitsNotCompleted(Student* s, unsigned short int y);
};

#endif
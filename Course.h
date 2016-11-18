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
	vector<CourseUnit*>& getCourseUnits() { return courseUnits; }
	vector<Student*>& getStudents() { return students; }
	vector<Tutor*>& getProfessors() { return professors; }
	College*& getCollege() { return college; }
	vector<CourseUnit*> getCourseUnits(unsigned short int y);
	vector<CourseUnit*> getCourseUnitsNotCompleted(Student* s, unsigned short int y);

	//PRINT TO SCREEN
	void show() const;
	void showAllCourseUnits() const;
	
	//OPERATORS
	friend ofstream& operator<<(ofstream &file, Course *c);
};

#endif
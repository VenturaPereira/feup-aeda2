#pragma once

#ifndef ENROLLMENTSYSTEM_H
#define ENROLLMENTSYSTEM_H

class University;
class College;
class Course;
class CourseUnit;
class CourseUnitClass;
class Student;
class Tutor;
class Date;

#include <vector>
#include <string>
using namespace std;

/*!
*	Class for the Whole System
*/
class EnrollmentSystem
{
private:
	//MEMBER VARIABLES
	const unsigned int MAXIMUM_CREDITS;
	string universityFile = "universities.txt",
		collegesFile = "colleges.txt",
		coursesFile = "courses.txt",
		courseUnitsFile = "courseunits.txt",
		courseUnitClassesFile = "courseunitclasses.txt",
		studentsFile = "students.txt",
		professorsFile = "tutors.txt";
	vector<University*> universitiesVector;

	//SORTING OPTIONS (POINTERS TO THE SORTING FUNCTIONS)
	bool(*universitySortOption)(University* l, University* r);
	bool(*collegeSortOption)(College* l, College* r);
	bool(*courseSortOption)(Course* l, Course* r);
	bool(*courseUnitSortOption)(CourseUnit* l, CourseUnit* r);
	bool(*courseUnitClassSortOption)(CourseUnitClass* l, CourseUnitClass* r);
	bool(*studentsSortOption)(Student* l, Student* r);
	bool(*professorsSortOption)(Tutor* l, Tutor* r);

		
public:
	//MEMBER FUNCTIONS
	/*!
	*	EnrollmentSystem Constructor with given Maximum Credits
	*/
	EnrollmentSystem(unsigned int mc);

	/*!
	*	EnrollmentSystem Destructor
	*/
	~EnrollmentSystem() {}

	/*!
	*	Adds a University to the System
	*/
	void addUniversity(University& u) { universitiesVector.push_back(&u); }

	/*!
	*	Removes a University from the System
	*/
	void removeUniversity(University& u);

	//PRINT TO SCREEN
	/*!
	*	Prints to the screen All Universities
	*/
	void showUniversities();

	/*!
	*	Prints to the screen All Colleges
	*/
	void showColleges();

	/*!
	*	Prints to the screen All Courses
	*/
	void showCourses();

	/*!
	*	Prints to the screen All Course Units
	*/
	void showCourseUnits();

	/*!
	*	Prints to the screen All Course Units Classes
	*/
	void showCourseUnitClasses();	

	/*!
	*	Prints to the screen All Professors
	*/
	void showProfessors();

	/*!
	*	Prints to the screen All Students
	*/
	void showStudents();

	/*!
	*	Prints to the screen Detailed Information about a Student
	*/
	void showStudentInDetail();
	
	/*!
	*	Prints to the screen Detailed Information about a Course Unit
	*/
	void showCourseUnitInDetail();

	/*!
	*	Template Function To Save All Data Into Files
	*/
	template<class T>
	friend void saveToFiles(vector<T*> const &vector, string &fileName)
	{
		ofstream file;
		file.open(fileName);
		for (unsigned int i = 0; i < vector.size(); i++)
			(*vector[i]).operator<<(file);
		file.close();
	}

	//HANDLERS (COMMUNICATION WITH THE USER)
	/*!
	* Adds Students to Course
	*/
	friend bool addStudentHandler(EnrollmentSystem& s); 

	/*!
	*	Removes Students from Course
	*/
	friend bool removeStudentHandler(EnrollmentSystem& s); 

	/*!
	*	Shows Course Units available to Enroll and Adds a Student to them
	*/
	friend bool enrollmentHandler(EnrollmentSystem& s); 

	/*!
	*	Grades the Student if the grade is high enough(>= 10), and removes the Student from the Course Unit
	*/
	friend bool studentFinishedCourseUnitHandler(EnrollmentSystem& s);

	/*!
	*	Tries to Remove University
	*/
	friend bool removeUniversityHandler(EnrollmentSystem& s);


	//LOAD AND SAVE FROM FILES

	/*!
	*	Calls All Load Functions to get All Data from the .txt
	*/
	void loadHandler();

	/*!
	*	Calls All Saving Functions to store All Data to the .txt
	*/
	void saveHandler();

	/*!
	*	Loads All Students (students.txt)
	*/
	void loadStudents();

	/*!
	*	Loads All Professors (tutors.txt)
	*/
	void loadProfessors();

	/*!
	*	Loads All Course Unit Classes (courseunitclasses.txt)
	*/
	void loadCourseUnitClasses();

	/*!
	*	Loads All Universities (universities.txt)
	*/
	void loadUniversities();

	/*!
	*	Loads All Colleges (colleges.txt)
	*/
	void loadColleges();

	/*!
	*	Loads All Courses (courses.txt)
	*/
	void loadCourses();

	/*!
	*	Loads All Course Units (courseunits.txt)
	*/
	void loadCourseUnits();
	
	
	//SORT FUNCTIONS
	/*!
	*	Changes the Sorting Option for Course Units
	*/
	bool changeCourseUnitSortOption(unsigned int &option);

	/*!
	*	Changes the Sorting Option for Course Units Classes
	*/
	bool changeCourseUnitClassSortOption(unsigned int &option);

	/*!
	*	Changes the Sorting Option for Students
	*/
	bool changeStudentsSortOption(unsigned int &option);

	/*!
	*	Changes the Sorting Option for Professors
	*/
	bool changeProfessorsSortOption(unsigned int &option);

	//GETS

	/*!
	*	Returns Maximum Credits of the System
	*/
	unsigned int getMaxCredits() const { return MAXIMUM_CREDITS; }

	/*!
	*	Returns All Universities in the System
	*/
	vector<University*>& getUniversities() { return universitiesVector; }

	/*!
	*	Returns the University chosen by the User
	*/
	friend University& getUniversity(EnrollmentSystem &s);

	/*!
	*	Returns the College chosen by the User
	*/
	friend College& getCollege(EnrollmentSystem &s);

	/*!
	*	Returns the Course chosen by the User
	*/
	friend Course& getCourse(EnrollmentSystem &s);

	/*!
	*	Returns the Course Unit chosen by User
	*/
	friend CourseUnit& getCourseUnitUser(EnrollmentSystem &s);

	/*!
	*	Returns the Student with a given ID
	*/
	Student& getStudent(unsigned long long int &ID);

	/*!
	*	Returns the Professor with a given ID and a Course
	*/
	Tutor& getProfessor(unsigned long long int &ID, Course& course);

	/*!
	*	Returns the University with a given Acronym
	*/
	University& getUniversity(string &acronym);

	/*!
	*	Returns the College with a given Acronym and University
	*/
	College& getCollege(string &acronym, University& university);

	/*!
	*	Returns the Course with a given Acronym and College
	*/
	Course& getCourse(string &acronym, College& college);

	/*!
	*	Returns the Course Unit with a givem Acronym and Course
	*/
	CourseUnit& getCourseUnit(string &acronym, Course& course);

	/*!
	*	Returns the Course Unit Class with a given Class Number and a Course Unit
	*/
	CourseUnitClass& getCourseUnitClass(unsigned int &classNumber, CourseUnit& courseUnit);

	/*!
	*	Returns All Colleges
	*/
	vector<College*> getAllColleges();

	/*!
	*	Returns All Courses
	*/
	vector<Course*> getAllCourses();

	/*!
	*	Returns All Course Units
	*/
	vector<CourseUnit*> getAllCourseUnits();

	/*!
	*	Returns All Course Units Classes
	*/
	vector<CourseUnitClass*> getAllCourseUnitClasses();

	/*!
	*	Returns All Students
	*/
	vector<Student*> getAllStudents();

	/*!
	*	Returns All Professors
	*/
	vector<Tutor*> getAllProfessors();

	Tutor& getProfessor(unsigned long long int &ID);
	
	//MEETINGS
	void addMeetingHandler();

	void removeMeetingHandler();

	void changeMeetingDescriptionHandler();
};

#endif
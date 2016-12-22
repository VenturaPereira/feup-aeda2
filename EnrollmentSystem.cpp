#pragma once

#include "EnrollmentSystem.h"
#include "Utilities.h"
#include "University.h"
#include "College.h"
#include "Course.h"
#include "CourseUnit.h"
#include "Date.h"
#include "Student.h"
#include "CourseUnitClass.h"
#include "Tutor.h"


EnrollmentSystem::EnrollmentSystem(unsigned int mc) : MAXIMUM_CREDITS(mc)
{
	loadHandler();
	//LOAD DEFAULT SORTING OPTIONS
	courseSortOption = &compareCourseByName;
	courseUnitSortOption = &compareCourseUnitByTime;
	courseUnitClassSortOption = &compareCourseUnitClassByNumber;
	studentsSortOption = &compareStudentByID;
	professorsSortOption = &compareProfessorByID;
	universitySortOption = &compareUniversityByName;
	collegeSortOption = &compareCollegeByName;
}

void EnrollmentSystem::loadHandler() {
	loadUniversities();
	loadColleges();
	loadCourses();
	loadCourseUnits();
	loadProfessors();
	loadCourseUnitClasses();
	loadStudents();
}

void EnrollmentSystem::loadUniversities() {
	
	/*
	FORMAT
	NAME;ACRONYM;COUNTRY_ACRONYM;LAST_STUDENT_ID;LAST_PROFESSOR_ID
	*/
	string line;
	ifstream file;

	file.open(universityFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			string name, acr, country;
			char delimiter = ';';
			unsigned long long int lsid, lpid;
			istringstream iss(line);

			getline(iss, name, delimiter);
			getline(iss, acr, delimiter);
			getline(iss, country, delimiter);
			iss >> ws >> lsid >> ws >> delimiter >> ws >> lpid;

			addUniversity(*(new University(name, acr, country, lsid, lpid)));
		}
		file.close();
	}
}

void EnrollmentSystem::loadColleges(){
	
	/*
	FORMAT
	UNIVERSITY_ACRONYM;NAME;ACRONYM
	*/

	ifstream file;
	string line, uni, name, acr;
	University* uniPtr;
	char ch = ';';

	file.open(collegesFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream iss(line);
			getline(iss, uni, ch);
			getline(iss, name, ch);
			getline(iss, acr, '\n');
			try {
				uniPtr = &getUniversity(uni);
			}
			catch (...){
				continue;
			}
			new College(name, acr, *uniPtr);
		}
		file.close();
	}
}

void EnrollmentSystem::loadCourses() {

	/*
	FORMAT
	UNIVERSITY_ACRONYM;COLLEGE_ACRONYM;NAME;ACRONYM
	*/

	ifstream file;
	string line, uni, col, name, acr;
	char ch = ';';
	College *collegePtr;
	University* uniPtr;

	file.open(coursesFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream iss(line);
			getline(iss, uni, ch);
			getline(iss, col, ch);
			getline(iss, name, ch);
			getline(iss, acr, '\n');

			try {
				uniPtr = &getUniversity(uni);
				collegePtr = &getCollege(col, *uniPtr);
			}
			catch (...)	{
				continue;
			}

			new Course(name, acr, *collegePtr);

		}

		file.close();
	}
}

void EnrollmentSystem::loadCourseUnits()
{
	/*
	FORMAT
	UNIVERSITY_ACRONYM;COLLEGE_ACRONYM;COURSE_ACRONYM;NAME;ACRONYM;MANDATORY;MAX_NUM_STUDENTS_PER_CLASS;YEAR;SEMESTER;CREDITS

	or

	UNIVERSITY_ACRONYM;COLLEGE_ACRONYM;COURSE_ACRONYM;NAME;ACRONYM;OPTIONAL;MAX_NUM_STUDENTS;SCIENTIFIC_AREA;YEAR;SEMESTER;CREDITS
	*/

	ifstream file;
	string line, uni, col, course, name, acr, type, scientificArea;
	unsigned short int year, semester, max_num_students_per_class, max_num_students;
	double credits;
	char ch = ';';
	Course* coursePtr;

	file.open(courseUnitsFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream iss(line);
			getline(iss, uni, ch);
			getline(iss, col, ch);
			getline(iss, course, ch);
			getline(iss, name, ch);
			getline(iss, acr, ch);

			try {
				University* uniPtr = &getUniversity(uni);
				College* collegePtr = &getCollege(col, *uniPtr);
				coursePtr = &getCourse(course, *collegePtr);
			}
			catch (...) {
				continue;
			}
			
			getline(iss, type, ch);

			if (type == "Mandatory") {
				iss >> ws >> max_num_students_per_class
					>> ws >> ch
					>> ws >> year
					>> ws >> ch
					>> ws >> semester
					>> ws >> ch
					>> ws >> credits;
				new MandatoryCourseUnit(max_num_students_per_class, name, acr, *coursePtr, year, semester, credits);
			}
			else if (type == "Optional") {
				iss >> ws >> max_num_students
					>> ws >> ch;
				getline(iss, scientificArea, ch);
				iss	>> ws >> year
					>> ws >> ch
					>> ws >> semester
					>> ws >> ch
					>> ws >> credits;
				new OptionalCourseUnit(max_num_students, name, acr, *coursePtr, year, semester, scientificArea, credits);
			}
			else continue;

		}

		file.close();
	}

}

void EnrollmentSystem::loadCourseUnitClasses() 
{
	/*
	FORMAT
	UNIVERSITY_ACRONYM;COLLEGE_ACRONYM;COURSE_ACRONYM;COURSE_UNIT_ACRONYM;CLASS_NUMBER;PROFESSOR_ID
	*/

	ifstream file;
	string line, uni, col, course, courseUnit;
	unsigned short int classNumber;
	unsigned long long int professor_id;
	char ch = ';';
	CourseUnit* courseUnitPtr;
	Course* coursePtr;
	Tutor* professor;

	file.open(courseUnitClassesFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			istringstream iss(line);
			getline(iss, uni, ch);
			getline(iss, col, ch);
			getline(iss, course, ch);
			getline(iss, courseUnit, ch);
			
			try {
				University* uniPtr = &getUniversity(uni);
				College* collegePtr = &getCollege(col, *uniPtr);
				coursePtr = &getCourse(course, *collegePtr);
				courseUnitPtr = &getCourseUnit(courseUnit, *coursePtr);
			}
			catch (...) {
				continue;
			}

			iss >> ws >> classNumber
				>> ws >> ch
				>> ws >> professor_id;

			try {
				professor = &getProfessor(professor_id, *coursePtr);
			}
			catch (...) {
				continue;
			}

			new CourseUnitClass(classNumber, *courseUnitPtr, *professor);
		}

		file.close();
	}

}

void EnrollmentSystem::loadStudents() {
	
	/*
	FORMAT
	UNIVERSITY_ACRONYM;COLLEGE_ACRONYM;COURSE_ACRONYM;NAME;BIRTH_DATE;DATE_OF_REGISTRATION;STATUS;CREDITS;YEAR;ID;TUTOR_ID;
	{(COMPLETED_COURSE_UNIT, GRADE),(COMPLETED_COURSE_UNIT, GRADE),(COMPLETED_COURSE_UNIT, GRADE),...};
	{(ATTENDING_COURSE_UNIT, CLASS_NUMBER),(ATTENDING_COURSE_UNIT, CLASS_NUMBER),(ATTENDING_COURSE_UNIT, CLASS_NUMBER),...}
	*/
		
	ifstream file;
	string line, uni, col, course, name, dateStr, status, ccuStr, ccaStr;
	unsigned long long int ID, tutor_ID;
	unsigned short int year;
	double credits;
	Tutor* tutorPtr;
	Course* coursePtr;
	map<CourseUnit*, unsigned short int> ccu;
	map<CourseUnit*, CourseUnitClass*> cca;

	file.open(studentsFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			char ch = ';';
			istringstream iss(line);
			getline(iss, uni, ch);
			getline(iss, col, ch);
			getline(iss, course, ch);
			getline(iss, name, ch);
			getline(iss, dateStr, ch);
			Date birthDate(dateStr); 
			getline(iss, dateStr, ch);
			Date dateOfRegistration(dateStr);
			getline(iss, status, ch);
			iss >> ws >> credits
				>> ws >> ch
				>> ws >> year
				>> ws >> ch
				>> ws >> ID
				>> ws >> ch
				>> ws >> tutor_ID
				>> ws >> ch;


			try {
				University* uniPtr = &getUniversity(uni);
				College* colPtr = &getCollege(col, *uniPtr);
				coursePtr = &getCourse(course, *colPtr);
				tutorPtr = &getProfessor(tutor_ID, *coursePtr);

				getline(iss, ccuStr, ch);
				ccuStr.erase(0, 1); //REMOVES '{'
				ccuStr.erase(ccuStr.size() - 1, 1); //REMOVES '}'
				istringstream iss_2(ccuStr);
				char endCh;
				string pair;
				bool firstIt = true;

				while (getline(iss_2, pair, ')'))
				{
					if (!firstIt)
						pair.erase(0, 1); //REMOVE ',' IF NOT THE FIRST ITERATION
					else firstIt = false;
					string courseUnitStr;
					unsigned short int grade;
					pair.erase(0,1); //REMOVES '('
					istringstream iss_3(pair);
					getline(iss_3, courseUnitStr, ','); //GETS THE COURSE UNIT STR
					iss_3 >> grade; //GETS THE GRADE

					CourseUnit* courseUnitPtr = &getCourseUnit(courseUnitStr, *coursePtr);

					ccu.insert(std::pair<CourseUnit*, unsigned short int>(courseUnitPtr, grade));
				}

				getline(iss, ccaStr, '\n');
				ccaStr.erase(0, 1); //REMOVES '{'
				ccaStr.erase(ccaStr.size() - 1, 1); //REMOVES '}'
				istringstream iss_4(ccaStr);
				firstIt = true;

				while (getline(iss_4, pair, ')'))
				{
					if (!firstIt)
						pair.erase(0,1); //REMOVE ',' IF NOT THE FIRST ITERATION
					else firstIt = false;
					string courseUnitStr;
					unsigned int classNumber;
					pair.erase(0, 1); //REMOVES '('
					istringstream iss_5(pair);
					getline(iss_5, courseUnitStr, ','); //GETS THE COURSE UNIT STR
					iss_5 >> classNumber; //GETS THE CLASS NUMBER

					CourseUnit* courseUnitPtr = &getCourseUnit(courseUnitStr, *coursePtr);

					cca.insert(std::pair<CourseUnit*, CourseUnitClass*>(
						courseUnitPtr,
						&getCourseUnitClass(classNumber, *courseUnitPtr)));
				}


			}
			catch (...) {
				continue;
			}
			new Student(name, birthDate, dateOfRegistration, *coursePtr, *tutorPtr, year, credits, status, ccu, cca, ID);
		}
	
	file.close();
	}
}

void EnrollmentSystem::loadProfessors()
{
	/*
	FORMAT
	UNIVERSITY_ACRONYM;COLLEGE_ACRONYM;COURSE_ACRONYM;NAME;BIRTH_DATE;DATE_OF_REGISTRATION;ID;
	{ABLE_TO_TEACH,ABLE_TO_TEACH,ABLE_TO_TEACH,...};
	{TEACHING,TEACHING,TEACHING,...};
	*/

	ifstream file;
	string line, uni, col, course, name, dateStr, ableToTeachStr, teachingStr;
	unsigned long long int ID;
	Course* coursePtr;
	vector<CourseUnit*> ableToTeach, currentlyTeaching;

	file.open(professorsFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			ableToTeach.clear();
			currentlyTeaching.clear();

			char ch = ';';
			istringstream iss(line);
			getline(iss, uni, ch);
			getline(iss, col, ch);
			getline(iss, course, ch);
			getline(iss, name, ch);
			getline(iss, dateStr, ch);
			Date birthDate(dateStr);
			getline(iss, dateStr, ch);
			Date dateOfRegistration(dateStr);
			iss >> ws >> ID >> ws >> ch;


			try {
				University* uniPtr = &getUniversity(uni);
				College* colPtr = &getCollege(col, *uniPtr);
				coursePtr = &getCourse(course, *colPtr);

				getline(iss, ableToTeachStr, ch);
				ableToTeachStr.erase(0, 1); //REMOVE '{'
				ableToTeachStr.erase(ableToTeachStr.size()-1, 1); //REMOVE '}'
				istringstream iss_2(ableToTeachStr);
				string courseUnitStr;
				char endCh;

				while (getline(iss_2, courseUnitStr, ',')){
					CourseUnit* courseUnitPtr = &getCourseUnit(courseUnitStr, *coursePtr);
					ableToTeach.push_back(courseUnitPtr);
				}

				getline(iss, teachingStr, '\n');
				teachingStr.erase(0, 1); //REMOVE '{'
				teachingStr.erase(teachingStr.size() - 1, 1); //REMOVE '}'
				istringstream iss_4(teachingStr);

				while (getline(iss_4, courseUnitStr, ',')){
					CourseUnit* courseUnitPtr = &getCourseUnit(courseUnitStr, *coursePtr);
					currentlyTeaching.push_back(courseUnitPtr);
				}
				
			}
			catch (...) {
				continue;
			}
			new Tutor(name, birthDate, dateOfRegistration, *coursePtr, ID, currentlyTeaching, ableToTeach);
		}

		file.close();
	}
}

University& EnrollmentSystem::getUniversity(string &acronym)
{
	vector<University*>::iterator it;
	for (it = universitiesVector.begin(); it != universitiesVector.end(); it++){
		if ((*it)->getAcronym() == acronym)
			return *(*it);
	}
	throw NotFound<University*, string>(acronym);
}

College& EnrollmentSystem::getCollege(string &acronym, University& university)
{
	vector<College*>::iterator it;
	for (it = university.getColleges().begin();
		it != university.getColleges().end();
		it++) {
		if ((*it)->getAcronym() == acronym)
			return *(*it);
	}
	throw NotFound<College*, string>(acronym);
}

Course& EnrollmentSystem::getCourse(string &acronym, College& college)
{
	vector<Course*>::iterator it;
	for (it = college.getCourses().begin(); it != college.getCourses().end(); it++) {
		if ((*it)->getAcronym() == acronym)
			return *(*it);
	}
	throw NotFound<Course*, string>(acronym);
}

University& getUniversity(EnrollmentSystem &s)
{
	if (s.universitiesVector.size() == 0)
		throw NotFound<University*, EnrollmentSystem>(s);

	int answer = -1;

	while (answer <= 0 || answer > s.universitiesVector.size()) {
		system("CLS");
		for (size_t i = 0; i < s.universitiesVector.size(); i++) //SHOW AS MENU
		{
			cout << (i + 1) << ". ";
			cout << s.universitiesVector[i]->getName() << endl;
		}
		cout << endl;
		answer = enterInput<int>(); //READ SELECTION
	}

	answer--;

	return *(s.universitiesVector[answer]);
}

College& getCollege(EnrollmentSystem &s)
{
	University* university = &getUniversity(s);

	int answer_2 = -1;

	if (university->getColleges().size() == 0)
		throw NotFound<College*, University*>(university);

	while (answer_2 <= 0 || answer_2 > university->getColleges().size()) {
		system("CLS");
		for (size_t i = 0; i < university->getColleges().size(); i++) //SHOW AS MENU
		{
			cout << (i + 1) << ". ";
			cout << university->getColleges()[i]->getName() << endl;
		}
		cout << endl;
		answer_2 = enterInput<int>(); //READ SELECTION
	}

	answer_2--;

	return *(university->getColleges()[answer_2]);
}

Course& getCourse(EnrollmentSystem &s)
{
	College* college = &getCollege(s);

	int answer_3 = -1;

	if (college->getCourses().size() == 0)
		throw NotFound<Course*, College*>(college);

	while (answer_3 <= 0 || answer_3 > college->getCourses().size()) {
		system("CLS");
		for (size_t i = 0; i < college->getCourses().size(); i++) //SHOW AS MENU
		{
			cout << (i + 1) << ". ";
			cout << college->getCourses()[i]->getName() << endl;
		}
		cout << endl;
		answer_3 = enterInput<int>(); //READ SELECTION
	}

	answer_3--;

	return *(college->getCourses()[answer_3]);
}

CourseUnit& getCourseUnitUser(EnrollmentSystem &s)
{
	Course* course = &getCourse(s);

	int answer_4 = -1;

	if (course->getCourseUnits().size() == 0)
		throw NotFound<CourseUnit*, Course*>(course);

	while (answer_4 <= 0 || answer_4 > course->getCourseUnits().size()) {
		system("CLS");
		for (size_t i = 0; i < course->getCourseUnits().size(); i++) //SHOW AS MENU
		{
			cout << (i + 1) << ". ";
			cout << course->getCourseUnits()[i]->getName() << endl;
		}
		cout << endl;
		answer_4 = enterInput<int>(); //READ SELECTION
	}

	answer_4--;

	return *(course->getCourseUnits()[answer_4]);
}

Student& EnrollmentSystem::getStudent(unsigned long long int &ID)
{
	vector<University*>::iterator unIt;
	for (unIt = universitiesVector.begin();
		unIt != universitiesVector.end();
		unIt++
		)
	{
		vector<College*>::iterator colIt;
		for (colIt = (*unIt)->getColleges().begin();
			colIt != (*unIt)->getColleges().end();
			colIt++
			)
		{
			vector<Course*>::iterator courseIt;
			for (courseIt = (*colIt)->getCourses().begin();
				courseIt != (*colIt)->getCourses().end();
				courseIt++
				)
			{
				vector<Student*>::iterator sIt; 
				for (sIt = (*courseIt)->getStudents().begin();
					sIt != (*courseIt)->getStudents().end();
					sIt++
					)
				{
					if ((*sIt)->getID() == ID)
						return *(*sIt);

				}
			}
		}
	}
	throw NotFound<Student*, unsigned long long int>(ID);
}

Tutor& EnrollmentSystem::getProfessor(unsigned long long int &ID) {
	
	vector<University*>::iterator unIt;
	for (unIt = universitiesVector.begin();
		unIt != universitiesVector.end();
		unIt++
		)
	{
		vector<College*>::iterator colIt;
		for (colIt = (*unIt)->getColleges().begin();
			colIt != (*unIt)->getColleges().end();
			colIt++
			)
		{
			vector<Course*>::iterator courseIt;
			for (courseIt = (*colIt)->getCourses().begin();
				courseIt != (*colIt)->getCourses().end();
				courseIt++
				)
			{
				vector<Tutor*>::iterator sIt;
				for (sIt = (*courseIt)->getProfessors().begin();
					sIt != (*courseIt)->getProfessors().end();
					sIt++
					)
				{
					if ((*sIt)->getID() == ID)
						return *(*sIt);

				}
			}
		}
	}
	throw NotFound<Tutor*, unsigned long long int>(ID);
}

void EnrollmentSystem::removeUniversity(University& u)
{
	vector<University*>::iterator it;
	it = find(universitiesVector.begin(), universitiesVector.end(), &u);
	if (it != universitiesVector.end()) {
		universitiesVector.erase(it);
		return;
	}
	else
		throw NotFound<University*, string>(u.getName());

}

bool addStudentHandler(EnrollmentSystem& s)
{
	Date dateOfBirth;
	Course* course;
	string studentName, status;

	try
	{
		studentName = enterString("\nAdd Student\n\n", "Enter the name of the student [CTRL+Z to cancel] : ");
		vector<string> supportedStatus = {
			"Estudante Regular",
			"Trabalhador Estudante",
			"Dirigente Associativo",
			"Praticante de Desporto de Alto Rendimento",
			"Pai e Mãe Estudante",
			"Necessidades Educativas Especiais",
			"Militar",
			"Bombeiro",
			"Praticante de Confissões Religiosas",
			"Estudante-atleta da U.Porto",
		};
		while (true) {
			system("cls");
			cout << "\nAdd Student\n\n" << "\nSelect a status [CTRL+Z to cancel] \n\n";
			for (unsigned int i = 0; i < supportedStatus.size(); i++) {
				cout << i + 1 << ". " << supportedStatus[i] << endl;
			}
			cout << endl;
			unsigned int option = enterInput<unsigned int>();
			if (option >= 1 && option <= supportedStatus.size()) {
				status = supportedStatus[option - 1];
				break;
			}
		}

		while (true)
		{
			dateOfBirth = Date(enterString("\nAdd Student\n\n", "Enter the date of birth (DD-MM-YYYY) [CTRL+Z to cancel] : "));
			if (dateOfBirth.getValid())
				break;
			cout << "\nInvalid Date!\n";
			system("PAUSE");
		}
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		system("pause");
		return false;
	}
	
	try {
		course = &getCourse(s); //GET THE COURSE FROM THE USER
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		return false;
	}
	catch (NotFound<University*, EnrollmentSystem> &nfu)
	{
		cout << "There are no universities in the system\n";
		return false;
	}
	catch (NotFound<College*, University*> &nfc)
	{
		cout << "There are no colleges in: " << nfc.getMember()->getName() << endl;
		return false;
	}
	catch (NotFound<Course*, College*> &nfco)
	{
		cout << "There are no courses in: " << nfco.getMember()->getName() << endl;
		return false;
	}
		
	new Student(studentName, dateOfBirth, *course, status);

	return true;
}

bool removeStudentHandler(EnrollmentSystem& s)
{
	Student* student;
	unsigned long long int ID;

	try
	{
		ID = enterInput<unsigned long long int>("\nRemove Student\n\n", "Enter the ID of the student [CTRL+Z to cancel] : ");
		student = &(s.getStudent(ID));
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		return false;
	}
	catch (NotFound<Student*, unsigned long long int> &nfs)
	{
		cout << "Student " << nfs.getMember() << " not found!\n";
		return false;
	}

	student->getCourse().removeStudent(*student);
	
	return true;
}

bool removeUniversityHandler(EnrollmentSystem& s) {
	University* uni;
	string name;

	try
	{
		cout << "\nRemove University\n\n";
		uni = &getUniversity(s);
		s.removeUniversity(*uni);
	}
	catch (EndOfFile &eof)
	{
		cout << "\nRemove canceled!\n";
		return false;
	}
	catch (NotFound<University*, string> &nfu)
	{
		cout << "University " << nfu.getMember() << " not found!\n";
		return false;
	}

	cout << "University Erased";

	return true;
}

bool enrollmentHandler(EnrollmentSystem& s)
{
	Student* student;
	unsigned long long int ID;

	try
	{
		ID = enterInput<unsigned long long int>("\nEnrollment System\n\n", "Enter the ID of the student [CTRL+Z to cancel] : ");
		student = &(s.getStudent(ID));
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		return false;
	}
	catch (NotFound<Student*, unsigned long long int> &nfs)
	{
		cout << "Student " << nfs.getMember() << " not found!\n";
		system("PAUSE");
		return false;
	}
	
		vector<CourseUnit*> courseUnitsToShow = student->getCourse().getCourseUnitsNotCompleted(*student, student->getYear());
	
		unsigned int answer = 0;
		try 
		{
			while (answer != (courseUnitsToShow.size() + 1) && courseUnitsToShow.size() != 0) //EXIT
			{
				system("CLS");
				size_t i;
				for (i = 0; i < courseUnitsToShow.size(); i++) //SHOW AS MENU
				{
					cout << (i + 1) << ". ";
					courseUnitsToShow[i]->show();
				}
				cout << endl << endl << (i+1) << ". Exit\n\n";
				answer = enterInput<unsigned int>(); //READ SELECTION
				if (answer >= 1 && answer <= courseUnitsToShow.size()) 
				{
					if (student->getCredits() + courseUnitsToShow[answer - 1]->getCredits() <= s.getMaxCredits())
					{
						student->enrollCourseUnit(s.getCourseUnit(
							(courseUnitsToShow[answer - 1])->getAcronym(),
							student->getCourse()));

						student->setCredits(student->getCredits() + (*courseUnitsToShow[answer - 1]).getCredits());
						courseUnitsToShow = student->getCourse().getCourseUnitsNotCompleted(*student, student->getYear()); //REFRESH MENU
					}
					else cout << "Student cannot enroll this course unit. Maximum credits have been exceeded";
				}
			}
		}
		catch (EndOfFile &eof)
		{
			cout << "Enrollment Canceled!\n";
			return false;
		}
	
	return courseUnitsToShow.size() == 0;
}

bool studentFinishedCourseUnitHandler(EnrollmentSystem& s) 
{
	Student* student;
	unsigned long long int ID;
	Course* course;
	unsigned short int grade;

	try
	{
		ID = enterInput<unsigned long long int>("\nFinish Course Unit\n\n", "Enter the ID of the student [CTRL+Z to cancel] : ");
		student = &(s.getStudent(ID));
		course = &(student->getCourse());
	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		system("pause");
		return false;
	}
	catch (NotFound<Student*, unsigned long long int> &nfs)
	{
		cout << "Student " << nfs.getMember() << " not found!\n";
		system("pause");
		return false;
	}
	
	while (true) {
		vector<CourseUnit*> courseUnitsToShow;
		unsigned int answer;

		try {

		unsigned int i;

		courseUnitsToShow = student->getCourseUnitsAttending();

		system("cls");
		if (courseUnitsToShow.size() == 0) {
			cout << "\nThis student is not taking any classes\n";
			system("pause");
			return false;
		}

		for (i = 0; i < courseUnitsToShow.size(); i++) {
			cout << (i + 1) << ". ";
			courseUnitsToShow[i]->show();
		}
		cout << endl << endl << (i + 1) << ". Exit\n\n";
		answer = enterInput<unsigned int>(); //READ SELECTION
		answer--;

		if (answer == courseUnitsToShow.size())
			return true;
				
		grade = enterInput<unsigned short int>("\nFinish Course Unit\n\n", "Enter the grade of the student to this course unit [CTRL+Z to cancel] : ");
		

		if (!student->completedClass(*courseUnitsToShow[answer], grade)) {
			cout << "\nThe Student wasn't taking this course unit or the grade is invalid!\n." << endl;
			system("pause");
		}
		else {
			cout << "\nThe student has been graded!\n";
			system("pause");
		}

		}
		catch (EndOfFile &eof)
		{
			cout << "\nAddition canceled!\n";
			system("pause");
			return false;
		}
		

		//CHECK IF STUDENT HAS COMPLETED ALL THE COURSE UNITS OF THE CURRENT YEAR
		if (student->completedAllCourseUnits(student->getYear()))
		{
			//GET READY FOR NEXT YEAR
			student->setCredits(double(0));
			student->setYear(student->getYear() + 1);
			cout << "Student finished this Course Year. Now he/she is currently in year " << student->getYear() << "." << endl;
			system("pause");
			break;
		}
		else {
			cout << "\nStudent still has course units to complete in order to enroll the next year\n";
			system("pause");
		}
	}
	return true;
}

bool EnrollmentSystem::changeCourseUnitSortOption(unsigned int &option)
{
	vector<bool(*)(CourseUnit*, CourseUnit*)> options = {
		compareCourseUnitByName,
		compareCourseUnitByNumberStudents,
		compareCourseUnitByTime
	};

	size_t minimum = 1, maximum = options.size() + 1;

	if (option >= minimum && option <= (maximum - 1)) {
		courseUnitSortOption = options[option - 1]; //CALL THE CORRESPONDENT FUNCTION
		return true;
	}
	else if (option == maximum) //EXIT
		return true;
	else return false; //CALL THE FUNCTION AGAIN
}

bool EnrollmentSystem::changeCourseUnitClassSortOption(unsigned int &option)
{
	vector<bool(*)(CourseUnitClass*, CourseUnitClass*)> options = {
		compareCourseUnitClassByNumber,
		compareCourseUnitClassByNumberStudents
	};

	size_t minimum = 1, maximum = options.size() + 1;

	if (option >= minimum && option <= (maximum - 1)) {
		courseUnitClassSortOption = options[option - 1]; //CALL THE CORRESPONDENT FUNCTION
		return true;
	}
	else if (option == maximum) //EXIT
		return true;
	else return false; //CALL THE FUNCTION AGAIN
}

bool EnrollmentSystem::changeStudentsSortOption(unsigned int &option)
{
	vector<bool(*)(Student*, Student*)> options = {
		compareStudentByID,
		compareStudentByName,
		compareStudentByBirth,
		compareStudentByCouseYear,
		compareStudentByRegistration
	};

	size_t minimum = 1, maximum = options.size() + 1;

	if (option >= minimum && option <= (maximum - 1)) {
		studentsSortOption = options[option - 1]; //CALL THE CORRESPONDENT FUNCTION
		return true;
	}
	else if (option == maximum) //EXIT
		return true;
	else return false; //CALL THE FUNCTION AGAIN
}

bool EnrollmentSystem::changeProfessorsSortOption(unsigned int &option)
{
	vector<bool(*)(Tutor*, Tutor*)> options = {
		compareProfessorByID,
		compareProfessorByName,
		compareProfessorByBirth,
		compareProfessorByRegistration
	};

	size_t minimum = 1, maximum = options.size() + 1;

	if (option >= minimum && option <= (maximum - 1)) {
		professorsSortOption = options[option - 1]; //CALL THE CORRESPONDENT FUNCTION
		return true;
	}
	else if (option == maximum) //EXIT
		return true;
	else return false; //CALL THE FUNCTION AGAIN
}

void EnrollmentSystem::saveHandler() {
	saveToFiles(getAllStudents(), studentsFile);
	saveToFiles(getAllCourseUnitClasses(), courseUnitClassesFile);
	saveToFiles(getAllProfessors(), professorsFile);
	saveToFiles(getAllCourseUnits(), courseUnitsFile);
	saveToFiles(getAllCourses(), coursesFile);
	saveToFiles(getAllColleges(), collegesFile);
	saveToFiles(universitiesVector, universityFile);
}

Tutor& EnrollmentSystem::getProfessor(unsigned long long int &ID, Course& course)
{
	vector<Tutor*>::iterator it;
	for (it = course.getProfessors().begin();
		it != course.getProfessors().end();
		it++)
	{
		if ((*it)->getID() == ID)
			return *(*it);
	}
	throw NotFound<Tutor*, Course*>(&course);
}

CourseUnit& EnrollmentSystem::getCourseUnit(string &acronym, Course& course)
{
	vector<CourseUnit*>::iterator it;
	for (it = course.getCourseUnits().begin();
		it != course.getCourseUnits().end();
		it++)
	{
		if ((*it)->getAcronym() == acronym)
			return *(*it);
	}
	throw NotFound<CourseUnit*, Course*>(&course);
}

CourseUnitClass& EnrollmentSystem::getCourseUnitClass(unsigned int &classNumber, CourseUnit& courseUnit)
{
	vector<CourseUnitClass*>::iterator it;
	for (it = courseUnit.getClasses().begin();
		it != courseUnit.getClasses().end();
		it++)
	{
		if ((*it)->getClassNumber() == classNumber)
			return *(*it);
	}
	throw NotFound<CourseUnitClass*, CourseUnit*>(&courseUnit);
}

vector<College*> EnrollmentSystem::getAllColleges()
{
	vector<College*> colleges;
	for (unsigned int i = 0; i < universitiesVector.size(); i++){
		colleges.insert(colleges.begin(), universitiesVector[i]->getColleges().begin(), universitiesVector[i]->getColleges().end());
	}
	return colleges;
}

vector<Course*> EnrollmentSystem::getAllCourses()
{
	vector<College*> colleges = getAllColleges();
	vector<Course*> courses;
	for (unsigned int i = 0; i < colleges.size(); i++) {
		courses.insert(courses.begin(), colleges[i]->getCourses().begin(), colleges[i]->getCourses().end());
	}
	return courses;
}

vector<CourseUnit*> EnrollmentSystem::getAllCourseUnits()
{
	vector<Course*> courses = getAllCourses();
	vector<CourseUnit*> courseUnits;
	for (unsigned int i = 0; i < courses.size(); i++) {
		courseUnits.insert(courseUnits.begin(), courses[i]->getCourseUnits().begin(), courses[i]->getCourseUnits().end());
	}
	return courseUnits;
}

vector<CourseUnitClass*> EnrollmentSystem::getAllCourseUnitClasses()
{
	vector<CourseUnit*> courseUnits = getAllCourseUnits();
	vector<CourseUnitClass*> courseUnitClasses;
	for (unsigned int i = 0; i < courseUnits.size(); i++) {
		courseUnitClasses.insert(courseUnitClasses.begin(), courseUnits[i]->getClasses().begin(), courseUnits[i]->getClasses().end());
	}
	return courseUnitClasses;
}

vector<Student*> EnrollmentSystem::getAllStudents()
{
	vector<Student*> students;
	vector<Course*> courses = getAllCourses();
	for (unsigned int i = 0; i < courses.size(); i++) {
		students.insert(students.begin(), courses[i]->getStudents().begin(), courses[i]->getStudents().end());
	}
	return students;
}

vector<Tutor*> EnrollmentSystem::getAllProfessors()
{
	vector<Tutor*> professors;
	vector<Course*> courses = getAllCourses();
	for (unsigned int i = 0; i < courses.size(); i++) {
		professors.insert(professors.begin(), courses[i]->getProfessors().begin(), courses[i]->getProfessors().end());
	}
	return professors;
}

void EnrollmentSystem::showUniversities()
{
	system("cls");
	cout << "\nUniversities\n\n";
	sort(universitiesVector.begin(), universitiesVector.end(), universitySortOption);
	if (universitiesVector.size() != 0)
	{
		vector<University*>::iterator it;
		for (it = universitiesVector.begin();
			it != universitiesVector.end();
			it++
			) {
			(*it)->show();
		}
	}
	else cout << "There are no universities";
}

void EnrollmentSystem::showColleges()
{
	system("cls");
	cout << "\nColleges\n\n";
	vector<College*> colleges = getAllColleges();
	sort(colleges.begin(), colleges.end(), collegeSortOption);
	if (colleges.size() != 0) {
		vector<College*>::iterator it;
		for (it = colleges.begin();
			it != colleges.end();
			it++
			)
		{
			(*it)->show();
		}
	}
	else cout << "There are no colleges\n";
}

void EnrollmentSystem::showCourses()
{
	system("cls");
	cout << "\nCourses\n\n";
	vector<Course*> courses = getAllCourses();
	sort(courses.begin(), courses.end(), courseSortOption);
	if (courses.size() != 0) {
		vector<Course*>::iterator it;
		for (it = courses.begin();
			it != courses.end();
			it++
			)
		{
			(*it)->show();
		}
	}
	else cout << "There are no courses\n";
}

void EnrollmentSystem::showCourseUnits()
{
	system("cls");
	cout << "\nCourseUnit\n\n";
	vector<CourseUnit*> courseUnits = getAllCourseUnits();
	sort(courseUnits.begin(), courseUnits.end(), courseUnitSortOption);
	if (courseUnits.size() != 0) {
		vector<CourseUnit*>::iterator it;
		for (it = courseUnits.begin();
			it != courseUnits.end();
			it++
			)
		{
			(*it)->show();
		}
	}
	else cout << "There are no course units\n";
}

void EnrollmentSystem::showProfessors()
{
	system("cls");
	cout << "\nProfessors\n\n";
	vector<Tutor*> professors = getAllProfessors();
	sort(professors.begin(), professors.end(), professorsSortOption);
	if (professors.size() != 0) {
		vector<Tutor*>::iterator it;
		for (it = professors.begin();
			it != professors.end();
			it++
			)
		{
			(*it)->show();
		}
	}
	else cout << "There are no professors\n";
}

void EnrollmentSystem::showStudents()
{
	system("cls");
	cout << "\nStudents\n\n";
	vector<Student*> students = getAllStudents();
	sort(students.begin(), students.end(), studentsSortOption);
	if (students.size() != 0) {
		vector<Student*>::iterator it;
		for (it = students.begin();
			it != students.end();
			it++
			)
		{
			(*it)->show();
		}
	}
	else cout << "There are no students\n";
}

void EnrollmentSystem::showCourseUnitClasses()
{
	system("cls");
	cout << "\nClasses\n\n";
	vector<CourseUnitClass*> courseUnitClasses = getAllCourseUnitClasses();
	sort(courseUnitClasses.begin(), courseUnitClasses.end(), courseUnitClassSortOption);
	if (courseUnitClasses.size() != 0) {
		vector<CourseUnitClass*>::iterator it;
		for (it = courseUnitClasses.begin();
			it != courseUnitClasses.end();
			it++
			)
		{
			(*it)->show();
		}
	}
	else cout << "There are no classes";
}

void EnrollmentSystem::showStudentInDetail()
{
	try {
		system("cls");
		cout << "\nEnter the ID of the student\n\n";
		unsigned long long int id = enterInput<unsigned long long int>();
		Student s = getStudent(id);
		system("cls");
		cout << "\nStudent Details\n\n\n";
		s.showInDetail();
	}
	catch (...) {

	}
}

void EnrollmentSystem::showCourseUnitInDetail()
{
	try {
		system("cls");
		CourseUnit* cuPtr = &getCourseUnitUser(*this);
		cout << "\nCourse Unit Details\n\n\n";
		cuPtr->showInDetail();
	}
	catch (...) {

	}
}

void EnrollmentSystem::addMeetingHandler() {
	
	Tutor* tutor;
	Student* student;
	vector<string> topics;
	Date date;
	unsigned int hour, minute;
	unsigned long long int tutorID;

	try
	{
		tutorID = enterInput<unsigned long long int>("\nAdd Meeting\n\n", "Enter the ID of the tutor [CTRL+Z to cancel] : ");
		tutor = &(getProfessor(tutorID));
		/*
		studentID = enterInput<unsigned long long int>("\nAdd Meeting\n\n", "Enter the ID of the student [CTRL+Z to cancel] : ");
		student = &(getStudent(studentID));

		if (!(tutor->isTutorOf(*student))) {
			system("CLS");
			cout << "\nAdd Meeting\n\n" << "The student's tutor is not the professor you've introduced\n\n";
			system("PAUSE");
			return;
		}*/

		while (true) {
			system("cls");
			cout << "\nAdd Meeting\n\n";
			if (tutor->getStudents().size()) {
				for (size_t i = 0; i < tutor->getStudents().size(); i++) {
					cout << i + 1 << ". ";
					tutor->getStudents()[i]->show();
				}
				cout << tutor->getStudents().size() + 1 << ". Exit\n";
				cout << "\nWhat student do you want to meet with?\n";
				size_t option = enterInput<size_t>();
				option--;
				if (option == tutor->getStudents().size()) { //EXIT
					cout << "\nAction Cancelled\n\n";
					system("Pause");
					return;
				}
				else if (option >= 0 && option <= (tutor->getStudents().size() - 1)) { //WITHIN RANGE
					student = tutor->getStudents()[option];
					break;
				}
				else {
					cout << "\nInvalid Option\n\n";
					system("Pause");
					continue;
				}
			}
			else {
				cout << "The tutor is not tutoring any student\n\n";
				system("Pause");
				return;
			}

		}


		while (true)
		{
			date = Date(enterString("\nAdd Meeting\n\n", "Enter the date for the meeting (DD-MM-YYYY) [CTRL+Z to cancel] : "));
			if (date.getValid())
				break;
			cout << "\nInvalid Date!\n";
			system("PAUSE");
		}

		while (true) {
			string time = enterString("\nAdd Meeting\n\n", "Enter the time for the meeting (HH:MM) [CTRL+Z to cancel] : ");
			istringstream iss(time);
			char tempChar;
			iss >> hour >> tempChar >> minute;
			if (!iss.fail())
				break;
		}

	}
	catch (EndOfFile &eof)
	{
		cout << "\nAddition canceled!\n";
		return;
	}
	catch (NotFound<Student*, unsigned long long int> &nfs)
	{
		cout << "Student " << nfs.getMember() << " not found!\n";
		return;
	}
	catch (NotFound<Tutor*, unsigned long long int> &nfs)
	{
		cout << "Tutor " << nfs.getMember() << " not found!\n";
		return;
	}

	//ENTER THE TOPICS
	while (true) {
		system("cls");
		cout << "\nAdd Meeting\n\n";
		if (topics.size()) {
			cout << "\nTopics:\n";
			for (size_t i = 0; i < topics.size(); i++)
				cout << '\t' << topics[i] << '\n';
		}
		cout << "Enter a topic [CTRL+Z to end] : \n";
		string temp;
		if (getline(cin, temp)) {
			topics.push_back(temp);
		}
		else {
			cin.clear();
			break;
		}
	}	

	tutor->addMeeting(Meeting(date, student,topics, hour, minute));

}

void EnrollmentSystem::removeMeetingHandler() {
	Tutor* tutor; 
	unsigned long long int tutorID;

	try	{
		tutorID = enterInput<unsigned long long int>("\nCancel Meeting\n\n", "Enter the ID of the tutor [CTRL+Z to cancel] : ");
		tutor = &(getProfessor(tutorID));
	}
	catch (EndOfFile &eof){
		cout << "\nAction canceled!\n";
		return;
	}
	catch (NotFound<Tutor*, unsigned long long int> &nfs){
		cout << "Tutor " << nfs.getMember() << " not found!\n";
		return;
	}

	while (true) {
		system("cls");
		cout << "\nCancel Meeting\n\n";
		set<Meeting> meetings = tutor->getMeetings();
		if (meetings.size()) {
			set<Meeting>::iterator it;
			size_t i = 1;
			for (it = meetings.begin();
				it != meetings.end();
				it++, i++) {
				cout << i << ". " << endl;
				it->show();
			}
			cout << i << ". " << "Exit" << endl;
			cout << "\nSelect the meeting you wish to cancel:\n";
			size_t option = enterInput<size_t>();
			option--;
			if (option == meetings.size()) { //EXIT OPTION
				cout << "Action cancelled\n\n";
				system("Pause");
				return;
			}
			else if (option >= 0 && option <= (meetings.size() - 1)) { //WITHIN RANGE
				it = tutor->getMeetings().begin();
				for (; option > 0; option--) {
					it++;
				}
				tutor->getMeetings().erase(it);

				return;
			}
			else { //OUTSIDE RANGE
				cout << "Invalid option\n\n";
				system("Pause");
			}
		}
		else {
			cout << "There are no meetings to cancel\n\n";
			system("Pause");
			return;
		}
	}
}

void EnrollmentSystem::changeMeetingDescriptionHandler() {
	Tutor* tutor;
	unsigned long long int tutorID;

	try {
		tutorID = enterInput<unsigned long long int>("\nModify Meeting\n\n", "Enter the ID of the tutor [CTRL+Z to cancel] : ");
		tutor = &(getProfessor(tutorID));
	}
	catch (EndOfFile &eof) {
		cout << "\nAction canceled!\n";
		return;
	}
	catch (NotFound<Tutor*, unsigned long long int> &nfs) {
		cout << "Tutor " << nfs.getMember() << " not found!\n";
		return;
	}

	while (true) {
		system("cls");
		cout << "\nModify Meeting\n\n";
		set<Meeting> meetings = tutor->getMeetings();
		if (meetings.size()) {
			set<Meeting>::iterator it;
			size_t i = 1;
			for (it = meetings.begin();
				it != meetings.end();
				it++, i++) {
				cout << i << ". " << endl;
				it->show();
			}
			cout << i << ". " << "Exit" << endl;
			cout << "\nSelect the meeting you wish to modify:\n";
			size_t option = enterInput<size_t>();
			option--;
			if (option == meetings.size()) { //EXIT OPTION
				cout << "Action cancelled\n\n";
				system("Pause");
				return;
			}
			else if (option >= 0 && option <= (meetings.size() - 1)) { //WITHIN RANGE
				it = tutor->getMeetings().begin();
				for (; option > 0; option--) {
					it++;
				}

				string newDescription = enterString("\nModify Meeting\n\n", "Enter the new description for this meeting: ");

				//CANNOT MODIFY DIRECTLY IN SET
				//SOLUTION: SAVE IT TO A TEMP VARIABLE, REMOVE FROM SET, MODIFY IT AND STORE IT AGAIN IN SET
				Meeting tempMeeting = *it;
				tutor->getMeetings().erase(it);
				tempMeeting.setDescription(newDescription);
				tutor->addMeeting(tempMeeting);
				return;
			}
			else { //OUTSIDE RANGE
				cout << "Invalid option\n\n";
				system("Pause");
			}
		}
		else {
			cout << "There are no meetings to modify\n\n";
			system("Pause");
			return;
		}
	}
}
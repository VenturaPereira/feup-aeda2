#pragma once

#include "University.h"
#include "College.h"
#include "Course.h"
#include "CourseUnit.h"
#include "Utilities.h"


void University::incrementLastStudentID()
{
	lastStudentID++;
}

void University::incrementLastProfessorID()
{
	lastProfessorID++;
}

void University::addCollege(College& c)
{
	collegesVector.push_back(&c);
}

bool University::removeCollege(College& c)
{
	for (vector<College *> ::iterator it = collegesVector.begin();
		it != collegesVector.end();
		it++)
	{
		if ((*it) == &c)
		{
			collegesVector.erase(it);
			return true;
		}
	}
	return false;
}

void University::showAllOptional(string scientificArea, OptionalCourseUnit& arg) const
{
	vector<College*>::const_iterator colIt;
	vector<Course*>::const_iterator courseIt;
	vector<CourseUnit*>::const_iterator cuIt;
	for (colIt = collegesVector.begin();
		colIt != collegesVector.end();
		colIt++)
	{
		for (courseIt = (*colIt)->getCourses().begin();
			courseIt != (*colIt)->getCourses().end();
			courseIt++)
		{
			for (cuIt = (*courseIt)->getCourseUnits().begin();
				cuIt != (*courseIt)->getCourseUnits().end();
				cuIt++)
			{
				OptionalCourseUnit* ocu = dynamic_cast<OptionalCourseUnit*>((*cuIt));
				if (ocu != NULL)
					if(ocu->getScientificArea() == scientificArea && &arg != ocu) //SAME SCIENTIFIC AREA, BUT NOT THE SAME COURSE UNIT AS THE ARGUMENT
						ocu->show();
			}
		}
	}
}

bool compareUniversityByName(University* u1, University* u2)
{
	return u1->name < u2->name;
}

ofstream& University::operator<<(ofstream &file)
{
	file << this->name
		<< ";" 
		<< this->acronym
		<<";"
		<< this->countryAcronym
		<< ";"
		<< this->lastStudentID
		<< ";"
		<< this->lastProfessorID
		<< endl;
	return file;
}

void University::show() const
{
	cout << name
		<< setw(CONSOLE_WIDTH * 1.5 - name.size())
		<< acronym
		<< endl;
}

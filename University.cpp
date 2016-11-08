#pragma once

#include "University.h"
#include "College.h"
#include "Course.h"
#include "CourseUnit.h"


void University::incrementLastStudentID()
{
	lastStudentID++;
}

void University::incrementLastProfessorID()
{
	lastProfessorID++;
}

void University::addCollege(College* c)
{
	collegesVector.push_back(c);
}

bool University::removeCollege(College *c)
{
	for (vector<College *> ::iterator it = collegesVector.begin();
		it != collegesVector.end();
		it++)
	{
		if ((*it) == c)
		{
			collegesVector.erase(it);
			return true;
		}
	}
	return false;
}

void University::showAllOptional(string scientificArea, OptionalCourseUnit* arg) const
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
					if(ocu->getScientificArea() == scientificArea && arg != ocu) //SAME SCIENTIFIC AREA, BUT NOT THE SAME COURSE UNIT AS THE ARGUMENT
						ocu->show();
			}
		}
	}
}


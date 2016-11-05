#pragma once

#include "University.h"


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

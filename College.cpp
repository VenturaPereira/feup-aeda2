#pragma once

#include "College.h"

void College::addCourse(Course* c)
{
	courses.push_back(c);
}

bool College::removeCourse(Course* c)
{
	for (vector<Course *> ::const_iterator it = courses.begin();
		it != courses.end();
		it++)
	{
		if ((*it) == c) 
		{
			courses.erase(it);
			return true;
		}
	}
	return false;
}
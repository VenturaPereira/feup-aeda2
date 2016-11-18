#pragma once

#include "CollegeUser.h" 
#include "Course.h"

CollegeUser::CollegeUser(string n, Date dob, Course* c)
{
	name = n;
	dateOfRegistration;
	dateOfBirth = dob;
	college = c->getCollege();
}
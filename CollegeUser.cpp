#pragma once

#include "CollegeUser.h" 
#include "Course.h"

CollegeUser::CollegeUser(string n, Date dob, Course& c, string ad, unsigned long long int pn)
{
	phoneNumber = pn;
	address = ad;
	name = n;
	dateOfRegistration;
	dateOfBirth = dob;
	college = &(c.getCollege());
}
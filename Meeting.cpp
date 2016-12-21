#include "Meeting.h"
#include <ctime>
#include <iostream>
#include "Student.h"

Meeting::Meeting(Date d, Student* st, string des, unsigned int h, unsigned int m) :
	student(st), description(des), date(d), minute(m), hour(h) {
}

bool Meeting::hasOccured() const {
	//Get current time
	time_t t = time(NULL);
	tm now;
	localtime_s(&now, &t);

	//Return if this->date is less than the current date (includes hour:minute)
	return (this->date < Date()) ||
		(this->date == Date() &&
		(hour < now.tm_hour ||
			(hour == now.tm_hour && minute < now.tm_min)));
}

bool operator<(const Meeting &m1, const Meeting &m2) {
	return (m1.date < m2.date ||
		(m1.date == m2.date &&
		(m1.hour < m2.hour ||
			(m1.hour == m2.hour && m1.minute < m2.minute))));
}

bool operator==(const Meeting &m1, const Meeting &m2) {
	return 
		(m1.date == m2.date &&
			m1.hour == m2.hour && 
				m1.minute == m2.minute &&
					m1.student == m2.student);
}

void Meeting::show() const {
	cout << "Date: " << date.getDateString() << " - " << hour << ':' << minute << endl;
	cout << "Student: " << student->getID() << endl;
	cout << "Description: " << description << endl;
}
#include "Student.h"
#include "Meeting.h"
#include <ctime>
#include <iostream>


Meeting::Meeting(Date d, Student* st, vector<string> &top, unsigned int h, unsigned int m) :
	student(st), topics(top), date(d), minute(m), hour(h) {
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
	if (m1.date < m2.date)
		return true;
	else if (m1.date == m2.date) {
		if (m1.hour < m2.hour)
			return true;
		else if (m1.hour == m2.hour) {
			if (m1.minute < m2.minute)
				return true;
			else return false;
		}
		else return false;
	}
	else return false;
}

bool operator==(const Meeting &m1, const Meeting &m2) {
	return 
		(m1.date == m2.date &&
			m1.hour == m2.hour && 
				m1.minute == m2.minute);
}

void Meeting::show() const {
	cout << "Date: " << date.getDateString() << " - " << hour << ':' << minute << endl;
	cout << "Student: " << student->getID() << endl;
	cout << "Topics:\n";
	if (topics.size()) {
		for (size_t i = 0; i < topics.size(); i++)
			cout << "\t" << topics[i] << endl;
	}
	else cout << "\tThere are no topics for this meeting!\n";
	cout << "Description: " << description << endl;
}
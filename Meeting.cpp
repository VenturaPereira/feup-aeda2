#include "Student.h"
#include "Meeting.h"
#include "Tutor.h"
#include <ctime>
#include <iostream>
#include <fstream>


Meeting::Meeting(Date d, Student* st, Tutor* t, vector<string> &top, unsigned int h, unsigned int m) :
	student(st), professor(t), topics(top), date(d), minute(m), hour(h) {
}

bool Meeting::hasOccured() const {
	//Return if this->date is less than the current date (includes hour:minute)
	Date currentDate;
	if (this->date < currentDate) {
		return true;
	}
	else {
		if (this->date == currentDate) {
			//Get current time
			time_t t = time(NULL);
			tm now;
			localtime_s(&now, &t);
			if (hour < now.tm_hour)
				return true;
			else if (hour == now.tm_hour) {
				return minute < now.tm_min;
			}
			else return false;

		}
		else return false;
	}
}

bool operator<(const Meeting &m1, const Meeting &m2) {
	if (m1.date < m2.date)
		return true;
	else if (m1.date == m2.date) {
		if (m1.hour < m2.hour)
			return true;
		else if (m1.hour == m2.hour) {
			return m1.minute < m2.minute;
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

ofstream& Meeting::operator<<(ofstream& file) {
	file << professor->getID()
		<< ';'
		<< student->getID()
		<< ';'
		<< date.getDateString()
		<< ';'
		<< hour
		<< ':'
		<< minute
		<< ';'
		<< description
		<< ';'
		<< '{';

	for (size_t i = 0; i < topics.size(); i++) {
		file << topics[i];
		if (i != topics.size() - 1)
			file << ',';
	}

	file << '}'
		<< endl;

	return file;
}
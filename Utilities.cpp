#pragma once

#include "Utilities.h"

unsigned int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	unsigned int CONSOLE_WIDTH = (csbi.srWindow.Right - csbi.srWindow.Left) / 2;

	return CONSOLE_WIDTH;

}

const unsigned int CONSOLE_WIDTH = getConsoleWidth();

void center(const string s) {
	cout << setw(CONSOLE_WIDTH + s.length() / 2) << s << endl;
}

string enterString(string title, string requestMsg)
{
	string line;
	while (true)
	{
		system("CLS");
		cin.clear();
		cout << title << requestMsg;
		getline(cin, line);
		if (cin.eof())
			throw EndOfFile();
		else if (line.length() > 0)
			return line;
	}
}

bool yesNoAnswer() {
	string answer;
	while (true)
	{
		cout << "\nAnswer: ";
		getline(cin, answer);
		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
		if (answer == "y" || answer == "yes")
			return true;
		else if (answer == "n" || answer == "no")
			return false;
		else cerr << "Invalid Answer!\n";
		cin.clear();
	}
}

bool leapYear(const unsigned short int &year)
{
	if ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0))
		return true;
	else return false;
}

unsigned short int numberDays(const unsigned short int &year, const unsigned short int &month)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return (unsigned short int)31;
	case 4:
	case 6:
	case 9:
	case 11:
		return (unsigned short int)30;
	case 2:
		if (leapYear(year))
			return (unsigned short int)29;
		else return (unsigned short int)28;
	default:
		return (unsigned short int)0;
	}
}
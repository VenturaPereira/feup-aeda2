#pragma once

#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

unsigned int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	unsigned int CONSOLE_WIDTH = (csbi.srWindow.Right - csbi.srWindow.Left) / 2;

	return CONSOLE_WIDTH;

}

extern const unsigned int CONSOLE_WIDTH = getConsoleWidth();

/*void c(const string s) {
	cout << setw(CONSOLE_WIDTH + s.length() / 2) << s << endl;
}*/

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

template<typename T>
T enterInput(string title, string requestMsg)
{
	string line;
	T input;

	while (true)
	{
		system("CLS");
		cin.clear();
		cout << title  << requestMsg;
		getline(cin, line);
		if (cin.eof())
			throw EndOfFile();
		istringstream iss(line);
		iss >> input;
		if (!iss.fail() && line.length() > 0)
			return input;		
	}
}

void validFile(string fileType) {
	
	string requestMsg = "\nWhat's the name of your " + fileType + " file? ";
		
	while (true)
	{
		string fileName = enterString("", requestMsg);
		ifstream file(fileName);
		if (file.is_open())
		{
			cout << "\nFile found!\n";
			file.close();
			return;
		}
		else cout << "\nFile not found!\n";
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

bool leapYear(const unsigned short int &year);

unsigned short int numberDays(const unsigned short int &year, const unsigned short int &month);

class lowGrade
{
private:
	unsigned int grade;
public:
	lowGrade(unsigned int g) : grade(g) {}
	unsigned int getGrade() const { return grade; }
};

class EndOfFile
{
public:
	EndOfFile() {}
};
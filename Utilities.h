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

void c(const string s) {
	cout << setw(CONSOLE_WIDTH + s.length() / 2) << s << endl;
}

template<typename T>
T validInput(string badInput, string normalInput, string tryAgain)
{
	string line;
	T input;
	cout << normalInput;
	while (getline(cin, line))
	{
		istringstream iss(line);
		iss >> ws >> input >> ws;
		if (iss.fail() || !iss.eof())
		{
			cin.clear();
			system("cls");
			cerr << badInput;
			cout << endl << endl << tryAgain << normalInput;
		}
		else return input;
	}
	cin.clear();
	return NULL;
}

template<typename T>
T validInput(string &badInput, string &normalInput, vector<string> &tryAgain)
{
	string line;
	T input;
	cout << endl << endl;
	for (unsigned int i = 0; i < tryAgain.size(); i++)
		c(tryAgain[i]);
	cout << normalInput;
	while (getline(cin, line))
	{
		istringstream iss(line);
		iss >> ws >> input >> ws;
		if (iss.fail() || !iss.eof())
		{
			cin.clear();
			system("cls");
			cerr << badInput;
			cout << endl << endl;
			for (unsigned int i = 0; i < tryAgain.size(); i++)
				c(tryAgain[i]);
			cout << normalInput;
		}
		else return input;
	}
	cin.clear();
	return NULL;
}

/*string validFile(string fileType) {
	string fileName;
	while (true)
	{
		cout << "\nWhat's the name of your " << fileType << " file? ";
		getline(cin, fileName);
		ifstream file(fileName);
		if (file.is_open())
		{
			cout << "File found!\n";
			file.close();
			break;
		}
		else cout << "File not found!\n";
	}
	return fileName;
}*/

bool yesNoAnswer() {
	string answer;
	while (true)
	{
		cout << "Answer: ";
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

class lowGrade
{
private:
	unsigned int grade;
public:
	lowGrade(unsigned int g) : grade(g) {}
	unsigned int getGrade() const { return grade; }
};
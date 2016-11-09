#pragma once

#ifndef UTILITIES_H
#define UTILITIES_H

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

unsigned int getConsoleWidth();

extern const unsigned int CONSOLE_WIDTH;

void center(const string s);

string enterString(string title, string requestMsg);

template<typename T>
T enterInput(string title, string requestMsg)
{
	string line;
	T input;

	while (true)
	{
		system("CLS");
		cin.clear();
		cout << title << requestMsg;
		getline(cin, line);
		if (cin.eof())
			throw EndOfFile();
		istringstream iss(line);
		iss >> input;
		if (!iss.fail() && line.length() > 0)
			return input;
	}
}

template<typename T>
T enterInput(string title, vector<string> options)
{
	string line;
	T input;

	while (true)
	{
		system("CLS");
		cin.clear();
		center(title);
		for (size_t i = 0; i < options.size(); i++)
			center(options[i]);
		cout << "Select option: ";
		getline(cin, line);
		if (cin.eof())
			throw EndOfFile();
		istringstream iss(line);
		iss >> input;
		if (!iss.fail() && line.length() > 0)
			return input;
	}

}

template<typename T>
T enterInput()
{
	string line;
	T input;

	while (true)
	{
		cin.clear();
		cout << "Answer: ";
		getline(cin, line);
		if (cin.eof())
			throw EndOfFile();
		istringstream iss(line);
		iss >> input;
		if (!iss.fail() && line.length() > 0)
			return input;
	}
}

void validFile(string fileType);

bool yesNoAnswer();

bool leapYear(const unsigned short int &year);

unsigned short int numberDays(const unsigned short int &year, const unsigned short int &month);

class EndOfFile
{
public:
	EndOfFile() {}
};

template <class Type, class Member>
class NotFound
{
private:
	Member member;
public:
	NotFound(Member m) : member(m) {}
	Member getMember() const { return member; }
};

#endif
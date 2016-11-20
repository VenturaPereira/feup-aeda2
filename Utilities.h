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

/*!
 *	Returns Console Width
 */
unsigned int getConsoleWidth();

extern const unsigned int CONSOLE_WIDTH;

/*!
 *	Prints the Parameter s in the Center of the Screen
 */
void center(const string s);

/*!
 *	Outputs title and Request Message and Waits for Input and Returns it
 */
string enterString(string title, string requestMsg);

/*!
*	Template Function that Outputs Title and Request Message and Waits for Input and Returns it
*/
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

/*!
*	Template Function that Outputs Title and Options and Waits for Input and Returns it
*/
template<typename T>
T enterInput(string title, vector<string> options)
{
	string line;
	T input;

	while (true)
	{
		system("CLS");
		cin.clear();
		//center(title);
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

/*!
*	Template Function that Waits for Input and Returns it
*/
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

/*!
*	Checks If Input of User is Yes Or No (or variants) and Returns It
*/
bool yesNoAnswer();

/*!
*	Checks if a Year is 365 or 366 days
*/
bool leapYear(const unsigned short int &year);

/*!
*	Gets the number of days of a given month and year(can be a leap year)
*/
unsigned short int numberDays(const unsigned short int &year, const unsigned short int &month);

/*!
*	Class for Exceptions Handling
*/
class EndOfFile
{
public:
	EndOfFile() {}
};

/*!
*	Template Class for Exceptions Handling
*/
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
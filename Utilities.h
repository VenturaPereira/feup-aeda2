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
T enterInput(string title, string requestMsg);

template<typename T>
T enterInput(string title, vector<string> options);

void validFile(string fileType);

bool yesNoAnswer();

bool leapYear(const unsigned short int &year);

unsigned short int numberDays(const unsigned short int &year, const unsigned short int &month);

class EndOfFile
{
public:
	EndOfFile() {}
};

class lowGrade
{
private:
	unsigned int grade;
public:
	lowGrade(unsigned int g) : grade(g) {}
	unsigned int getGrade() const { return grade; }
};

#endif
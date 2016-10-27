#pragma once


class lowGrade
{
private:
	unsigned int grade;
public:
	lowGrade(unsigned int g) : grade(g) {}
	unsigned int getGrade() const { return grade; }
};
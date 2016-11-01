#pragma once

#ifndef MENU_H
#define MENU_H

#include "Date.h"

template <class FuntionReturn, class FunctionArguments>
class Menu 
{
private:
	string title;
	vector<string> optionsStr;
	vector<FuntionReturn(*)(FunctionArguments*)> optionsFunctions;
public:
	Menu(string t, vector<string> &os, vector<FuntionReturn(*)(FunctionArguments*)> &of);
	bool play(FunctionArguments* fa) const;
};

#endif

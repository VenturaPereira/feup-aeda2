#pragma once

#ifndef MENU_H
#define MENU_H

#include "Utilities.h"

template <class FuntionReturn, class FunctionArguments>
class Menu 
{
private:
	string title;
	vector<String> optionsStr;
	vector<FuntionReturn(*functions)(FunctionArguments*)> optionsFunctions;
public:
	Menu(string t, vector<string> &os, vector<FuntionReturn(*f)(FunctionArguments*)> &of);
	bool play(FunctionArguments* fa) const;
};

#endif

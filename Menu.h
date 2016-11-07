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
	vector<FuntionReturn(*)(FunctionArguments)> optionsFunctions;
public:
	Menu(string t, vector<string> &os, vector<FuntionReturn(*)(FunctionArguments)> &of);
	bool play(FunctionArguments fa);
};


template <class FuntionReturn, class FunctionArguments>
Menu<FuntionReturn, FunctionArguments>::Menu(string t, vector<string> &os, vector<FuntionReturn(*)(FunctionArguments)> &of)
{
	title = t;
	optionsStr = os;
	optionsFunctions = of;
}

template <class FuntionReturn, class FunctionArguments>
bool Menu<FuntionReturn, FunctionArguments>::play(FunctionArguments fa)
{
	size_t minimum = 1, maximum = optionsFunctions.size() + 1;
	unsigned int option;

	while (true)
	{
		option = enterInput<unsigned int>(title, optionsStr); //GET OPTIONS FROM USER
		if (option >= minimum && option <= (maximum - 1)) {
			optionsFunctions[option-1](fa); //CALL THE CORRESPONDENT FUNCTION
			return true;
		}
		else if (option == maximum) //EXIT
			return false;
	}
}

#endif

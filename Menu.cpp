#pragma once

#include "Menu.h"

template <class FuntionReturn, class FunctionArguments>
Menu<FuntionReturn, FunctionArguments>::Menu(string t, vector<string> &os, vector<FuntionReturn(*)(FunctionArguments*)> &of)
{
	title = t;
	optionsStr = os;
	optionsFunctions = of;
}

template <class FuntionReturn, class FunctionArguments>
bool Menu<FuntionReturn, FunctionArguments>::play(FunctionArguments* fa) const
{
	size_t minimum = 1, maximum = of.size() + 1;
	unsigned int option;

	while(true)
	{
		option = enterInput<unsigned int>(title, optionsStr); //GET OPTIONS FROM USER
		if (option >= minimum && option <= (maximum - 1)) {
			of[option](fa); //CALL THE CORRESPONDENT FUNCTION
			return true;
		}
		else if (option == maximum) //EXIT
			return false;
	}
}

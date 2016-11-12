#pragma once

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "Utilities.h"
using namespace std;


class Menu 
{
private:
	string title;
	vector<string> optionsStr;
	vector<bool(*)()> optionsFunctions;
public:
	Menu(string t, vector<string> &os, vector<bool(*)()> &of);
	bool play();
};


Menu::Menu(string t, vector<string> &os, vector<bool(*)()> &of)
{
	title = t;
	optionsStr = os;
	optionsFunctions = of;
}

bool Menu::play()
{
	size_t minimum = 1, maximum = optionsFunctions.size() + 1;
	unsigned int option;

	while (true)
	{
		option = enterInput<unsigned int>(title, optionsStr); //GET OPTIONS FROM USER
		if (option >= minimum && option <= (maximum - 1)) {
			optionsFunctions[option-1](); //CALL THE CORRESPONDENT FUNCTION
			return true;
		}
		else if (option == maximum) //EXIT
			return false;
	}
}

#endif

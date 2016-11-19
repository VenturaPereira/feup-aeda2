#pragma once

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
using namespace std;

class EnrollmentSystem;

unsigned int menuOption(string badInput, string normalInput, vector<string> tryAgain, unsigned int min, unsigned int max);
bool mainMenu(EnrollmentSystem &sys);
bool studentsMenu(EnrollmentSystem &sys);
bool professorsMenu(EnrollmentSystem &sys);
bool infoMenu(EnrollmentSystem &sys);
/*
bool modifyClientsMenu(Store &store);
bool modifyProductsMenu(Store &store);
bool clientsMenu(Store &store);
bool productsMenu(Store &store);
bool transactionsMenu(Store &store);
bool sortClientOptions(Store &store);
bool sortProductsOptions(Store &store);
bool sortTransactionsOptions(Store &store); */
bool optionsMenu(EnrollmentSystem &sys);

/*
class Menu 
{
private:
	string title;
	vector<string> optionsStr;
	vector<void(*)()> optionsFunctions;
public:
	Menu(string t, vector<string> &os, vector<void(*)()> &of);
	friend bool play(Menu &m);
};


Menu::Menu(string t, vector<string> &os, vector<void(*)()> &of)
{
	title = t;
	optionsStr = os;
	optionsFunctions = of;
}

bool play(Menu &m)
{
	size_t minimum = 1, maximum = m.optionsFunctions.size() + 1;
	unsigned int option;

	while (true)
	{
		option = enterInput<unsigned int>(m.title, m.optionsStr); //GET OPTIONS FROM USER
		if (option >= minimum && option <= (maximum - 1)) {
			m.optionsFunctions[option-1](); //CALL THE CORRESPONDENT FUNCTION
			return true;
		}
		else if (option == maximum) //EXIT
			return false;
	}
}
*/
#endif

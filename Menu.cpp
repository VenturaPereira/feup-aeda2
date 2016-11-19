#pragma once

#include "Menu.h"
#include "Utilities.h"
#include "EnrollmentSystem.h"

unsigned int menuOption(string badInput, string normalInput, vector<string> tryAgain, unsigned int min, unsigned int max){
	unsigned int option;
	while(true)
	{
		option = enterInput<unsigned int>(normalInput, tryAgain);
		if (option >= min && option <= max)
			return option;
	} 
}

bool mainMenu(EnrollmentSystem &sys){
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "==============================",
			"WELCOME", "",
			"1 - Students              ",
			"2 - Professors            ", 
			"3 - Information           " ,
			"4 - Options               ", "",
			"5 - Exit                  ",
			"==============================" }, 1, 5);
		switch (option)
		{
		case 1:
			studentsMenu(sys);
			break;
		case 2:
			professorsMenu(sys);
			break;
		case 3:
			infoMenu(sys);
			break;
		case 4:
			optionsMenu(sys);
			break;
		case 5:
			cout << "\nAre you sure you want to exit? (Y/N)\n";
			if (yesNoAnswer()){
				if (sys.getChanged()){
					cout << "\nDo you want to save your changes? (Y/N)\n";
					if (yesNoAnswer()){
						cout << "\n\nSaving. Don't turn off the power!";
						sys.saveHandler();
						cout << "\n\nSaving complete!\n\n";
						return true;
					}
					return true;
				}
				return true;
			}
			else
				break;
		}
	}
}

bool studentsMenu(EnrollmentSystem &sys){
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "==============================",
			"Enrollment System", "",
			"1 - Add Student           ",
			"2 - Remove Student        ", 
			"3 - Enroll                " , 
			"4 - Back                  ", 
			"==============================" }, 1, 4);
		switch (option)
		{
		case 1:
			addStudentHandler(sys);
				return true;
		case 2:
			removeStudentHandler(sys);
			return true;
		case 3:
			enrollmentHandler(sys);
				return true;
		case 4:
			return false;

		}
	}
}

bool professorsMenu(EnrollmentSystem &sys){
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "-------------------------------------",
			"Professors", "",
			"1 - Add Professor                ",
			"2 - Remove Professor             ",
			"3 - Grade Students               ", "",
			"4 - Back                         ",
			"-------------------------------------" }, 1, 4);
		switch (option)
		{
			/*
		case 1:
			addProfessorHandler(sys);
			//system("pause");
			return true;
		case 2:
			removeProfessorHandler(sys);
			//system("pause");
			return true; */
		case 3:
			studentFinishedCourseUnitHandler(sys);
			return true;
		case 4:
			return false;
		}
	}
}

//MODIFY FOR THIS PROJECT
bool infoMenu(EnrollmentSystem &sys){
	while (true)
	{
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "---------------------------------------",
			"Information", "",
			"1 - Read all Universities          ",
			"2 - Read all Colleges              ",
			"3 - Read all Courses               ",
			"4 - Read all Course Units          ",
			"5 - Read all Students              ",
			"6 - Read all Professors            ", "",
			"7 - Back                           ",
			"---------------------------------------" }, 1, 7);

		switch (option)
		{
		case 1:
			sys.showUniversities();
			system("pause");
			return true;
		case 2:
			sys.showColleges();
			system("pause");
			return true;
		case 3:
			sys.showCourses();
			system("pause");
			return true;
		case 4:
			sys.showCourseUnits();
			system("pause");
			return true;
		case 5:
			sys.showStudents();
			system("pause");
			return true;
		case 6:
			sys.showProfessors();
			system("pause");
			return true;
		case 7:
			return false;
		}
	}
}

//TODO CHECK  --- > MODIFY FOR THIS PROJECT  --- 
bool optionsMenu(EnrollmentSystem &sys)
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "--------------------------------------------",
			"Options", "",
			"1 - Change Students sorting options    ",
			"2 - Change Professors sorting options  ",
			"3 - Change Course Units sorting options", "",
			"4 - Back                               ",
			"--------------------------------------------", }, 1, 4);
		

		switch (option)
		{
		case 1:
			sortingStudentsMenu(sys);
			return true;
		case 2:
			return true;
		case 3:
			return true;
		case 4:
			return true;
		case 5:
			return false;
		}
	}
}

bool sortingStudentsMenu(EnrollmentSystem &sys) {
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "--------------------------------------------",
			"Students Sorting Options", "",
			"1 - Sort by ID                         ",
			"2 - Sort by Name                       ",
			"3 - Sort by Age                        ",
			"4 - Sort by Course Year                ", "",
			"5 - Back                               ",
			"--------------------------------------------", }, 1, 5);


		switch (option)
		{
		case 1:
			sys.changeStudentsSortOption(option);
			return true;
		case 2:
			sys.changeStudentsSortOption(option);
			return true;
		case 3:
			sys.changeStudentsSortOption(option);
			return true;
		case 4:
			sys.changeStudentsSortOption(option);
			return true;
		case 5:
			return false;
		}
	}
}

/*
bool mainMenu(Store &store)
{
	while (true)
	{
		system("cls");
		unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
		{ "=======================================",
			"Main Menu", "",
			"1 - Information                    ",
			"2 - Clients Management             ",
			"3 - Products Management            ",
			"4 - Transactions Management        ",
			"5 - Recommend Products to Client   ",
			"6 - Recommend Products to BottomTen", "",
			"7 - Options                        ",
			"8 - Return to Files' Names Menu    ",
			"9 - Exit App                       ",
			"=======================================" }, 1, 9);

		switch (option)
		{
		case 1:
		{
			informationMenu(store);
			break;
		}
		case 2:
		{
			clientsMenu(store);
			break;
		}
		case 3:
		{
			productsMenu(store);
			break;
		}
		case 4:
		{
			transactionsMenu(store);
			break;
		}
		case 5:
		{
			store.advertising();
			system("pause");
			break;
		}
		case 6:
		{
			store.makeBottomTenVectors();
			store.advertisingBottomTen();
			system("pause");
			break;
		}
		case 7:
			optionsMenu(store);
			break;
		case 8:
		{
			if (store.getClientChanged() || store.getProductsChanged() || store.getTransactionsChanged())
			{
				cout << "\nDo you want to save your changes? (Y/N)\n";
				if (yesNoAnswer())
				{
					cout << "\n\nSaving. Don't turn off the power!";
					store.saveChanges();
					cout << "\n\nSaving complete!\n\n";
					return false;
				}
				return false;
			}
			return false;
		}
		case 9:
		{
			cout << "\nAre you sure you want to exit? (Y/N)\n";
			if (yesNoAnswer())
			{
				if (store.getClientChanged() || store.getProductsChanged() || store.getTransactionsChanged())
				{
					cout << "\nDo you want to save your changes? (Y/N)\n";
					if (yesNoAnswer())
					{
						cout << "\n\nSaving. Don't turn off the power!";
						store.saveChanges();
						cout << "\n\nSaving complete!\n\n";
						return true;
					}
					return true;
				}
				return true;
			}
			else break;
		}
		}
	}
}*/
/*
bool informationMenu(Store &store)
{
while (true)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{ "-----------------------------------",
"Which file do you wish to read?", "",
"1 - Clients File     ",
"2 - Products File    ",
"3 - Transactions File", "",
"4 - Back             ",
"-----------------------------------" }, 1, 4);

switch (option)
{
case 1:
{
if (clientsInformationMenu(store))
return true;
break;
}
case 2:
{
store.displayProducts();
system("pause");
return true;
}
case 3:
{
if (transactionsInformationMenu(store))
return true;
break;
}
case 4:
return false;
}
}
}
bool modifyClientsMenu(Store &store)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{
"-------------------------------",
"What do you want to modify?", "",
"1 - Name  ",
"2 - Amount", "",
"3 - Back  ",
"-------------------------------" }, 1, 3);

switch (option)
{
case 1:
store.setClientsChanged(store.correctClientName());
system("pause");
return true;
case 2:
store.setClientsChanged(store.modifyClientAmount());
system("pause");
return true;
case 3:
return false;
}
}
bool modifyProductsMenu(Store &store)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{
"-------------------------------",
"What do you want to modify?", "",
"1 - Name ",
"2 - Price", "",
"3 - Back ",
"-------------------------------" }, 1, 3);

switch (option)
{
case 1:
store.setProductsChanged(store.changeProductName());
system("pause");
return true;
case 2:
store.setProductsChanged(store.changeProductPrice());
system("pause");
return true;
case 3:
return false;
}
}
bool clientsMenu(Store &store)
{
while (true)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{ "----------------------",
"Clients Management", "",
"1 - Add Clients   ",
"2 - Remove Clients",
"3 - Modify Clients", "",
"4 - Back          ",
"----------------------" }, 1, 4);

switch (option)
{
case 1:
{
store.setClientsChanged(store.addClient());
system("pause");
return true;
}
case 2:
{
store.setClientsChanged(store.removeClient());
system("pause");
return true;
}
case 3:
{
if (modifyClientsMenu(store))
return true;
break;
}
case 4:
return false;
}
}
}
bool productsMenu(Store &store)
{
while (true)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{ "-----------------------",
"Products Management", "",
"1 - Add Products   ",
"2 - Remove Products",
"3 - Modify Products", "",
"4 - Back           ",
"-----------------------" }, 1, 4);

switch (option)
{
case 1:
{
store.setProductsChanged(store.addProduct());
system("pause");
return true;
}
case 2:
{
store.setProductsChanged(store.removeProduct());
system("pause");
return true;
}
case 3:
{
if (modifyProductsMenu(store))
return true;
break;
}
case 4:
return false;
}
}
}
bool transactionsMenu(Store &store)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{ "---------------------------",
"Transactions Management", "",
"1 - Add Transactions   ",
"2 - Cancel Transactions", "",
"3 - Back               ",
"---------------------------" }, 1, 3);

switch (option)
{
case 1:
{
store.setTransactionsChanged(store.addTransaction());
system("pause");
return true;
}
case 2:
{
store.setTransactionsChanged(store.cancelTransaction());
system("pause");
return true;
}
case 3:
return false;
}
}*/ /*
bool sortClientOptions(Store &store)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{ "------------------------------",
"Client Sorting Options", "",
"1 - Sort by ID            ",
"2 - Sort by Names         ",
"3 - Sort by Subscribe Date",
"4 - Sort by Sum           ", "",
"5 - Back                  ",
"------------------------------", }, 1, 5);
switch (option)
{
case 1:
store.sortStore(store.getClientsVector());
return true;
case 2:
store.sortStore(store.getClientsVector(), compareClientByName);
return true;
case 3:
store.sortStore(store.getClientsVector(), compareClientBySubscribeDate);
return true;
case 4:
store.sortStore(store.getClientsVector(), compareClientBySum);
return true;
case 5:
return false;
}
}
bool sortProductsOptions(Store &store)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{ "---------------------------",
"Product Sorting Options", "",
"1 - Sort by Names",
"2 - Sort by Price", "",
"3 - Back         ",
"---------------------------", }, 1, 3);
switch (option)
{
case 1:
store.sortStore(store.getProductsVector());
return true;
case 2:
store.sortStore(store.getProductsVector(), compareProductByPrice);
return true;
case 3:
return false;
}
}
bool sortTransactionsOptions(Store &store)
{
system("cls");
unsigned int option = menuOption("Invalid Option!\n\n", "Menu Option: ",
{ "-------------------------------",
"Transaction Sorting Options", "",
"1 - Sort by ID  ",
"2 - Sort by Date", "",
"3 - Back        ",
"-------------------------------", }, 1, 3);
switch (option)
{
case 1:
store.sortStore(store.getTransactionsVector(), compareTransactionByID);
return true;
case 2:
store.sortStore(store.getTransactionsVector());
return true;
case 3:
return false;
}
}*/
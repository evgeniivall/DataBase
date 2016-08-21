#include<conio.h>
#include<windows.h>
#include <iostream>
#include "Declarations.h"

#define clrscr() system("cls")
#define TAB "\t\t"
#define Err cout << "The function not emplmented yet";

HANDLE hConsole, hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

extern int attributesAmount;

extern string fileName;
extern int databaseSize;

extern string infoFileName;
extern dataBaseInfo *dataBaseAttributes;
extern string* dataBaseItem;

extern void addAttribute(dataBaseInfo* att, int amount);


void searchModify(int attAmount, char operation);
int position = 0;

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


void mainMenu()
{
		clrscr();
		SetColor(15, 0);
		cout << TAB << "\tMenu" << endl;
		int positionColor[9];
		for (int i = 0; i < 9; i++)
		{
			positionColor[i] = 15;
		}
		positionColor[position] = 12;

		SetColor(positionColor[0], 0);
		cout << TAB << "Print database" << endl;
		SetColor(positionColor[1], 0);
		cout << TAB << "Search the item" << endl;
		SetColor(positionColor[2], 0);
		cout << TAB << "Add the item" << endl;
		SetColor(positionColor[3], 0);
		cout << TAB << "Modify the item" << endl;
		SetColor(positionColor[4], 0);
		cout << TAB << "Remove the item" << endl;
		SetColor(positionColor[5], 0);
		cout << TAB << "Rename database" << endl;
		SetColor(positionColor[6], 0);
		cout << TAB << "Information" << endl;
		SetColor(positionColor[7], 0);
		cout << TAB << "Return to the previous menu" << endl;
		SetColor(positionColor[8], 0);
		cout << TAB << "Exit" << endl;

		navigator(9, 'g');
		mainMenu();
}

void openMenu()
{
	clrscr();
	SetColor(15, 0);
	cout << TAB << "\tMenu" << endl;

	int positionColor[3];
	for (int i = 0; i < 3; i++)
	{
		positionColor[i] = 15;
	}
	positionColor[position] = 12;

	SetColor(positionColor[0], 0);
	cout << endl << TAB << "Open existing database" << endl;
	SetColor(positionColor[1], 0);
	cout << TAB << "Create new database" << endl;
	SetColor(positionColor[2], 0);
	cout << TAB << "Exit" << endl;

	navigator(3, 'o');
	openMenu();
}

void navigator(int menuMax, char mode)
{
	int choice = _getch();
	
	switch (choice)
	{
	case 80: 
	{
		if (position + 1 < menuMax)
			++position;
		else
			position = 0;
		break;
	}
	case 72:
	{
		if (position - 1 >= 0)
			--position;
		else
			position = menuMax - 1;
		break;
	}
	case 13:
	{
		switch (mode)
		{
		case 'a': Choiser(position - 10); break;
		case 'o': Choiser(position);		break;
		case 'g': Choiser(position + 10);	break;
		case 's':
		{
			if (position == (attributesAmount))
			{
				position = 0;
				mainMenu();
				break;
			}
			else
			{
				if (databaseSize == 0)
				{
					cout << "Database is empty!";
					_getch();
					mainMenu();
					break;
				}
				seatchDatabase(position);
				break;
			}
		}
		case 'm':
		{
			if (position == (attributesAmount))
			{
				position = 0;
				mainMenu();
				break;
			}
			else
			{
				if (databaseSize == 0)
				{
					cout << "Database is empty!";
					_getch();
					mainMenu();
					break;
				}
				cout << "Input id of the record, you want to modify: ";
				string modID;
				cin >> modID;
				while (idCheck(modID, 1, 0))
				{
					cin >> modID;
				}
				modifyDatabase(stoi(modID), position);
				break;
			}
		}
		}
	}
		
	}
	
}

void Choiser(int choise)  
{
	clrscr();
	switch (choise)
	{
	case 0:
	{
		position = 0;
		openExistingDatabase();
		break;
	}
	case 1: 
	{
		position = 0;
		createNewFile();
		addAttribute(0, 1);
		MENU();
		createNewDatabase();
		break;
	}
	case 2: exit(0);
	case 10: printDataBase();	break;
	case 11: position = 0; searchModify(attributesAmount + 1, 's');	break;
	case 12:
	{
		string* temp;
		temp = addInput();
		addNewItem(temp, 1);
		break;
	}
	case 13: position = 0; searchModify(attributesAmount + 1, 'm');	break;
	case 14:
	{
		if (databaseSize == 0)
		{
			cout << "Database is empty!";
			_getch();
			mainMenu();
			break;
		}
		string id;
		cout << "Input ID of the record, you want to delete: ";
		cin >> id;
		while (idCheck(id, 1, 1))
		{
			cin >> id;
		}
		removeItem(stoi(id), 1);
		break;
	}
	case 15:	//Rename databese
	{
		string newName;
		string newInfoName;
		clrscr();
		cout << "Enter the new name of database: ";
		cin >> newName;
		newInfoName = newName + "info.txt";
		newName += ".txt";
		{
			char *oldName = (char*)fileName.c_str();
			char *name = (char*)newName.c_str();
			rename(oldName, name);
		}
		{
			char *oldName = (char*)infoFileName.c_str();
			char *name = (char*)newInfoName.c_str();
			rename(oldName, name);
		}
		fileName = newName;
		infoFileName = newInfoName;
		break;
	}
	case  16:	infoAboutDatabase(2);		break;
	case  17:	position = 0;	openMenu();	break;
	case  18:	exit(0);
	case -10:	position = 0;	addAttribute(dataBaseAttributes, attributesAmount);	break;
	case  -9:	position = 0;   createNewDatabase();								break;
	
	}
}


void MENU()
{
	clrscr();
	int positionColor[2];

	for (int i = 0; i < 2; i++)
	{
		positionColor[i] = 15;
	}
	positionColor[position] = 12;

	SetColor(positionColor[0], 0);
	cout << endl << TAB << "Add new attribute" << endl;
	SetColor(positionColor[1], 0);
	cout << TAB << "Stop" << endl;

	navigator(2, 'a');
	MENU();
}

void searchModify(int attAmount, char operation)
{
	
	clrscr();
	int* positionColor = new int [attAmount];

	for (int i = 0; i < attAmount; i++)
	{
		positionColor[i] = 15;
	}
	positionColor[position] = 12;


	for (int i = 0; i < attAmount - 1; i++)
	{
		SetColor(positionColor[i], 0);
		cout << TAB << dataBaseAttributes[i].attributeName << endl;
	}
	SetColor(positionColor[attAmount - 1], 0);
	cout << TAB << "Return" << endl;

	switch (operation)
	{
	case 'm': navigator(attAmount, 'm');	searchModify(attAmount, 'm');	break;
	case 's': navigator(attAmount, 's');	searchModify(attAmount, 's');	break;
	}
	
}
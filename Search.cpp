
#include <iostream>
#include <string>
#include <fstream>
#include "Declarations.h"
#include "conio.h"

#define TAB "\t"

using namespace std;

extern int attributesAmount;
extern string fileName;
extern dataBaseInfo *dataBaseAttributes;
extern string* dataBaseItem;

extern int databaseSize;

extern string createDate;
extern string lastEditDate;

extern string infoFileName;

extern int position;

int seatchDatabase(int att)
{
	int head = 0;
	string input;
	cout << "Input searching value of attribute \"" << dataBaseAttributes[att].attributeName << "\": ";
	cin >> input;
	char *searchingValue = (char*)input.c_str();

	ifstream database;
	database.open(fileName);
	if (!database)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}


	while (!database.eof())
	{
		for (int i = 0; i < attributesAmount; i++)
		{
			database >> dataBaseItem[i];
		}
		if (!database.eof())
		{
			char *currentValue = (char*)dataBaseItem[att].c_str();
			
			if (!(_strcmpi(searchingValue, currentValue)))
			{
				if (head == 0)
				{
					cout << TAB << char(218);
					for (int i = 0; i < attributesAmount; i++)
					{
						for (int j(0); j < dataBaseAttributes[i].attributeLenght; j++)
							cout << char(196);
						if (i == attributesAmount - 1)
						{
							cout << char(191);
							break;
						}
						cout << char(194);
					}
					cout << endl << TAB << char(179);

					for (int i = 0; i < attributesAmount; i++)
					{
						SetColor(9, 0);
						cout.setf(ios::left);
						cout.width(dataBaseAttributes[i].attributeLenght);
						cout << dataBaseAttributes[i].attributeName;
						SetColor(15, 0);
						cout << char(179);
					}

					cout << endl << TAB << char(195);
					for (int i = 0; i < attributesAmount; i++)
					{
						for (int j(0); j < dataBaseAttributes[i].attributeLenght; j++)
							cout << char(196);
						if (i == attributesAmount - 1)
						{
							cout << char(180);
							break;
						}
						cout << char(197);
					}

					cout << endl;
					head++;
				}
				cout << TAB << char(179);
				for (int i = 0; i < attributesAmount; i++)
				{
					cout.setf(ios::left);
					cout.width(dataBaseAttributes[i].attributeLenght);
					cout << dataBaseItem[i] << char(179);
				}
				cout << endl;
			}
		}
	}
		if (head != 0)
		{
			cout << TAB << char(192);
			for (int i = 0; i < attributesAmount; i++)
			{
				for (int j(0); j < dataBaseAttributes[i].attributeLenght; j++)
					cout << char(196);
				if (i == attributesAmount - 1)
				{
					cout << char(217);
					break;
				}
				cout << char(193);
			}

			cout << endl;
			database.close();

			_getch();
			position = 0;
			mainMenu();
			return 0;
		}
		else
		{
			cout << "Item wasn`t found";
			cout << endl;
			database.close();
			_getch();
			searchModify(attributesAmount + 1, 's');
			return 0;
		}
	

	return 0;
}
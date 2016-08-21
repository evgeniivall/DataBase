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

int printDataBase()
{
	ifstream database;
	database.open(fileName);
	if (!database)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}
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

	cout << endl <<  TAB <<char(195);
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
	while (!database.eof())
	{
		for (int i = 0; i < attributesAmount; i++)
		{
			database >> dataBaseItem[i];
		}
		if (!database.eof())
		{
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
	return 0;
}
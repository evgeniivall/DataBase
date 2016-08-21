#include <iostream>
#include <string>
#include <fstream>
#include "Declarations.h"
#include "conio.h"

using namespace std;

extern int attributesAmount;
extern string fileName;
extern dataBaseInfo *dataBaseAttributes;
extern string* dataBaseItem;

extern int databaseSize;

extern string createDate;
extern string lastEditDate;

extern string infoFileName;

int idCheck(string id, int mode, int remove)
{

	if (inputProtect(id) )
	{
		cout << "ID can contains only digits!Try again: ";
		return 1;
	}
	if (!remove)
	{
		ifstream database;
		database.open(fileName);

		if (!database)
		{
			cout << "Cannot open file. " << endl;
			return 1;
		}
		while (!database.eof())
		{

			if (!database.eof())
			{
				for (int i = 0; i < attributesAmount; i++)
				{
					database >> dataBaseItem[i];
				}
				switch (mode)
				{

				case 0:
				{
					if (dataBaseItem[0] == id)
					{
						cout << "ID already exist! Try again: ";
						return 1;
					}
				}
				case 1:
				{
					if (dataBaseItem[0] == id)
					{
						return 0;
					}
				}
				}
			}
		}
		switch (mode)
		{
		case 0: return 0;
		case 1: cout << "Unexisting ID! Try again: "; return 1;
		}
	}
	return 0;
}


string* addInput()
{
	string *tempAddItem = new string[attributesAmount];

	cout << "Id : ";
	cin >> tempAddItem[0];
	
	if (databaseSize != 0)
	{
		while (idCheck(tempAddItem[0], 0, 0))
		{
			cin >> tempAddItem[0];
		}
	}
	if (tempAddItem[0].length() > dataBaseAttributes[0].attributeLenght)
		dataBaseAttributes[0].attributeLenght = tempAddItem[0].length();

	for (int i = 1; i < attributesAmount; i++)
	{
	
		cout << "Input " << dataBaseAttributes[i].attributeName << ": ";
		cin >> tempAddItem[i];
		
		if (tempAddItem[i].length() > dataBaseAttributes[i].attributeLenght)
		{
			dataBaseAttributes[i].attributeLenght = tempAddItem[i].length();
		}
	}

	return tempAddItem;
}


int addNewItem(string *tempItem, int resultOutput)
{
	int check = 0;
	
	ifstream database;
	database.open(fileName);
	if (!database)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}

	ofstream tempFile;
	tempFile.open("temp.txt");
	if (!tempFile)
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
		if (databaseSize != 0)
		{
			if ((stoi(dataBaseItem[0]) > stoi(tempItem[0])) && (check == 0))
			{
				for (int i = 0; i < attributesAmount; i++)
				{
					tempFile.setf(ios::left);
					tempFile.width(dataBaseAttributes[i].attributeLenght);
					tempFile << tempItem[i] << ' ';
				}
				tempFile << endl;
				check++;
			}
		}
		if (!database.eof())
		{
			for (int i = 0; i < attributesAmount; i++)
			{
				tempFile.setf(ios::left);
				tempFile.width(dataBaseAttributes[i].attributeLenght);
				tempFile << dataBaseItem[i] << ' ';
			}
			tempFile << endl;
		}

	}
	if (check == 0)
	{
		for (int i = 0; i < attributesAmount; i++)
		{
			tempFile.setf(ios::left);
			tempFile.width(dataBaseAttributes[i].attributeLenght);
			tempFile << tempItem[i] << ' ';
		}
		tempFile << endl;
	}
	database.close();
	tempFile.close();

	if (resultOutput)
	{
		cout << "Item ID " << tempItem[0] << " was succesfully added.\n";
		delete[]tempItem;
	}

	char *name = (char*)fileName.c_str();
	remove(name);
	rename("temp.txt", name);

	//Rewrite infofile
	ifstream databaseInfoFile;
	databaseInfoFile.open(infoFileName);
	if (!databaseInfoFile)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}
	ofstream tempInfoFile;
	tempInfoFile.open("tempInfo.txt");
	if (!tempInfoFile)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}

	databaseInfoFile >> attributesAmount;
	tempInfoFile << attributesAmount << ' ';

	for (int i = 0; i < attributesAmount; i++)
	{
		int previous_size;
		databaseInfoFile >> previous_size;
		tempInfoFile << dataBaseAttributes[i].attributeLenght <<  ' ';
	}
	databaseInfoFile >> databaseSize;
	databaseSize++;
	tempInfoFile << databaseSize;
	tempInfoFile << endl;

	for (int i = 0; i < attributesAmount; i++)
	{
		databaseInfoFile >> dataBaseAttributes[i].attributeName;
		tempInfoFile << dataBaseAttributes[i].attributeName << ' ';
	}

	tempInfoFile << endl;
	lastEditDate = dateTime();
	tempInfoFile << createDate;
	tempInfoFile << endl;
	tempInfoFile << lastEditDate;
	tempInfoFile << endl;

	databaseInfoFile.close();
	tempInfoFile.close();
	char *infoName = (char*)infoFileName.c_str();
	remove(infoName);
	rename("tempInfo.txt", infoName);

	if (resultOutput)
	{
		_getch();
	}

	return 0;
	
}



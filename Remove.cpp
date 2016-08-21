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
extern string infoFileName;


extern string createDate;
extern string lastEditDate;

int removeItem(int ID, int resultOutput)
{
	if (databaseSize == 0)
	{
		cout << "Database is empty!";
		_getch();
		return 0;
	}
	int test = 0;
	ifstream database;
	database.open(fileName);
	if (!database)
	{
		cout << "Cannot open file. " << endl;
		return 1;
	}

	ofstream tempFile;
	tempFile.open("temp.txt");
	if (!tempFile)
	{
		cout << "Cannot open file. " << endl;
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
			if (stoi(dataBaseItem[0]) == ID)
			{
				test = 1;
				continue;
			}
			for (int i = 0; i < attributesAmount; i++)
			{
				tempFile.setf(ios::left);
				tempFile.width(dataBaseAttributes[i].attributeLenght);
				tempFile << dataBaseItem[i] << ' ';
			}
			tempFile << endl;
		}
	}

	tempFile.close();
	database.close();
	if (resultOutput)
	{
		if (test == 1)
		{
			cout << "Record " << ID << " was succesfully removed from database.\n";
		}
		else
		{
			cout << "Record " << ID << " is not found.\n";
			_getch();
			return 0;
		}
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
		databaseInfoFile >> dataBaseAttributes[i].attributeLenght;
		tempInfoFile << dataBaseAttributes[i].attributeLenght << ' ';
	}
	databaseInfoFile >> databaseSize;
	tempInfoFile << --databaseSize;
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

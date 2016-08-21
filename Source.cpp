
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include "Declarations.h"
#include "conio.h"
#include <ctime>
#include <Windows.h>


using namespace std;

//Global variables
int attributesAmount;			//The amount of attributes
int databaseSize;				//The amount of 
string fileName;				//Full direction to the .txt database file
string infoFileName;
string createDate;
string lastEditDate;



dataBaseInfo *dataBaseAttributes;	//Dynamic array of structs, which contains name and field width of the attribute
string* dataBaseItem;				//Dynamic array of strings, which contains attributes values

void addAttribute(dataBaseInfo* att, int amount);


int main()
{

	openMenu();

	system("pause");
	delete[]dataBaseAttributes;
	delete[]dataBaseItem;

	return 0;
}

int createNewDatabase()
{
	databaseSize = 0;
	ofstream databaseInfoFile;
	databaseInfoFile.open(infoFileName);
	
	databaseInfoFile << attributesAmount << ' ';
	for (int i = 0; i < attributesAmount; i++)
	{
		databaseInfoFile << dataBaseAttributes[i].attributeLenght << ' ';
	}
	databaseInfoFile << databaseSize;
	databaseInfoFile << endl;

	for (int i = 0; i < attributesAmount; i++)
	{
		databaseInfoFile.setf(ios::left);
		databaseInfoFile.width(dataBaseAttributes[i].attributeLenght);
		databaseInfoFile << dataBaseAttributes[i].attributeName << ' ';
	}
	
	databaseInfoFile << endl;
	createDate = dateTime();
	lastEditDate = dateTime();
	databaseInfoFile << createDate;
	databaseInfoFile << endl;
	databaseInfoFile << lastEditDate;
	databaseInfoFile << endl;
	databaseInfoFile.close();
	
	dataBaseItem = new string[attributesAmount];

	infoAboutDatabase(1);
	return 0;
}

void addAttribute(dataBaseInfo* att, int amount)
{
	system("cls");
	cout << endl;

	if (amount == 1)
	{
		att = new dataBaseInfo[amount + 1];
		att[0].attributeName = "ID";
		att[0].attributeLenght = 2;
	}
	else
	{
		dataBaseInfo* tempAttribute = new dataBaseInfo[amount + 1];

		for (int i = 0; i < amount; i++)
		{
			tempAttribute[i] = att[i];
		}
		delete[] att;

		att = tempAttribute;
	}

	cout << "Enter the name of the " << amount << " attribute: ";
	cin >> att[amount].attributeName;
	att[amount].attributeLenght = att[amount].attributeName.length();

	
	amount++;
	attributesAmount = amount;
	dataBaseAttributes = att;

	return;

}


int openExistingDatabase()
{
	cout << endl << "Enter the directory to the file of database: ";
	cin >> fileName;
	
	infoFileName = fileName;
	infoFileName[infoFileName.length() - 4] = 'i';
	infoFileName[infoFileName.length() - 3] = 'n';
	infoFileName[infoFileName.length() - 2] = 'f';
	infoFileName[infoFileName.length() - 1] = 'o';
	infoFileName += ".txt";

	ifstream databaseInfoFile;
	databaseInfoFile.open(infoFileName);

	if (!databaseInfoFile)
	{
		cout << "Cannot open file" << endl;
		openExistingDatabase();
		return 0;
	}
	databaseInfoFile >> attributesAmount;

	dataBaseAttributes = new dataBaseInfo[attributesAmount];
	for (int i = 0; i < attributesAmount; i++)
	{
		databaseInfoFile >> dataBaseAttributes[i].attributeLenght;
	}
	databaseInfoFile >> databaseSize;
	for (int i = 0; i < attributesAmount; i++)
	{
		databaseInfoFile >> dataBaseAttributes[i].attributeName;
	}
	createDate = "\0";
	for (int i = 0; i < 5; i++)
	{
		string temp;
		databaseInfoFile >> temp;
		createDate += temp + ' ';
	}
	lastEditDate = "\0";
	for (int i = 0; i < 5; i++)
	{
		string temp;
		databaseInfoFile >> temp;
		lastEditDate += temp + ' ';
	}

	dataBaseItem = new string[attributesAmount];
	databaseInfoFile.close();
	infoAboutDatabase(0);
	
	return 0;
}

void createNewFile()
{
	cout << "Enter the name of file: ";
	cin >> fileName;

	ofstream database;
	database.open(fileName + ".txt");

	cout << "Database " << fileName << " was successfully created. " << endl;

	infoFileName = fileName + "Info.txt";

	ofstream databaseInfoFile;
	databaseInfoFile.open(infoFileName);
	
	fileName += ".txt";
	database.close();
	databaseInfoFile.close();
	return;
}

void infoAboutDatabase(int mode)
{
	SetColor(15, 0);
	cout << endl << endl;
	switch (mode)
	{
	case 0: cout << "\tDatabase " << fileName << " was succsessfully opened."; break;
	case 1: cout << "\tDatabase " << fileName << " was succsessfully created."; break;
	case 2: break;
	}
	cout << "\n\n\tDatabase has " << attributesAmount << " attributes:\n";
	for (int i = 0; i < attributesAmount; i++)
	{
		cout << "\t\t" << dataBaseAttributes[i].attributeName << "\tField width: " << dataBaseAttributes[i].attributeLenght << endl;
	}
	cout << "\n\tDatabase has " << databaseSize << " records." << endl << endl;
	cout << "\tCreated:\t\t" << createDate << endl;
	cout << "\tLast modification:\t" << lastEditDate << endl;
	

	_getch();
	mainMenu();
}

string dateTime()
{
	string currentTime;
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	currentTime = asctime(timeinfo);
	return currentTime;
}


int inputProtect(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (!((str[i] >= 48) && (str[i] <= 57)))
		{
			return 1;
		}
	}
	return 0;
}

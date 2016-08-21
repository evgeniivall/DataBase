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


int modifyDatabase(int ID, int att)
{

	int test = 0;
	string oldFeatureValue;
	

	ifstream database;
	database.open(fileName);
	if (!database)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}
	string* modifyTemp = new string[attributesAmount];

	while (!database.eof())
	{
		for (int i = 0; i < attributesAmount; i++)
		{
			database >> modifyTemp[i];
		}
		oldFeatureValue = modifyTemp[att];
		if (!database.eof())
		{
			if (stoi(modifyTemp[0]) == ID)
			{
				cout << "Old value is: \"" << oldFeatureValue << "\".\n";
				cout << "Enter new value of " << dataBaseAttributes[att].attributeName;
				cin >> modifyTemp[att];

				if (!(modifyTemp[att].length() > dataBaseAttributes[att].attributeLenght))
				{
					dataBaseAttributes[att].attributeLenght = modifyTemp[att].length();
				}
				
				if (att == 0)
				{
					database.close();
					while (idCheck(modifyTemp[0], 0, 0))
					{
						cin >> modifyTemp[0];
					}
					removeItem(ID, 0);
					addNewItem(modifyTemp, 0);
				}
				else
				{
					database.close();
					removeItem(ID, 0);
					addNewItem(modifyTemp, 0);
				}
				break;

			}

		}
	}

	cout << "The " << dataBaseAttributes[att].attributeName << " was successfully changed from " << oldFeatureValue << " to " << modifyTemp[att];

	_getch();
	mainMenu();
	
	return 0;


}
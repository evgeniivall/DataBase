#pragma once
#include <string>



using namespace std;

void openMenu();
void mainMenu();
void navigator(int menuMax, char mode);
void Choiser(int choise);

void infoAboutDatabase(int mode);
string dateTime();
void SetColor(int text, int background);

int seatchDatabase(int att);
//extern int SIZE;
//extern string fileName;
//extern dataBaseInfo *dataBaseAttributes;


void MENU();
void createNewFile();

int idCheck(string id, int mode, int remove);

int addNewItem(string *tempItem, int resultOutput);
string* addInput();

int modifyDatabase(int ID, int att);

int printDataBase();
void openMenu();
void mainMenu();
int openExistingDatabase();
int createNewDatabase();

int removeItem(int ID, int resultOutput);

int inputProtect(string str);

void searchModify(int attAmount, char operation);

struct dataBaseInfo
{
	string attributeName;
	int attributeLenght;
};
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Menu
{
	static bool endProg;
	string option;
public:
	void openingMain();
	void displayMain();
	void setOption();
	string getOption();
	bool checkendProg();
	void displaySubMenu(string);
	void displaySubMenu2(string);
	void resetOpt();
	void setFrtfile(string&);
	void setCgofile(string&);
	void displaySaveMenu();
};


#pragma once
# include <string>
#include <iostream>
using namespace std;

class Base
{
private:
	string ID;
	string Destination;
	int time;
public:
	Base(string, string, int);
	virtual string getID();
	virtual string getDestination();
	virtual int getTime();
	virtual void setID(string);
	virtual void setTime(int);
	virtual void setDestination(string);
};


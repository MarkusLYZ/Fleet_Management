#pragma once //Aaron Ng
#include "Base.h"
#include <iostream>
#include<vector>

class Freight :
    public Base
{
    friend std::ostream& operator<<(std::ostream& out, Freight& frt);
    int capacity;
public:
    Freight(string id = "Unnamed Freight", string dest = "SGP", int time = 0, int cap = 2);
    void setCapacity(int cap);
    int getCapacity();
    void decCapacity();
    void showFreight();
    static void deleteFreight(vector<Freight>& freightList, bool& newupdate);
    static void editFreight(vector<Freight>& freightList, bool& newupdate);
    static void addFreight(vector<Freight>& freightList, bool& newupdate);
};


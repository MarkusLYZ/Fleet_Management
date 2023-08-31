#pragma once
#include "Base.h"
#include <vector>

class Cargo :
    public Base
{
    friend std::ostream& operator<<(std::ostream& out, Cargo& frt);
public:
    void showCargo();
    Cargo(string id = "Unnamed cargo", string dest = "SGP", int time = 0);
    static void deleteCargo(vector<Cargo>&, bool& newupdate);
    static void editCargo(vector<Cargo>&, bool& newupdate);
    static void addCargo(vector<Cargo>&, bool& newupdate); 
};

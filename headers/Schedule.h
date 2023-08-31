#pragma once
#include "Freight.h"
#include "Cargo.h"
#include <fstream>

class Schedule :
    public Cargo, Freight
{
    friend std::ostream& operator<<(std::ostream& out, Schedule& sch);
private:
    int schNum;
    Freight freight;
    Cargo cargo;
public:
    Schedule(int sid, Freight freight, Cargo cargo);
    //constructor with individual aruguments - overloading a new constructor
    Schedule(int sid, string fid, string fdest, int ftime, int cap, string cid, string cdest, int ctime);
    void showInfo();
};



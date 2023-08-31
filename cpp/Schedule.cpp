#include "Schedule.h"

Schedule::Schedule(int sid, Freight fgt, Cargo cgo) : freight(fgt), cargo(cgo)
{//call freight constructor and cargo constructor
    schNum = sid;
}
//constructor with individual aruguments
Schedule::Schedule(int sid, string fid, string fdest, int ftime, int cap, string cid, string cdest, int ctime) : freight(fid, fdest, ftime, cap), cargo(cid, cdest, ctime)
{
    schNum = sid;
}

void Schedule::showInfo() {
    //For debug
    cout << schNum << " ";
    freight.showFreight(); //chain to freight.showInfo()
    cout << "\t";
    cargo.showCargo();	//chain to cargo.showInfo()
    cout << endl;
}

ostream& operator<<(std::ostream& out, Schedule& sch) {
    out << sch.schNum << " " << sch.freight.getID() << " " << sch.freight.getCapacity() << " " << sch.freight.getDestination() << " "
        << sch.freight.getTime() << " " << sch.cargo.getID() << " " << sch.cargo.getDestination() << " " << sch.cargo.getTime() << endl;
    return out;
}
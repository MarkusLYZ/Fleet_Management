#include "Freight.h" // Aaron Ng
#include<fstream>
#include <iomanip>
using namespace std;

Freight::Freight(string id, string dest, int time, int cap)
    : Base(id, dest, time)			//call Base constructor
{
    capacity = cap;
}

void Freight::setCapacity(int cap) { //set freight capacity
    capacity = cap;
}

int Freight::getCapacity() { //retrieve capacity
    return capacity;
}

void Freight::decCapacity() { //decrease capacity after add cargo
    capacity--;
}

void Freight::showFreight() { //Display freight 
    //For debug
    cout << Base::getID() << "\t" << capacity << "\t" << Base::getDestination() << "\t\t" << setfill('0') << setw(4) << Base::getTime();
}

ostream& operator<<(std::ostream& out, Freight& frt) { //
    out << frt.getID() << "," << frt.capacity << "," << frt.getDestination() << "," << frt.getTime();
    return out;
}

void Freight::deleteFreight(vector<Freight>& freightList, bool& newupdate) { //delete freight member
    string deletefline;
    int freightInd = 0;
    bool ffound = false;


    cout << "Delete Freight:\n\n" << "Please enter Freight ID to be deleted. E.g F01: (Press '-1' to return)\n>"; //input line to remove
    cin >> deletefline;
    while (ffound == false && deletefline != "-1") {
        if (deletefline[0] != 'F') {
            cout << "Freight ID is in wrong format, E.g of a Freight ID, F01.\nEnter Freight ID:\n";
            cin >> deletefline;
        }
        else {
            for (int i = 0; i < freightList.size(); i++) {
                if (freightList[i].getID() == deletefline) { //find freight member
                    freightInd = i;
                    ffound = true;
                    cout << "Freight ID: " << deletefline << " has sucessfully been deleted from the list.\n";
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    freightList[freightInd].showFreight();
                    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    freightList.erase(freightList.begin() + freightInd);
                    newupdate = true;
                    break;
                }
                else if (i == freightList.size() - 1 && freightInd == 0) {
                    cout << "Freight ID not found\n";
                    cout << "Please enter the Freight ID to edit, e.g F01 (press '-1' to return): \n";
                    cin >> deletefline;
                }
            }
        }
    }
}

void Freight::editFreight(vector<Freight>& freightList, bool& newupdate) { //edit freight member
    string id, newedit, opt;
    int changefre = 0;
    bool ffound = false;
    bool accept = false;

    system("CLS");
    cout << "EDIT Freight\n\n";
    cout << "Please enter the Freight ID to edit, e.g F01 (press '-1' to return): \n";
    cin >> id;
    while (ffound == false && id != "-1") {
        if (id[0] != 'F') {
            cout << "Freight ID is in wrong format, E.g of a Freight ID, F01.\nEnter Freight ID:\n";
            cin >> id;
        }
        else {
            for (int i = 0; i < freightList.size(); i++) {
                if (freightList[i].getID() == id) { //find freight member
                    changefre = i;
                    cout << "Freight ID " << id << " found in freight list!\n";
                    ffound = true;
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    freightList[i].showFreight();
                    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    break;
                }
                else if (i == freightList.size() - 1 && changefre == 0) {
                    cout << "Freight ID not found\n";
                    cout << "Please enter the Freight ID to edit, e.g F01 (press '-1' to return): \n";
                    cin >> id;
                }
            }
        }
    }

    if (id != "-1") {

        cout << "\nFreight attributes:\n"
            << "1. Freight ID\n"
            << "2. Capacity\n"
            << "3. Destination\n"
            << "4. Refuel time\n"
            << "5. Back to Previous Menu\n"
            << "\nPlease enter your option:\n";

        cin >> opt;
        while (isdigit(opt[0]) == false) {
            cout << "Invaid input, please try agian.\nPlease enter your option:\n>";
            cin.ignore();
            cin >> opt;
        }
        while (stoi(opt) > 5) {
            cout << "Invaid option, please try agian.\nPlease enter your option:\n>";
            cin.ignore();
            cin >> opt;
        }

        switch (stoi(opt)) {
        case 1:
            cout << "Enter new Freight ID:\n";
            cin >> newedit;
            while (accept == false && newedit != "-1") {
                if (newedit[0] != 'F') { //data validation
                    cout << "Freight ID is in wrong format, E.g of a Freight ID, F01.\nEnter NEW Freight ID:\n";
                    cin >> newedit;
                }
                else {
                    for (int i = 0; i < freightList.size(); i++) {
                        if (freightList[i].getID() == newedit) { //check if ID already exists
                            cout << "Freight ID already exist, Enter a NEW Freight ID:\n";
                            cin >> newedit;
                            break;
                        }
                        else if (i == freightList.size() - 1) {
                            accept = true;
                            freightList[changefre].setID(newedit);
                            newupdate = true;
                            cout << "Freight ID " << id << " has been changed to " << newedit << ".\n";
                            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                            freightList[changefre].showFreight();
                            cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                        }
                    }
                }
            }
            break;

        case 2:
            cout << "Enter new Freight's Capacity small(2), large(4), super(6):\n";
            cin >> newedit;
            while (accept == false && newedit != "-1") {
                if (newedit == "2" || newedit == "4" || newedit == "6") {
                    accept = true;
                    freightList[changefre].setCapacity(stoi(newedit));
                    newupdate = true;
                    cout << "Freight's capacity has been changed to " << newedit << ".\n";
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    freightList[changefre].showFreight();
                    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                }
                else {//data validation
                    cout << "Choose either 2, 4 or 6 ONLY.\nEnter Freight Capacity small(2), large(4), super(6): \n";
                    cin >> newedit;
                }
            }
            break;

        case 3:
            cout << "Enter new Freight's destination:\n";
            cin >> newedit;
            while (accept == false && newedit != "-1") {
                if (newedit == "London" || newedit == "Paris") {
                    accept = true;
                    freightList[changefre].setDestination(newedit);
                    newupdate = true;
                    cout << "Freight's destination has been changed to " << newedit << ".\n";
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    freightList[changefre].showFreight();
                    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                }
                else { //data validation assuming only locations available are london and paris
                    cout << "Choose only London or Paris:\nEnter Freight destination in string (London or Paris) : \n";
                    cin >> newedit;
                }
            }
            break;
        case 4:
            cout << "Enter NEW Freight's refuel time:\n";
            cin >> newedit;
            while (accept == false && newedit != "-1") {
                for (int i = 0; i < newedit.size(); i++) {
                    if (isdigit(newedit[i]) == false || newedit.size() != 4) { //data validation for time
                        cout << "Wrong format, please input a 4 digit number in 24hrs format.\nEnter Freight refuel time in international time, eg. 0900 : ";
                        cin >> newedit;
                    }
                    else {
                        accept = true;
                        freightList[changefre].setTime(stoi(newedit));
                        newupdate = true;
                        cout << "Freight's refuel time has been changed to " << newedit << ".\n";
                        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                        freightList[changefre].showFreight();
                        cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    }
                }
            }
            break;
        default:
            break;
        }

    }
}

void Freight::addFreight(vector<Freight>& freightList, bool& newupdate) {
    Freight tmpFre("F01", "London", 0754, 2);
    string id, cap, dest, arr;
    bool accept = false;
    cout << "Enter Freight ID, eg. F01 : " << endl;
    cin >> id;
    while (accept == false) {
        if (id[0] != 'F') {
            cout << "Freight ID is in wrong format, E.g of a Freight ID, F01.\nEnter NEW Freight ID:\n";
            cin >> id;
        }
        else {
            for (int i = 0; i < freightList.size(); i++) {
                if (freightList[i].getID() == id) {
                    cout << "Freight ID already exist, Enter a NEW Freight ID:\n";
                    cin >> id;
                    break;
                }
                else if (i == freightList.size() - 1) {
                    accept = true;
                }
            }
        }
    }
    accept = false;
    cout << "Enter Freight Capacity small(2), large(4), super(6): " << endl;
    cin >> cap;
    while (accept == false) {
        if (cap == "2" || cap == "4" || cap == "6") {
            accept = true;
        }
        else {
            cout << "Choose either 2, 4 or 6 ONLY.\nEnter Freight Capacity small(2), large(4), super(6): \n";
            cin >> cap;
        }
    }
    accept = false;
    cout << "Enter Freight destination in string (London or Paris) : " << endl;
    cin >> dest;
    while (accept == false) {
        if (dest == "London" || dest == "Paris") {
            accept = true;
        }
        else {
            cout << "Choose only London or Paris:\nEnter Freight destination in string (London or Paris) : \n";
            cin >> dest;
        }
    }
    accept = false;
    cout << "Enter Freight refuel time in international time, eg. 0900 : " << endl;
    cin >> arr;
    while (accept == false) {
        for (int i = 0; i < arr.size(); i++) {
            if (isdigit(arr[i]) == false || arr.size() !=4) {
                cout << "Wrong format, please input a 4 digit number in 24hrs format.\nEnter Freight refuel time in international time, eg. 0900 : ";
                cin >> arr;
            }
            else {
                    accept = true;
            }
        }
    }
    accept = false;

    tmpFre.setID(id);
    tmpFre.setCapacity(stoi(cap));
    tmpFre.setDestination(dest);
    tmpFre.setTime(stoi(arr));

    freightList.push_back(tmpFre); //save to freight vector
    newupdate = true;

    cout << "Successfully added Freight!" << endl;
    cout << "----------------------------------------\n";
    tmpFre.showFreight();
    cout << "\n----------------------------------------\n";
}


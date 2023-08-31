#include "Cargo.h"
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <cstring>
#include <iomanip>

using namespace std;
Cargo::Cargo(string id, string des, int t) : Base(id, des, t) {};

void Cargo::showCargo() {
    cout << Base::getID() << "\t" << Base::getDestination() << "\t\t" << setfill('0') << setw(4) << Base::getTime();
}

void Cargo::deleteCargo(vector<Cargo>& cargoList, bool& newupdate) {
    string deleteline;
    int cargoInd = 0;
    bool cfound = false;

    cout << "DELETE CARGO:\n\n" << "Please enter Cargo ID to be deleted. E.g C01:\n>"; //input line to remove
    cin >> deleteline;
    while (cfound == false && deleteline != "-1") {//check if input has C infront and it is not a -1 if not it will loop back here
        if (deleteline[0] != 'C') {
            cout << "Cargo ID is in wrong format, E.g of a Cargo ID, F01.\nEnter Cargo ID:\n";
            cin >> deleteline;
        }
        else {
            for (int i = 0; i < cargoList.size(); i++) {//loops the vector list to check if the ID exist
                if (cargoList[i].getID() == deleteline) {//check if user input is same as id in vector list
                    cargoInd = i;//store the position of the vector to be deleted into cargoind
                    cfound = true;
                    cout << "CARGO ID: " << deleteline << " has sucessfully been deleted from the list.\n";
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    cargoList[cargoInd].showCargo();
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    cargoList.erase(cargoList.begin() + cargoInd);//deletes the vector using the position num of the vector
                    newupdate = true;
                    break;
                }
                else if (i == cargoList.size() - 1 && cargoInd == 0) {//after looping till the last i value, means its not found
                    cout << "Freight ID not found\n";
                    cout << "Please enter the Freight ID to edit, e.g F01 (press '-1' to return): \n";
                    cin >> deleteline;
                }
            }
        }
    }
}

void Cargo::editCargo(vector<Cargo>& cargoList, bool& newupdate) {
    string id;
    string newedit;
    string opt;
    int changecar = 0;
    bool cfound = false;
    bool acceptedchg = false;

    system("CLS");
    cout << "EDIT CARGO\n\n";
    cout << "Please enter the Cargo ID to edit, e.g C01 (press '-1' to return): \n>";//prompt for user input of id
    cin >> id;//stores user input into id
    while (cfound == false && id != "-1") {
        if (id[0] != 'C') {//check if user input enters C for cargo instead of F for freight
            cout << "Cargo ID is in wrong format, E.g of a Cargo ID, C01.\nEnter Cargo ID:\n>";//prints error statement
            cin >> id;
        }
        else {
            for (int i = 0; i < cargoList.size(); i++) {//loops the vector list to check if the ID exist
                if (cargoList[i].getID() == id) {//check if user input is same as id in vector list
                    changecar = i;//store the position of the vector to be edited into changecar
                    cout << "Cargo ID " << id << " found in cargo list!\n";
                    cfound = true;
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    cargoList[i].showCargo();//prints the cargo info to be edited
                    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    break;
                }
                else if (i == cargoList.size() - 1 && changecar == 0) {
                    cout << "Cargo ID not found!\n";
                    cout << "Please enter the Cargo ID to edit, e.g C01 (press '-1' to return): \n>";
                    cin >> id;
                }
            }
        }
    }

    if (id != "-1") {

        cout << "\nCargo items:\n"
            << "1. Cargo ID\n"
            << "2. Destination\n"
            << "3. Arrival time\n"
            << "4. Back to Previous Menu\n"//prompts user to change which specific data to edit
            << "\nPlease enter your option:\n";

        cin >> opt;
        while (isdigit(opt[0]) == false) {//isdigit checks if the first character in str is a digit
            cout << "Invaid input, please try agian.\nPlease enter your option:\n>";
            cin.ignore();
            cin >> opt;
        }
        while (stoi(opt) > 4) {//converts to int and checks if input doesnt exceed 4
            cout << "Invaid option, please try agian.\nPlease enter your option:\n>";
            cin.ignore();
            cin >> opt;
        }


        switch (stoi(opt)) {
        case 1:
            cout << "Enter NEW Cargo ID:\n";//prompts user for new cargo id
            cin >> newedit;//stores in string newedit
            while (acceptedchg == false && newedit != "-1") {
                if (newedit[0] != 'C') {//check if user input enters C for cargo instead of F for freight
                    cout << "Cargo ID is in wrong format, E.g of a Cargo ID, C01.\nEnter NEW Cargo ID:\n";//prints error statement
                    cin >> newedit;
                }
                else {
                    for (int i = 0; i < cargoList.size(); i++) {//loops the vector list to check if the ID exist
                        if (cargoList[i].getID() == newedit) {//check if user input is same as id in vector list
                            cout << "Cargo ID already exist, Enter a NEW Cargo ID:\n";
                            cin >> newedit;
                            break;
                        }
                        else if (i == cargoList.size() - 1) {
                            acceptedchg = true;
                            cargoList[changecar].setID(newedit);//insert new id into vector
                            cout << "Cargo ID " << id << " has been changed to " << newedit << ".\n";
                            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                            cargoList[changecar].showCargo();//prints the new cargo id and the rest of the info
                            cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                            newupdate = true;
                        }
                    }

                }
            }
            break;

        case 2:
            cout << "Enter NEW Cargo's destination:\n";
            cin >> newedit;
            while (acceptedchg == false && newedit != "-1") {
                if (newedit == "London" || newedit == "Paris") {//checks if input is ONLY London and Paris
                    cargoList[changecar].setDestination(newedit);//insert new dest into vector
                    cout << "Cargo's destination has been changed to " << newedit << ".\n";
                    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    cargoList[changecar].showCargo();//prints the new cargo dest and the rest of the info
                    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                    acceptedchg = true;
                    newupdate = true;
                }
                else {
                    cout << "Choose only London or Paris!\nEnter NEW Cargo's destination:\n";//prints error statement 
                    cin >> newedit;
                }
            }
            break;

        case 3:
            cout << "Enter NEW Cargo's arrival time in 24hours format:\n";
            cin >> newedit;
            while (acceptedchg == false && newedit != "-1") {
                for (int i = 0; i < newedit.size(); i++) {
                    if (isdigit(newedit[i]) == false || newedit.size() != 4) {//check if input exceeds 4 digit 
                        cout << "Wrong format, please input a 4 digit number in 24hrs format.\nEnter Cargo arrival time in international time, eg. 0900 : ";//error statement
                        cin >> newedit;
                    }
                    else {
                        acceptedchg = true;
                        cargoList[changecar].setTime(stoi(newedit));
                        cout << "Cargo's arrival time has been changed to " << newedit << ".\n";
                        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                        cargoList[changecar].showCargo();
                        cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                        newupdate = true;
                    }
                }

            }
            break;
        default:
            break;
        }

    }
}

void Cargo::addCargo(vector<Cargo>& cargoList, bool& newupdate) {
    Cargo tmpCar("C01", "London", 0754);
    string id, dest, arr;
    bool accept = false;


    cout << "Enter Cargo ID, eg. C01 : " << endl;
    cin >> id;
    while (accept == false && id != "-1") {//checks whether bool accept is still false and id is not equals to -1 
        if (id[0] != 'C') {//check if user input enters C for cargo instead of F for freight
            cout << "Cargo ID is in wrong format, E.g of a Cargo ID, C01.\nEnter NEW Cargo ID:\n";
            cin >> id;
        }
        else {
            for (int i = 0; i < cargoList.size(); i++) {
                if (cargoList[i].getID() == id) {//checks through the vector list if id already exists
                    cout << "Cargo ID already exist, Enter a NEW Cargo ID:\n";//error statement
                    cin >> id;
                    break;
                }
                else if (i == cargoList.size() - 1) {
                    accept = true;//breaks out of the while loop
                }
            }
        }
    }
    accept = false;
    cout << "Enter cargo destination in string : " << endl;//prompts user to enter dest
    cin >> dest;//stores dest in string dest
    while (accept == false && dest != "-1") {
        if (dest == "London" || dest == "Paris") {//checks if input is either London or Paris
            accept = true;//breaks out of the while loop
        }
        else {
            cout << "Choose only London or Paris:\nEnter Cargo's destination in string (London or Paris) : \n";//error statement
            cin >> dest;
        }
    }
    accept = false;
    cout << "Enter cargo arrival time in international time, eg. 0900 : " << endl;//prompts user to enter arr time
    cin >> arr;//store in string arr
    while (accept == false && arr != "-1") {
        for (int i = 0; i < arr.size(); i++) {
            if (isdigit(arr[i]) == false || arr.size() != 4) {//checks if user enter the time correctly
                cout << "Wrong format, please input a 4 digit number in 24hrs format.\nEnter Cargo arrival time in international time, eg. 0900 : ";
                cin >> arr;
            }
            else {
                accept = true;
            }
        }
    }
    accept = false;

    tmpCar.setID(id);
    tmpCar.setDestination(dest);
    tmpCar.setTime(stoi(arr));

    cargoList.push_back(tmpCar);

    cout << "Successfully added Cargo!" << endl;
    cout << "----------------------------------------\n";
    tmpCar.showCargo();
    cout << "\n----------------------------------------\n";
    newupdate = true;
}

ostream& operator<<(std::ostream& out, Cargo& frt) {
    out << frt.getID() << "," << frt.getDestination() << "," << frt.getTime();
    return out;
}
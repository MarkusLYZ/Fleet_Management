#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool Menu::endProg = false;
string defMsg = "Default file will be used.";
string errorFile = "User defined file encoutered a problem, Defualt file will be used.";


inline bool exists_test(const string& name) {  // Checks whether file exist 
    ifstream f(name);
    return f.good();
}

void Menu::openingMain() {
    string header = "TLM1008 - OOP Project";
    string header2 = "International Freight-Cargo Scheduling System";
    string members = "Group members: Harron, Ryan, Aaron, Arshad, Yun zhi";
    
    // creates box with *
    for (int i = 0; i < 80; i++) {
        cout << "*";
    }
    cout << endl;
    for (int i = 0; i < 8; i++) {
        cout << "*";
        for (int j = 0; j < 78; j++) {
            if (i == 1 && j == (78 - header.length()) / 2) {
                cout << header;
                j = (76 + header.length()) / 2;
            }
            else if (i == 2 && j == (78 - header2.length()) / 2) {
                cout << header2;
                j = (76 + header2.length()) / 2;
            }
            else if (i == 6 && j == (78 - members.length()) / 2) {
                cout << members;
                j = (76 + members.length()) / 2;
            }
            else
                cout << " ";
        }
        cout << "*\n";
    }
    for (int i = 0; i < 80; i++) {
        cout << "*";
    }
    cout << endl;
}

void Menu::setFrtfile(string& frtfile) {
    cout << "\n\nPlease enter input file path name for available freight (press Enter for default):\n";
    getline(cin, frtfile);
    if (frtfile == "") {
        throw(defMsg);
    }
    else if (frtfile[frtfile.length() - 1] == 't' && frtfile[frtfile.length() - 2] == 'x' && frtfile[frtfile.length() - 3] == 't' && frtfile[frtfile.length() - 4] == '.') {
        if (exists_test(frtfile) == false) {
            throw(errorFile);
        }
    }
    else {
        throw(errorFile);
    }
}

void Menu::setCgofile(string& crgofile) {
    cout << "\nPlease enter input folder path name for available cargo (press Enter for default):\n";
    getline(cin, crgofile);
    if (crgofile == "") {
        throw(defMsg);
    }
    else if (crgofile[crgofile.length() - 1] == 't' && crgofile[crgofile.length() - 2] == 'x' && crgofile[crgofile.length() - 3] == 't' && crgofile[crgofile.length() - 4] == '.') { // Checks whether file has .txt as extenstion 
        if (exists_test(crgofile) == false) {
            throw(errorFile);
        }
    }
    else {
        crgofile = "freight.txt";
        throw(errorFile);
    }
}


void Menu::displayMain() {
    system("CLS");
    std::cout << "MAIN MENU:\n"
        << "1. Display all freight\n"
        << "2. Display all cargo\n"
        << "3. Schedule cargo by cargo arrival time\n"
        << "4. Schedule cargo by minimum freight\n"
        << "5. Display freight that is under capacity\n"
        << "6. Display remaining cargo\n"
        << "7. Display scheduling plan\n"
        << "8. Save scheduling plan\n"
        << "9. Add/Delete/Edit freight\n"
        << "10. Add/Delete/Edit cargo\n"
        << "\nKey -1 to End Program\n"
        << "Please enter your option:\n";
}

void Menu::setOption() {
    cin >> option;
    while (isdigit(option[0]) == false) { // checks whether option is in digit 
        if (option[0] != '-') {
            cout << "Invaid input, please try agian.\nPlease enter your option:\n>";
        }
        else if (option[0] == '-' && option[1] == '1') {
            endProg = true;
            break;
        }
        cin.ignore();
        cin >> option;
    }
}

string Menu::getOption() {
    return option;
}

bool Menu::checkendProg() {
    return endProg;
}

void Menu::displaySubMenu(string x) {
    system("CLS");
    cout << "ADD / DELETE / EDIT " << x << ":\n";
    cout << "1. Add\n";
    cout << "2. Delete\n";
    cout << "3. Edit\n";
    cout << "4. Back to Main Menu\n";
    cout << "Key -1 to End Program\n\n";
    cout << "Please enter your option:\n>";
}

void Menu::displaySubMenu2(string x) {
    system("CLS");
    cout << "ADD / DELETE / EDIT " << x << ":\n";
    cout << "1. Add\n";
    cout << "2. Delete\n";
    cout << "3. Edit\n";
    cout << "4. Back to Main Menu\n";
    cout << "Key -1 to End Program\n\n";
    cout << "Please enter your option:\n>";
}

void Menu::resetOpt() {
    option = "0";
}

void Menu::displaySaveMenu() {
    cout << "1. Save Schedule By Minimum Freight" << endl;
    cout << "2. Save Scehdule By Cargo Arrival Time" << endl;
    cout << "3. Return to previous Menu\n";
    cout << "\nKey -1 to End Program\n";
    cout << "Please Enter Your Option \n>";
}


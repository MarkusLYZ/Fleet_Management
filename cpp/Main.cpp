#include <sstream>
#include <algorithm>
#include "Freight.h"
#include "Cargo.h"
#include "Schedule.h"
#include <vector>
#include "Menu.h"

using namespace std;

string frtfile, cargofile;
void getCargoData(vector<Cargo>& cargo);
void getFrtData(vector<Freight>& flist);
bool compFreightDestMaxCap(Freight f1, Freight f2);
bool compCargoDestTime(Cargo c1, Cargo c2);
bool compTime(int ftime, int ctime);
bool compFreightDestTime(Freight f1, Freight f2);
void schByMinFreight(vector<Schedule>& slist, vector<Freight>& flist, vector<Cargo>& clist, vector<Freight> orifrtlist, vector<Cargo> oricgolist);
void schByCargoTime(vector<Schedule>& slist, vector<Freight>& flist, vector<Cargo>& clist, vector<Freight> oriFlist, vector<Cargo> oriClist);
void saveSchPlan(vector<Schedule>& slistbyminfrt, vector<Schedule>& slistbycgotime, vector<Freight>& flist, vector<Cargo>& clist, Menu menu);
void saveFreight(vector<Freight>& freightList, bool& dataChanged, Menu opt);
void saveCargo(vector<Cargo>& cList, bool& dataChanged, Menu opt);


int main() {
    vector<Cargo> cargoList, remainingCgoByMinFrt, remainingCgoByCgoTime;
    vector<Freight> freightList, remainingFrtByMinFrt, remainingFrtByCgoTime;
    vector<Schedule> schListByMinFrt, schListByCargotime;
    Menu main, freightMenu, cargoMenu, savingMenu, saveMenu;
    bool dataChanged = false;

    // Start of program, shows starting page
    main.openingMain();
    
    // File name/path input by user
    try {
        main.setFrtfile(frtfile);
        cout << "User defined file has been set.\n";
    }
    catch (string msg) {
        frtfile = "freight.txt";
        cout << msg << endl;
    }

    try {
        main.setCgofile(cargofile);
        cout << "User defined file has been set.\n";
    }
    catch (string msg) {
        cargofile = "cargo.txt";
        cout << msg << endl;
    }
    cout << "\nPlease enter any key to continue:\n>";
    cin.get();

    // Create vector list for Freight and Cargo
    getCargoData(cargoList);
    getFrtData(freightList);

    // Main page
    main.displayMain();
    main.setOption();

    while (main.checkendProg() == false) {
        switch (stoi(main.getOption())) {
        case 1: // DISPLAY ALL FREIGHT                      
        {   
            system("CLS");
            cout << "DISPLAY ALL FREIGHT:\n\n"
                << "Freights:\n"
                << "---------------------------------------------------------------------------------------------\n";
            for (auto &v : freightList) {
                v.showFreight();
                cout << endl;
            }
            cout << "\nPlease enter any key to return to main menu:\n>";
            cin.ignore();
            cin.get();
            break;
        }
        case 2: // DISPLAY ALL CARGO                        
        {
            system("CLS");
            cout << "DISPLAY ALL CARGO:\n"
                << "Cargo:\n"
                << "---------------------------------------------------------------------------------------------\n";
            for (auto& v : cargoList) {
                v.showCargo();
                cout << endl;
            }
            cout << "\n\nPlease enter any key to return to main menu:\n>";
            cin.ignore();
            cin.get();
            break;
        }
        case 3: // Schedule cargo by cargo arrival time     
        {   
            system("CLS");
            if (schListByCargotime.size() > 1) {
                schListByCargotime.clear();
            }
            cout << "DISPLAY SCHEDULING PLAN:\n\n"
                << "Scheduling by Cargo Arrival Time\n"
                << " **** New Schedule Plan using Cargo Arrival Time  **** " << endl
                << "---------------------------------------------------------------------------------------------\n";
            schByCargoTime(schListByCargotime, remainingFrtByCgoTime, remainingCgoByCgoTime, freightList, cargoList);
            for (auto& v : schListByCargotime) {
                v.showInfo();
            }
            cout << "---------------------------------------------------------------------------------------------\n";
            cout << "\nPlease enter any key to return to main menu:\n>";
            cin.ignore();
            cin.get();
            break;
        }
        case 4: // Schedule cargo by minimum freight       
        {   
            if (schListByMinFrt.size() > 1) {
                schListByMinFrt.clear();
            }
            system("CLS");
            cout << "DISPLAY SCHEDULING PLAN:\n\n"
                << "Scheduling by Minimum Freight\n"
                << " **** New Schedule Plan using Minimum Freight  **** " << endl
                << "---------------------------------------------------------------------------------------------\n";
            schByMinFreight(schListByMinFrt, remainingFrtByMinFrt, remainingCgoByMinFrt, freightList, cargoList);
            for (auto& v : schListByMinFrt) {
                v.showInfo();
            }
            cout << "---------------------------------------------------------------------------------------------\n";
            cout << "Please enter any key to return to main menu:\n>";
            cin.ignore();
            cin.get();
            break;
        }
        case 5: // Display freight that is under capacity   
        {
            system("CLS");
            cout << " ********  Freight under capacity after scheduling plan by Cargo Arrival Time  ******** " << endl;
            if (schListByCargotime.size() == 0) {
                cout << "Scheduling plan by Cargo arrival time have not been executed.\n";
            }
            else {
                for (auto& v : remainingFrtByCgoTime) {
                    v.showFreight();
                    cout << endl;
                }
            }
            cout << "\n\n ********  Freight under capacity after scheduling plan by Minimum Freight  ******** " << endl;
            if (schListByMinFrt.size() == 0) {
                cout << "Scheduling plan by Minimum Freight have not been executed.\n";
            }
            else {
                for (auto& v : remainingFrtByMinFrt) {
                    v.showFreight();
                    cout << endl;
                }
            }
            cout << "\nPlease enter any key to return to main menu:\n>";
            cin.ignore();
            cin.get();
            break;
        }
        case 6: // Display remaining cargo                  
        {
            system("CLS");
            cout << " ******** Remaining Cargo after scheduling plan by Cargo Arrival Time  ******** " << endl;
            if (schListByCargotime.size() == 0) {
                cout << "Scheduling plan by Cargo arrival time have not been executed.\n";
            }
            else {
                for (auto& v : remainingCgoByCgoTime) {
                    v.showCargo();
                    cout << endl;
                }
            }

            cout << "\n\n ********  Remaining Cargo after scheduling plan by Minimum Freight  ******** " << endl;
            if (schListByMinFrt.size() == 0) {
                cout << "Scheduling plan by Minimum Freight have not been executed.\n";
            }
            else {
                for (auto& v : remainingCgoByMinFrt) {
                    v.showCargo();
                    cout << endl;
                }
            }
            cout << "Please enter any key to return to main menu:\n>";
            cin.ignore();
            cin.get();
            break;
        }
        case 7: // Display scheduling plan                 
        {
            system("CLS");
            cout << " **** Schedule Plan using Cargo Arrival Time  **** " << endl
                << "---------------------------------------------------------------------------------------------\n";
            if (schListByCargotime.size() == 0) {
                cout << "Scheduling plan by Cargo arrival time has not been executed.\n";
            }
            else {
                for (auto& v : schListByCargotime) {
                    v.showInfo();
                }
            }
            cout << "---------------------------------------------------------------------------------------------\n";
            cout << "\n\n ********  Schedule Plan using Minimum Freight  ******** " << endl;
            cout << "---------------------------------------------------------------------------------------------\n";
            if (schListByMinFrt.size() == 0) {
                cout << "Scheduling plan by Minimum Freight has not been executed.\n";
            }
            else {
                for (auto& v : schListByMinFrt) {
                    v.showInfo();
                }
            }
            cout << "---------------------------------------------------------------------------------------------\n";
            cout << "\n\nPlease enter any key to return to main menu:\n>";
            cin.ignore();
            cin.get();
            break;
        }
        case 8: // Save scheduling plan                     
        {   

            saveSchPlan(schListByMinFrt, schListByCargotime, freightList, cargoList, savingMenu);
            break;
        }
        case 9: // Add/Delete/Edit freight                
        {
            freightMenu.displaySubMenu("FREIGHT");
            freightMenu.setOption();
            while (stoi(freightMenu.getOption()) != 4 && freightMenu.checkendProg() == false) {
                switch (stoi(freightMenu.getOption())) {
                case 1:
                    Freight::addFreight(freightList, dataChanged);
                    if (dataChanged == true) {
                        saveFreight(freightList, dataChanged, saveMenu);
                    }
                    cout << "\n\nPlease enter any key to return to main menu:\n>";
                    cin.ignore();
                    cin.get();
                    break;
                case 2:
                    Freight::deleteFreight(freightList, dataChanged);
                    if (dataChanged == true) {
                        saveFreight(freightList, dataChanged, saveMenu);
                    }
                    cout << "\n\nPlease enter any key to return to main menu:\n>";
                    cin.ignore();
                    cin.get();
                    break;
                case 3:
                    Freight::editFreight(freightList, dataChanged);
                    if (dataChanged == true) {
                        saveFreight(freightList, dataChanged, saveMenu);
                    }
                    cout << "\n\nPlease enter any key to return to main menu:\n>";
                    cin.ignore();
                    cin.get();
                    break;
                default:
                    break;
                }
                
                freightMenu.displaySubMenu("FREIGHT");
                freightMenu.setOption();
            }
            break;
        }
        case 10: // Add/Delete/Edit cargo                   ***DONE***
        {
            cargoMenu.displaySubMenu("CARGO");
            cargoMenu.setOption();
            while (stoi(cargoMenu.getOption()) != 4 && cargoMenu.checkendProg() == false) {
                switch (stoi(cargoMenu.getOption())) {
                case 1:
                    system("CLS");
                    Cargo::addCargo(cargoList, dataChanged);
                    if (dataChanged == true) {
                        saveCargo(cargoList, dataChanged, saveMenu);
                    }
                    cout << "\n\nPlease enter any key to return to main menu:\n>";
                    cin.ignore();
                    cin.get();
                    break;
                case 2:
                    system("CLS");
                    Cargo::deleteCargo(cargoList, dataChanged);
                    if (dataChanged == true) {
                        saveCargo(cargoList, dataChanged, saveMenu);
                    }
                    cout << "\n\nPlease enter any key to return to main menu:\n>";
                    cin.ignore();
                    cin.get();
                    break;
                case 3:
                    Cargo::editCargo(cargoList, dataChanged);
                    if (dataChanged == true) {
                        saveCargo(cargoList, dataChanged, saveMenu);
                    }
                    cout << "\n\nPlease enter any key to return to main menu:\n>";
                    cin.ignore();
                    cin.get();
                    break;
                default:
                    break;
                }
                cargoMenu.displaySubMenu("CARGO");
                cargoMenu.setOption();
            }
            break;
        }
        default:
            cout << "Invaid input, please try agian.\n Please enter your option:\n>";
            break;
        }

        if (main.checkendProg() == true) { break; }
        else {
            main.displayMain();
            main.setOption();
        }
    }

    // Clearing of all vectors 
    cargoList.clear();
    remainingCgoByMinFrt.clear();
    freightList.clear();
    remainingFrtByMinFrt.clear();
    schListByMinFrt.clear();
    schListByCargotime.clear();
    remainingCgoByCgoTime.clear();
    remainingFrtByCgoTime.clear();
    return 0;
}


// Read from Cargo file and create vector list 
void getCargoData(vector<Cargo>& cargo) {
    Cargo tmpCar("C1", "London", 0745);
    ifstream inFile;
    string row[3];
    string line, word;
    inFile.open(cargofile);
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream s(line);
            int i = 0;
            while (getline(s, word, ',')) {
                row[i] = word;
                i++;
            }
            tmpCar.setID(row[0]);
            tmpCar.setDestination(row[1]);
            tmpCar.setTime(stoi(row[2]));
            cargo.push_back(tmpCar);
        }
    }
    else {
        cout << "Unable to open file! ";
    }
}
// Read from freight file and create vector list 
void getFrtData(vector<Freight>& flist) {

    Freight tmpFreight;				//temporary class buffer
    ifstream inFile;				//Input file pointer
    string row[4];					//array of string
    string line, word;

    //Read file - Using text file with 1 whitespace
    inFile.open(frtfile);

    if (inFile.is_open()) {
        while (getline(inFile, line)) {			//check if end of file, and store into line
            stringstream s(line);				//break line up and store into stringstream s
            int i = 0;
            while (getline(s, word, ',')) {		//check each stringstream s, and store into word, avoid blank
                row[i] = word;					//backup word into array of row
                i++;
            }

            tmpFreight.setID(row[0]);					//store Freight ID
            tmpFreight.setCapacity(stoi(row[1]));		//convert string to integer and store Capacity
            tmpFreight.setDestination(row[2]);			//store Destination
            tmpFreight.setTime(stoi(row[3]));			//convert string to integer and store
            flist.push_back(tmpFreight);				//save temp buffer into vector list
        }
    }

    inFile.close();
}




// Compare Freight's destination and then capacity
bool compFreightDestMaxCap(Freight f1, Freight f2) {

    if (f1.getDestination() != f2.getDestination())
        return (f1.getDestination() < f2.getDestination());
    return (f1.getCapacity() > f2.getCapacity());
}

// Compare Cargo's destination and then compare time
bool compCargoDestTime(Cargo c1, Cargo c2) {
    if (c1.getDestination() != c2.getDestination())
        return (c1.getDestination() < c2.getDestination());
    return (c1.getTime() < c2.getTime());
}

// compare freight time and cargo time 
// Freight time can be earlier than cargo time - max gap 30mins
bool compTime(int ftime, int ctime) {
    bool status = false;
    int totalMinutes = 0;

    int f_hr = ftime / 100;		//get hour
    int f_min = ftime % 100;	//get min

    int c_hr = ctime / 100;		//get hour
    int c_min = ctime % 100;	//get min

    // Difference Between Times IN minutes
    if (c_hr >= f_hr) {													//look for earlier freight! Find gap in minutes
        totalMinutes = ((c_hr * 60) + c_min) - ((f_hr * 60) + f_min);	//Total = cTime - fTime

        if ((totalMinutes >= 0) && (totalMinutes <= 30)) {				//check grace time range only 0 to 30
            status = true;
        }
    }

    return status;
}

// Compare Freight's destination and then compare time
bool compFreightDestTime(Freight f1, Freight f2) {
    if (f1.getDestination() != f2.getDestination())
        return (f1.getDestination() < f2.getDestination());
    return (f1.getTime() < f2.getTime());
}




// Schedule by minimum freight
void schByMinFreight(vector<Schedule>& slist, vector<Freight>& flist, vector<Cargo>& clist, vector<Freight> orifrtlist , vector<Cargo> oricgolist) {
    int sid = 1;
    size_t i = 0, j = 0;

    flist = orifrtlist;
    clist = oricgolist;

    sort(flist.begin(), flist.end(), compFreightDestMaxCap);				// sort Freight, same destination, Ascending capacity
    sort(clist.begin(), clist.end(), compCargoDestTime);					// sort Cargo, same destination, Ascending time

    while (i < flist.size()) {											// Loop Freight
        j = 0;																// reset back to beginning
        while (j < clist.size()) {											// Loop Cargo
            int ftime = flist[i].getTime();
            int ctime = clist[j].getTime();
            if ((flist[i].getDestination() == clist[j].getDestination()) &&	// Destination matched,
                (compTime(ftime, ctime) == true) &&							// Within Grace period, 
                (flist[i].getCapacity() > 0)) 								// Within Freight Capacity
            {
                Schedule tmpSch(sid, flist[i], clist[j]);					// store tmp object data, call Schedule constructor			
                slist.push_back(tmpSch);									// save into schedule list
                sid++;
                flist[i].decCapacity();										// directlt decrement capacity
                clist.erase(clist.begin() + j);								// erase cargo element by index
                // cannot increase j counter, 
                // stay in the same position to do next check
            }
            else
                j++;														// go for next cargo element					
        }

        if (flist[i].getCapacity() == 0) {									// check capacity reached zero
            cout << "Freight: " << flist[i].getID() << " Capacity Full!" << endl;;
            flist.erase(flist.begin() + i);									// erase freight element by index
            // cannot increase i counter, 
            // stay in the same position to do next check
        }
        else
            i++;															// go for the next freight element
    }
}

// Schedule by cargo arrival time
void schByCargoTime(vector<Schedule>& slist, vector<Freight>& flist, vector<Cargo>& clist, vector<Freight> oriFlist, vector<Cargo> oriClist)
{
    flist = oriFlist;
    clist = oriClist;
    int sid = 1;
    size_t i = 0, j = 0;
    sort(flist.begin(), flist.end(), compFreightDestTime);    // sort Freight, same destination, Ascending time
    sort(clist.begin(), clist.end(), compCargoDestTime);     // sort Cargo, same destination, Ascending time
    while (i < flist.size()) {           // Loop Freight
        j = 0;                // reset back to beginning
        while (j < clist.size()) {           // Loop Cargo
            int ftime = flist[i].getTime();
            int ctime = clist[j].getTime();
            if ((flist[i].getDestination() == clist[j].getDestination()) && // Destination matched,
                (compTime(ftime, ctime) == true) &&       // Within Grace period, 
                (flist[i].getCapacity() > 0))         // Within Freight Capacity
            {
                Schedule tmpSch(sid, flist[i], clist[j]);     // store tmp object data, call Schedule constructor   
                slist.push_back(tmpSch);         // save into schedule list
                sid++;
                flist[i].decCapacity();          // directlt decrement capacity
                clist.erase(clist.begin() + j);        // erase cargo element by index
                // cannot increase j counter, 
                // stay in the same position to do next check
            }
            else
                j++;              // go for next cargo element     
        }
        if (flist[i].getCapacity() == 0) {         // check capacity reached zero
            cout << "Freight: " << flist[i].getID() << " Capacity Full!" << endl;
            flist.erase(flist.begin() + i);         // erase freight element by index
            // cannot increase i counter, 
            // stay in the same position to do next check
        }
        else
            i++;               // go for the next freight element
    }
    //Display Schedule Plan

}




// Save scheduling plan to file 
void saveSchPlan(vector<Schedule>& slistbyminfrt, vector<Schedule>& slistbycgotime, vector<Freight>& flist, vector<Cargo>& clist, Menu menu) {
    string fileName;
    system("cls");
    bool filesaved = false;

    menu.displaySaveMenu(); 
    menu.setOption(); // ask user for input option

    while (stoi(menu.getOption()) != 3 && menu.checkendProg() == false && filesaved == false) {
        switch (stoi(menu.getOption())) {
            case 1: {
                if (slistbyminfrt.size() == 0) {
                    cout << "Scheduling plan by Minimum Freight have not been executed.\n";
                    cout << "\n\nPlease enter any key to return:\n>";
                    cin.ignore();
                    cin.get();
                }
                else {
                    cout << "\nPlease Enter File Name(eg. PlanByMinFreight.txt): ";
                    cin >> fileName; // ask for file name 
                    std::ofstream out_file(fileName); //creates a txt file using the file name entered by the user 
                    for (int i = 0; i < slistbyminfrt.size(); i++) {

                        out_file << slistbyminfrt[i] << endl; //using overloaded operator, ouput each schedule into the target file

                    }
                    out_file.close();
                    filesaved = true;
                }
                break;
            }
            case 2: {
                if (slistbycgotime.size() == 0) { //check if scheduling has been run  
                    cout << "Scheduling plan by Cargo arrival time have not been executed.\n";
                    cout << "\n\nPlease enter any key to return:\n>";
                    cin.ignore();
                    cin.get();
                }
                else {
                    cout << "Please Enter File Name(eg. PlanByCargoTime.txt):";
                    cin >> fileName;
                    std::ofstream out_file(fileName); //creates a txt file using the file name entered by the user  
                    for (int i = 0; i < slistbycgotime.size(); i++) {
                        out_file << slistbycgotime[i] << endl;
                    }
                    out_file.close();
                    filesaved = true;
                }
                break;
            }
            default: { //removes possible errors
                cout << "\nInvalid options! Please try again!" << endl;
                cout << "Please Enter Your Option \n>";
                menu.setOption();
                break;
            }
        }
        if (filesaved == true) { //prompts user that file has been saved if process run without error
            cout << "File is successfully created.";
            cout << "\n\nPlease enter any key to return to main menu:\n>";
            cin.ignore();
            cin.get();
            break;
        }

        system("CLS");
        menu.displaySaveMenu();
        menu.setOption();
    }
    //Ask User to return to Main Menu
   
}

// Save freight vector list to freight file
void saveFreight(vector<Freight>& freightList, bool& dataChanged, Menu opt) {
    cout << "Frieght list was previously changed, would you like to the save changes to file? (Press 1 to save, any other number to return)\n>";
    opt.setOption();
    if (opt.getOption() == "1") {
        ofstream out_freight(frtfile); 
        for (int i = 0; i < freightList.size(); i++) { 
            out_freight << freightList[i] << endl; // writing data into file
        }
        out_freight.close();

        cout << "File: " << frtfile << " has been updated.";
        dataChanged = false;
    }
    opt.resetOpt();
}

// Save cargo vector list to cargo file 
void saveCargo(vector<Cargo>& cList, bool& dataChanged, Menu opt) {
    if (dataChanged == true) {
        cout << "Cargo list was previously changed, would you like to save changes to file? (Press 1 to save, any other number to return)\n>";
        opt.setOption();
        if (opt.getOption() == "1") {
            std::ofstream outfile(cargofile);
            for (int i = 0; i < cList.size(); i++) {
                outfile << cList[i] << endl; // writing data into file
            }
            outfile.close();

            cout << "File: " << cargofile << " has been updated.";
            dataChanged = false;
        }
    }
    opt.resetOpt();
} 

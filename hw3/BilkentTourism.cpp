/*
CS 201: Fundamental Structures of Computer Science I
Fall 2025
Homework Assignment 3
Student Name: Sıla Bozkurt
Student ID: 22401775
Section: 3
Instructor: Ercüment Çiçek
Assistants: Mehmet Alper Yılmaz
Submission Date: 12.12.2025
*/
#include "BilkentTourism.h"
#include "BusLine.h"
#include "Bus.h" 
#include <iostream>

using namespace std;

/*
This is the default constructor for the system. Since the member variables (busLines, stops, buses) 
are LinkedList objects, they are automatically initialized by their own constructors when a BilkentTourism 
object is created. Therefore, this constructor is left empty as no additional manual initialization is required.
*/
BilkentTourism::BilkentTourism()
{

}

/*
This is the destructor for the system. It is responsible for cleaning up resources when the BilkentTourism object 
goes out of scope. Because the LinkedList class handles its own memory management (deleting nodes in its own destructor), 
this destructor does not need to manually delete the lists, so it remains empty.
*/
BilkentTourism::~BilkentTourism()
{

}


/*
This method is responsible for adding a new bus line to the system. It first iterates through the busLines linked list 
to ensure that no line with the provided lineId already exists. If a duplicate ID is found, it prints an error message and returns. 
If the ID is unique, it creates a new BusLine object and uses the insertSorted method to add it to the list, 
ensuring the lines remain ordered by their ID.
*/
void BilkentTourism:: addBusLine(const int lineId, const string& lineName){
    //check if any line with such a Id exists
    bool found = false;
        if(busLines.getSize() == 0){
            found = false;
        }
        for(int i = 0; i < busLines.getSize(); i++){
            if(busLines.get(i).getId() == lineId){
                found = true;
                break;
            }
        }

    if (found){
        cout<<"Cannot add line. There is already a bus line with ID "<< lineId<< "."<<endl;
        return;
    }
    BusLine busLine(lineId, lineName);
    busLines.insertSorted(busLine);
    cout<<"Added bus line "<<lineId<<"."<<endl;
}


/*
This method removes a specific bus line from the system based on its ID. It searches the busLines linked list for a line matching 
the lineId. If found, it removes the line at that specific index using the remove method and prints a success message. 
If the loop finishes without finding the ID, it informs the user that the bus line does not exist.
*/
void BilkentTourism:: removeBusLine(const int lineId) {
    bool found = false; 
    int lineIndex;
    if (busLines.getSize() == 0) {
        found = false;
    }
    for (int i = 0; i < busLines.getSize(); i++) {
        if (busLines.get(i).getId() == lineId) {
            found = true;
            lineIndex = i;
            busLines.remove(lineIndex);
            cout << "Removed bus line " << lineId << "." << endl; 
            // also remove the busses from this line
            for (int j = 0; j < buses.getSize(); j++) {
                for (int k = 0; k < busLines.get(i).lineBuses.getSize(); k++) {
                    if (buses.get(j).getID() == busLines.get(i).lineBuses.get(k).getID()) {
                        buses.remove(j);
                        j--;
                        break;
                    }
                }
            }
            return;
        }
    }
    if (!found) {
        cout << "Cannot remove bus line. There is no bus line with ID " << lineId << "." << endl;
    }

}


/*
This method displays all the bus lines currently registered in the system. It first checks if the busLines list is empty; 
if so, it prints a message stating there are no lines to show. Otherwise, it iterates through the list and uses the 
overloaded output operator (<<) of the BusLine class to print the details of each line.
*/
void BilkentTourism:: printBusLines() const{
    if(busLines.getSize() == 0){
        cout<<"There are no bus lines to show."<<endl;
        return;
    }
    cout<<"Bus lines in the system:"<<endl;
    for(int i = 0; i < busLines.getSize(); i++){
        cout<< busLines.get(i) <<endl;
    }
}


/*
This method adds a new stop to the global pool of stops. It first checks the stops linked list to prevent adding a 
stop with a duplicate stopId. If the ID is unique, it creates a new Stop object and inserts it into the global stops 
list using insertSorted to keep the list organized.
*/
void BilkentTourism:: addStop(const int stopId, const string& stopName){
    for(int i = 0; i < stops.getSize(); i++){
        if(stops.get(i).stopId == stopId){
            cout<<"Cannot add stop. BilkentTourism already contains stop "<< stopId<< "."<<endl;
            return;
        }
    }
    Stop stop(stopId, stopName);
    stops.insertSorted(stop);
    cout<<"Added stop "<<stopId<<"."<<endl;
}


/*
This method handles the removal of a stop from the global system, but with strict validation. First, it verifies 
that the stop actually exists in the global stops list. Second, it iterates through every BusLine to ensure the stop 
is not currently part of any active route. If the stop is found in any line's lineStops list, the removal is blocked 
to prevent breaking routes. If the stop exists and is unused, it is removed from the global list.
*/
void BilkentTourism:: removeStop(const int stopId){
    // First check if the stop exists
    bool stopExists = false;
    for(int i = 0; i < stops.getSize(); i++){
        if(stops.get(i).getId() == stopId){
            stopExists = true;
            break;
        }
    }
    
    if(!stopExists){
        cout<< "Cannot remove stop " << stopId << ". There is no bus stop with ID "<< stopId <<"."<<endl;
        return;
    }
    
    // Check if the stop is used in any bus line
    for(int i = 0; i < busLines.getSize(); i++){
        for(int j = 0; j < busLines.get(i).lineStops.getSize(); j++){
            if(busLines.get(i).lineStops.get(j).getId() == stopId){
                cout<< "Cannot remove stop " << stopId << ". The stop is currently in use."<<endl;
                return;
            }
        }
    }
    
    // Remove the stop if it exists and is not in use
    for(int i = 0; i < stops.getSize(); i++){
        if(stops.get(i).getId() == stopId){
            stops.remove(i);
            cout<<"Removed stop "<<stopId<<"."<<endl;
            return;
        }
    }
}


/*
This method adds an existing global stop to a specific bus line. It validates two conditions: the stopId must exist 
in the global stops list, and the lineId must correspond to an existing bus line. It also checks if the line 
already contains that specific stop to avoid duplicates. If all validations pass, the stop is retrieved from the 
global list and inserted into the specific BusLine's lineStops list using insertSorted.
*/
void BilkentTourism:: addStopToLine(const int stopId, const int lineId){
    bool stopFound = false;
    bool lineFound = false;
    for(int i = 0; i < stops.getSize(); i++){
        if(stops.get(i).getId() == stopId){
            stopFound = true;
            break;
        }
    }
    if(!stopFound){
        cout<< "Cannot add stop. There is no stop with ID "<<stopId<<"."<<endl;
        return;
    }
    
    for(int j = 0; j < busLines.getSize(); j++){
        if(busLines.get(j).getId() == lineId){
            lineFound = true;
            BusLine& line = busLines.get(j);
            //check if the stop is already in the line
            for(int k = 0; k < busLines.get(j).lineStops.getSize(); k++){
                if(busLines.get(j).lineStops.get(k).getId() == stopId){
                    cout<<"Cannot add stop. Line "<<lineId<<" already contains stop "<<stopId<<"."<<endl;
                    return;
                }
            }
            //add the stop to the line
            for(int m = 0; m < stops.getSize(); m++){
                if(stops.get(m).getId() == stopId){
                    busLines.get(j).lineStops.insertSorted(stops.get(m));
                    cout<<"Added stop "<<stopId<<" to line "<<lineId<<" ("<<line.getLineName()<<")."<<endl;
                    return;
                }
            }
        }
    } 
    if(!lineFound){
        cout<<"Cannot add stop. There is no line with ID "<<lineId<<"."<<endl;
    } 
}


/*
This method removes a stop from a specific bus line's route. It first checks if the stopId exists globally. 
Then, it searches for the specified BusLine. If the line is found, it searches that line's internal lineStops 
list for the stop. If the stop is present in the line, it is removed; otherwise, error messages are printed 
indicating either the line does not exist or the stop was not part of that line.
*/
void BilkentTourism::removeStopFromLine(const int stopId, const int lineId){
    bool stopFound = false;
    for(int i = 0; i < stops.getSize(); i++){
        if(stops.get(i).getId() == stopId){
            stopFound = true;
            break;
        }
    }
    if(!stopFound){
        cout<< "Cannot add stop. There is no stop with ID "<<stopId<<"."<<endl;
        return;
    }
    for (int i = 0; i < busLines.getSize(); i++){
        if(busLines.get(i).getId() == lineId){
            for(int j = 0; j < busLines.get(i).lineStops.getSize(); j++){
                if(busLines.get(i).lineStops.get(j).getId() == stopId){
                    busLines.get(i).lineStops.remove(j);
                    cout<<"Removed stop "<<stopId<<" from line "<<lineId<<"."<<endl;
                    return;
                }
            }
            cout<<"Cannot remove stop. Line "<<lineId<<" does not have stop "<<stopId<<"."<<endl;
            return;
        }
    }
    cout << "Cannot remove stop. There is no line with ID " << lineId << "." << endl;
}


/*
This method lists all the stops assigned to a specific bus line. It searches for the line matching lineId. 
If found, it checks if the line has any stops. If stops exist, it iterates through the line's lineStops list 
and prints them. If the line is not found or has no stops, appropriate error messages are displayed.
*/
void BilkentTourism:: printStops(const int lineId) const{
    bool lineFound = false;
    for(int i = 0; i < busLines.getSize(); i++){
        if(busLines.get(i).getId() == lineId){
            lineFound = true;
            if(busLines.get(i).lineStops.getSize() == 0){
                cout<<"Cannot print stops. There is no stop to show."<<endl;
                return;
            }
            cout<<"Stops in bus line "<<busLines.get(i).getId()<<" ("<<busLines.get(i).getLineName() << ") :"<<endl;
            for(int j = 0; j < busLines.get(i).lineStops.getSize(); j++){
                cout<< busLines.get(i).lineStops.get(j) <<endl;
            }
            return;
        }
    }
    if(!lineFound){
        cout<<"Cannot print stops. There is no line with ID "<<lineId<<"."<<endl;
    }
}


/*
This method assigns a bus and driver to a specific route. It performs comprehensive checks: it ensures the target 
line exists, the bus ID is not already assigned to that specific line, and the bus ID is not currently assigned to 
any other line in the system. If the bus is available and the line exists, a new Bus object is created and added 
to both the BusLine's internal lineBuses list and the global buses list.
*/
void BilkentTourism::assignBus(const int busId, const string& driverName, const int lineId) {
    // Create a new bus object
    Bus newBus(busId, driverName);
    
    // Find the bus line
    for (int i = 0; i < busLines.getSize(); i++) {
        if (busLines.get(i).getId() == lineId) {
            BusLine& line = busLines.get(i);
            // Check if the bus ID already exists in the line
            for (int j = 0; j < busLines.get(i).lineBuses.getSize(); j++) {
                if (busLines.get(i).lineBuses.get(j).getID() == busId) {
                    cout << "Cannot assign bus. Bus " << busId << " is already assigned to line " << lineId << "." << endl;
                    return; // Exit if duplicate bus ID is found
                }
            }

            // Check if bus is already assigned to any line
            for(int k = 0; k < busLines.getSize(); k++){
                for(int j = 0; j < busLines.get(k).lineBuses.getSize(); j++){
                    if(busLines.get(k).lineBuses.get(j).getID() == busId){
                        cout << "Cannot assign bus. Bus " << busId << " is already assigned to a line." << endl;
                        return;
                    }
                }
            }

            // Add the new bus to the line
            busLines.get(i).lineBuses.insertSorted(newBus);
            buses.insertSorted(newBus);
            cout << "Bus " << busId << " with driver "<< newBus.getDriver()<<" is assigned to line " << lineId <<" (" << line.getLineName()<< ")." << endl;
            return;
        }
    }

    // If the bus line is not found
    cout << "Cannot assign bus. There is no line with ID " << lineId << "." << endl;
}


/*
This method removes a bus from its assigned line. It first checks if the bus exists in the global buses registry. 
If it does, the method iterates through all BusLine objects to find which line currently contains this bus. Once the correct 
line is found, the bus is removed from that line's lineBuses list and buses of Bilkent Tourism.
*/
void BilkentTourism:: unassignBus(const int busId){
    bool busFound = false;
    for(int i = 0; i < buses.getSize(); i++){
        if(buses.get(i).getID() == busId){
            busFound= true;
            for(int i = 0; i < busLines.getSize(); i++){
                for(int j = 0; j < busLines.get(i).lineBuses.getSize(); j++){
                    if(busLines.get(i).lineBuses.get(j).getID() == busId){
                        busLines.get(i).lineBuses.remove(j);
                        for (int k = 0; k < buses.getSize(); k++){
                            if(buses.get(k).getID() == busId){
                                buses.remove(k);
                                break;
                            }
                        }
                        cout<<"Bus "<<busId<<" is unassigned from line "<<busLines.get(i).getId()<<" ("<<busLines.get(i).getLineName()<<")."<<endl;
                        return;
                    }
                }
            }
        }
    }
    if(!busFound){
        cout<<"Cannot unassign bus. There is no bus with ID "<<busId<<"."<<endl;
    }
}


/*
This method displays all buses currently operating on a specific line. It locates the line by its ID and checks if its 
lineBuses list is empty. If the list is not empty, it prints a header followed by the details of every bus assigned to 
that line. If the line has no buses or does not exist, it outputs the corresponding error message.
*/
void BilkentTourism:: printBussesInLine(const int lineId) const {
    bool foundLine = false;
    for (int i = 0; i < busLines.getSize(); i++) {
        if (busLines.get(i).getId() == lineId) {
            foundLine = true;
            if(busLines.get(i).lineBuses.getSize() == 0){
                cout<< "There are no bus to show in line "<<lineId<<" ("<<busLines.get(i).getLineName()<<")."<<endl;
                return;
            }
            cout << "Busses and their drivers assigned to the line " << lineId << " (" << busLines.get(i).getLineName() << "):" << endl;
            for (int j = 0; j < busLines.get(i).lineBuses.getSize(); j++) {
                cout << busLines.get(i).lineBuses.get(j) << endl;
                
            }
            return;
        }
    }
    if(!foundLine){
        cout<<"Cannot print busses. There is no line with ID "<<lineId<<"."<<endl;
    }
}


/*
This method identifies and prints every bus that drives through a specific stop. It first validates that the stop exists. 
Then, it scans all bus lines to see which ones include this stop in their route. For every line that passes through 
the stop, it prints the line's details and lists the buses assigned to it (formatted as a list like [12, 45]). If a line 
passes the stop but has no buses, it prints "None".
*/
void BilkentTourism::printBussesPassingStop(const int stopId) const {
    // Validate if the stop exists
    string stopName = "";
    bool stopExists = false;

    for (int i = 0; i < stops.getSize(); i++) {
        if (stops.get(i).stopId == stopId) {
            stopExists = true;
            stopName = stops.get(i).stopName;
            break;
        }
    }

    if (!stopExists) {
        cout << "Cannot print buses. There is no stop with ID " << stopId << "." << endl;
        return;
    }

    bool busesFound = false;
    for (int i = 0; i < busLines.getSize(); i++) {
        BusLine& line = busLines.get(i);
        for (int j = 0; j < line.lineStops.getSize(); j++) {
            if (line.lineStops.get(j).stopId == stopId) {
                busesFound = true;
                break;
            }
        }
        if (busesFound) break;
    }

    if (!busesFound) {
        cout << "Cannot print buses. No lines pass through the stop." << endl;
        return;
    }

    cout << "Buses and their assigned lines passing the stop " << stopId << " (" << stopName << "):" << endl;

    for (int i = 0; i < busLines.getSize(); i++) {
        BusLine& line = busLines.get(i);
        bool stopFoundInLine = false;

        for (int j = 0; j < line.lineStops.getSize(); j++) {
            if (line.lineStops.get(j).stopId == stopId) {
                stopFoundInLine = true;
                break;
            }
        }

        if (stopFoundInLine) {
            cout << "Line " << line.getId() << " (" << line.getLineName() << ") : ";

            if (line.lineBuses.isEmpty()) {
                cout << "None";
            } else {
                cout << "[";
                for (int k = 0; k < line.lineBuses.getSize(); k++) {
                    cout << line.lineBuses.get(k).getID();
                    if (k < line.lineBuses.getSize() - 1) {
                        cout << ",";
                    }
                }
                cout << "]";
            }
            cout << endl;
        }
    }
}


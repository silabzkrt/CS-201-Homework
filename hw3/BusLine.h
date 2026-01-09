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

#ifndef BUSLINE_H
#define BUSLINE_H

#include <string>
#include <iostream>
#include "LinkedList.h" 
class Bus; 
#include "Stop.h"
#include "Bus.h"

using namespace std;

class BusLine {
public:
    // are sorted
    LinkedList<Stop> lineStops;
    LinkedList<Bus> lineBuses;

    BusLine();
    BusLine(int id, string name);
    int getId();
    int getLineId();
    string getLineName();

    bool operator==(const BusLine& other) const;
    bool operator<(const BusLine& other) const;
    bool operator>(const BusLine& other) const;
    friend ostream& operator<<(ostream& os, const BusLine& line);
private:
    int lineId;
    string lineName;
    
};

#endif
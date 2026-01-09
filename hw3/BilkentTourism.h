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

#ifndef BILKENT_TOURISM_H
#define BILKENT_TOURISM_H

#include <string>
#include <iostream>
#include "LinkedList.h"
#include "BusLine.h"

using namespace std;

class BilkentTourism {
public:
    BilkentTourism();
    ~BilkentTourism();

    void addBusLine(const int lineId, const string& lineName);
    void removeBusLine(const int lineId);
    void printBusLines() const;

    void addStop(const int stopId, const string& stopName);
    void removeStop(const int stopId);
    void addStopToLine(const int stopId, const int lineId);
    void removeStopFromLine(const int stopId, const int lineId);
    void printStops(const int lineId) const;

    void assignBus(const int busId, const string& driverName, const int lineId);
    void unassignBus(const int busId);
    void printBussesInLine(const int lineId) const;
    void printBussesPassingStop(const int stopId) const;

private:
    LinkedList<BusLine> busLines;
    LinkedList<Stop> stops;
    LinkedList<Bus> buses;
};

#endif
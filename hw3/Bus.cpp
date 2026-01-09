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
#include "LinkedList.h"
#include "Bus.h"
#include <ostream>

using namespace std;

Bus::Bus() {
    busId = 0;
    busDriver = "";
}

Bus::Bus(int ID, const std::string& driverName) {
    busId = ID;
    busDriver = driverName;
}

Bus::Bus(const Bus& other) {
    busId = other.busId;
    busDriver = other.busDriver;
}

ostream& operator<<(std::ostream& os, const Bus& bus) {
    os << "Bus " << bus.busId << " : " << bus.busDriver;
    return os;
}

int Bus::getID() const {
    return busId;
}

void Bus::setID(int ID) {
    busId = ID;
}

string Bus::getDriver() {
    return busDriver;
}

bool Bus::getAssigned(){
    return assigned;
}

void Bus:: assignBus(){
    assigned = true;
}



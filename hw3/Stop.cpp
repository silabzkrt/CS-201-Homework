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

#include "Stop.h"
#include "Bus.h"

Stop::Stop() {
    stopId = 0;
    stopName = "";
}

Stop::Stop(int id, string name) {
    this->stopId = id;
    this->stopName = name;
}

bool Stop::operator==(const Stop& other) const {
    return this->stopId == other.stopId;
}

bool Stop::operator<(const Stop& other) const {
    return this->stopId < other.stopId;
}

bool Stop::operator>(const Stop& other) const {
    return this->stopId > other.stopId;
}

ostream& operator<<(ostream& os, const Stop& stop) {
    // Format: "Stop 14: Tunus"
    os << "Stop " << stop.stopId << " : " << stop.stopName;
    return os;
}

int Stop:: getId(){
    return stopId;
}


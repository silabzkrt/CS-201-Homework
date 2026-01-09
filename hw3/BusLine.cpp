/*
CS 201: Fundamental Structures of Computer Science I
Fall 2025
Homework Assignment 4
Student Name: Sıla Bozkurt
Student ID: 22401775
Section: 3
Instructor: Ercüment Çiçek
Assistants: Mehmet Alper Yılmaz, Sude Önder
Submission Date: 24.12.2025
*/

#include "BusLine.h"

BusLine::BusLine() {
    lineId = 0;
    lineName = "";
}

BusLine::BusLine(int id, string name) {
    lineId = id;
    lineName = name;
}

int BusLine:: getId(){
    return lineId;
}
int BusLine:: getLineId(){
    return lineId;
}
string BusLine:: getLineName(){
    return lineName;
}
bool BusLine::operator==(const BusLine& other) const {
    return lineId == other.lineId;
}
bool BusLine::operator<(const BusLine& other) const {
    return lineId < other.lineId;
}

bool BusLine::operator>(const BusLine& other) const {
    return lineId > other.lineId;
}
ostream& operator<<(ostream& os, const BusLine& line) {
    os << "Line " << line.lineId << " : " << line.lineName;
    return os;
}
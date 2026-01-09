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

#ifndef STOP_H
#define STOP_H

#include <string>
#include <iostream>
#include "LinkedList.h"

using namespace std;

class Stop {
public:
    int stopId;
    string stopName;

    Stop();
    Stop(int id, string name);

    bool operator==(const Stop& other) const;
    bool operator<(const Stop& other) const;
    bool operator>(const Stop& other) const;
    friend ostream& operator<<(ostream& os, const Stop& stop);

    int getId();
};

#endif
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

#ifndef BUS_H
#define BUS_H

#include <string>
#include <ostream>

using namespace std;

class Bus {
public:
    Bus();
    Bus(int ID, const string& driverName);
    Bus(const Bus& other); // Copy constructor takes a const reference
    friend std::ostream& operator<<(ostream& os, const Bus& bus);

    int getID() const;
    void setID(int ID);
    string getDriver();
    bool getAssigned();
    void assignBus();

    bool operator==(const Bus& other) const {
        return this->busId == other.busId;
    }

    bool operator<(const Bus& other) const {
        return this->busId < other.busId;
    }

    bool operator>(const Bus& other) const {
        return this->busId > other.busId;
    }

private:
    int busId;
    string busDriver;
    bool assigned;
};

#endif
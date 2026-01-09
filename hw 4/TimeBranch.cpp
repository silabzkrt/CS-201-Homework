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
#include "TimeBranch.h"
#include <iostream>
using namespace std;

TimeBranch::TimeBranch() : past(1), future(1), currentLocation(""), pastSize(1), futureSize(1), ID(0) {}

TimeBranch::TimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId)
    : past(pastCapacity), future(futureCapacity), currentLocation(startLocation), pastSize(pastCapacity), futureSize(futureCapacity), ID(branchId) {}

TimeBranch::~TimeBranch() {}

TimeBranch::TimeBranch(const TimeBranch& other)
    : past(other.past), future(other.future), currentLocation(other.currentLocation),
      timeStones(other.timeStones), pastSize(other.pastSize), futureSize(other.futureSize), ID(other.ID) {}

TimeBranch& TimeBranch::operator=(const TimeBranch& other) { 
    if (this == &other) return *this;
    past = other.past;
    future = other.future;
    currentLocation = other.currentLocation;
    timeStones = other.timeStones;
    pastSize = other.pastSize;
    futureSize = other.futureSize;
    ID = other.ID;
    return *this;
}

ostream& operator<<(ostream& os, const TimeBranch& timeBranch) {
    auto printStack = [&](Stack<string> s) {
        os << "[";
        if (!s.empty()) {
            Stack<string> rev;
            while (!s.empty()) rev.push(s.pop());
            os << " "; 
            while (!rev.empty()) {
                os << rev.pop();
                if (!rev.empty()) os << ", ";
            }
            os << " ";
        } else {
            os << "  ";
        }
        os << "]";
    };

    os << "\nPast   : "; printStack(timeBranch.past);
    os << "\nCurrent: ( " << timeBranch.currentLocation << " )";
    os << "\nFuture : "; printStack(timeBranch.future);
    os << "\nStones : "; printStack(timeBranch.timeStones);
    return os;
}

void TimeBranch::fastForward(const int k) {
    int steps = k;
    if (steps > (int)future.size()) steps = (int)future.size();

    if(steps + (int)past.size() > pastSize){
        cout << "Cannot fast forward " << k << " steps in branch "<<ID<<". Past stack capacity exceeded.\n";
        return;
    }

    for (int i = 0; i < steps; ++i) { 
        if (future.empty()) break;
        past.push(currentLocation);
        currentLocation = future.pop();
    }
    cout<<"Fast forwarded "<<steps<<" steps in branch "<<ID<<".\n";
}

void TimeBranch::rewind(const int k) {
    int steps = k;
    if (steps > (int)past.size()) steps = (int)past.size();

    if(steps + (int)future.size() > futureSize){
        cout << "Cannot rewind " << steps << " steps in branch "<<ID<<". Future stack capacity exceeded.\n";
        return;
    }

    for (int i = 0; i < steps; ++i) {
        if (past.empty()) break;
        future.push(currentLocation);
        currentLocation = past.pop();
    }
    cout<<"Rewound "<<steps<<" steps in branch "<<ID<<".\n";
}

void TimeBranch::travelTo(const string newLocation) {
    if((int)past.size() >= pastSize){
        cout << "Cannot travel to " << newLocation <<" in branch "<< ID<<". Past stack capacity exceeded.\n";
        return;
    }
    past.push(currentLocation);
    currentLocation = newLocation;
    future.clear();
    cout<<"Traveled to "<<newLocation<<" in branch "<<ID<<".\n";
}

void TimeBranch::placeTimeStone() {
    timeStones.push(currentLocation);
    cout<<"Time stone placed at "<<currentLocation<<".\n";
}

void TimeBranch::activateTimeStone() {
    if (timeStones.empty()) {
        cout << "Cannot activate time stone. No time stones available.\n";
        return;
    } 

    string L = timeStones.pop(); 
    
    if (currentLocation == L) {
        future.clear(); 
        cout << "Time stone activated. The traveler is now at " << L << ".\n";
        return;
    }

    Stack<string> tempPast = past; 
    bool foundInPast = false;
    while (!tempPast.empty()) {
        if (tempPast.pop() == L) { 
            foundInPast = true; 
            break; 
        }
    }

    Stack<string> tempFuture = future;
    bool foundInFuture = false;
    int stepsToL = 0;
    while (!tempFuture.empty()) {
        stepsToL++;
        if (tempFuture.pop() == L) { 
            foundInFuture = true; 
            break; 
        }
    }

    if (foundInPast) {
        while (currentLocation != L) {
            future.push(currentLocation);
            currentLocation = past.pop();
        }
        future.clear();
        cout << "Time stone activated. The traveler is now at " << L << ".\n";
        return;
    }

    if (foundInFuture) {
        if (stepsToL + (int)past.size() > pastSize) {
            cout << "Time stone discarded. Past stack capacity exceeded.\n";
            return;
        }
        while (currentLocation != L) {
            past.push(currentLocation);
            currentLocation = future.pop();
        }
        cout << "Time stone activated. The traveler is now at " << L << ".\n";
        return;
    }

    cout << "Time stone discarded. The recorded moment is no longer reachable.\n";
}

void TimeBranch::printTimeBranch() const {
    cout << *this;
}

int TimeBranch::getID(){ return ID; }
Stack<string>& TimeBranch::getPast(){ return past; }
Stack<string>& TimeBranch::getFuture(){ return future; }
Stack<string>& TimeBranch::getTimeStones(){ return timeStones; }
string TimeBranch::getCurrentLocation(){ return currentLocation; }
int TimeBranch::getPastSize(){ return pastSize; }
int TimeBranch::getFutureSize(){ return futureSize; }
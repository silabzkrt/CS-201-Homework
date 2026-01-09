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
#ifndef TIMEBRANCH_H
#define TIMEBRANCH_H

#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

class TimeBranch{
    public:
        TimeBranch(); 
        TimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId);
        ~TimeBranch();
        TimeBranch(const TimeBranch& other);
        TimeBranch& operator=(const TimeBranch& other);
        friend ostream& operator<<(ostream& os, const TimeBranch& timeBranch);
        
        void fastForward(const int k);
        void rewind(const int k);
        void travelTo(const string newLocation);
        void placeTimeStone();
        void activateTimeStone();
        void printTimeBranch() const;
        
        int getID();
        
        Stack<string>& getPast();
        Stack<string>& getFuture();
        Stack<string>& getTimeStones();
        
        string getCurrentLocation();
        int getPastSize();
        int getFutureSize();

    private:
        Stack<string> past;
        Stack<string> future;
        string currentLocation;
        Stack<string> timeStones;
        int pastSize;   
        int futureSize; 
        int ID;
};

#endif
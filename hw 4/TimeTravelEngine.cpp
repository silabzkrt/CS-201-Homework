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
#include "TimeTravelEngine.h"
#include <iostream>
using namespace std;

TimeTravelEngine::TimeTravelEngine() {}
TimeTravelEngine::~TimeTravelEngine() {}

int TimeTravelEngine::createTimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId){
    Stack <TimeBranch> temp = branches;
    while(!temp.empty()){
        if(temp.pop().getID() == branchId){
            cout<<"Cannot create time branch. A branch with ID "<<branchId<<" already exists."<<endl;
            return -1;
        }
    }
    TimeBranch newBranch(pastCapacity, futureCapacity, startLocation, branchId);
    branches.push(newBranch);
    cout<<"Created time branch with ID "<<branchId<<"."<<endl;
    return branchId;
}

void TimeTravelEngine::deleteTimeBranch(const int branchId){
    Stack<TimeBranch> tempStack;
    bool found = false;
    while (!branches.empty()) {
        TimeBranch currentBranch = branches.pop();
        if (currentBranch.getID() == branchId) {
            found = true; 
            cout << "Deleted time branch " << branchId << "." << endl;
        } else {
            tempStack.push(currentBranch); 
        }
    }
    while (!tempStack.empty()) branches.push(tempStack.pop());
    if (!found) cout << "Cannot delete branch. There is no branch with ID " << branchId << "." << endl;
}

void TimeTravelEngine::printAllBranches() const{
    Stack <TimeBranch> temp = branches;
    if(temp.empty()){
        cout << "There are no time branches to show." << endl;
        return;
    }

    int count = (int)temp.size();
    TimeBranch* sortArray = new TimeBranch[count];
    int idx = 0;
    while(!temp.empty()){
        sortArray[idx++] = temp.pop();
    }

    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(sortArray[j].getID() > sortArray[j+1].getID()) {
                TimeBranch t = sortArray[j];
                sortArray[j] = sortArray[j+1];
                sortArray[j+1] = t;
            }
        }
    }

    cout<<"Time branches in the system:"<<endl;
    for(int i = 0; i < count; i++) {
        cout<<"Branch "<< sortArray[i].getID() <<":";
        cout<<sortArray[i];
        cout<<endl;
        
        if(i < count - 1){
            cout<<endl;
        }
    }
    delete[] sortArray;
}

void TimeTravelEngine::travelTo(const int branchId, const string newLocation){
    Stack<TimeBranch> tempStack;
    Stack<TimeBranch> reverseStack;
    bool found = false;
    
    // Pop all branches and store them
    while (!branches.empty()) {
        tempStack.push(branches.pop());
    }
    
    // Process each branch in correct order
    while (!tempStack.empty()) {
        TimeBranch currentBranch = tempStack.pop();
        if (currentBranch.getID() == branchId) {
            currentBranch.travelTo(newLocation);
            found = true;
        }
        reverseStack.push(currentBranch);
    }
    
    // Rebuild branches stack
    while (!reverseStack.empty()) {
        branches.push(reverseStack.pop());
    }
    
    if (!found) cout << "Cannot travel. There is no branch with ID " << branchId << "." << endl;
}

void TimeTravelEngine::fastForward(const int branchId, const int k){
    Stack<TimeBranch> tempStack;
    Stack<TimeBranch> reverseStack;
    bool found = false;
    
    // Pop all branches and store them
    while (!branches.empty()) {
        tempStack.push(branches.pop());
    }
    
    // Process each branch in correct order
    while (!tempStack.empty()) {
        TimeBranch currentBranch = tempStack.pop();
        if (currentBranch.getID() == branchId) {
            currentBranch.fastForward(k);
            found = true;
        }
        reverseStack.push(currentBranch);
    }
    
    // Rebuild branches stack
    while (!reverseStack.empty()) {
        branches.push(reverseStack.pop());
    }
    
    if (!found) cout << "Cannot fast forward. There is no branch with ID " << branchId << "." << endl;
}

void TimeTravelEngine::rewind(const int branchId, const int k){
    Stack<TimeBranch> tempStack;
    Stack<TimeBranch> reverseStack;
    bool found = false;
    
    // Pop all branches and store them
    while (!branches.empty()) {
        tempStack.push(branches.pop());
    }
    
    // Process each branch in correct order
    while (!tempStack.empty()) {
        TimeBranch currentBranch = tempStack.pop();
        if (currentBranch.getID() == branchId) {
            currentBranch.rewind(k);
            found = true;
        }
        reverseStack.push(currentBranch);
    }
    
    // Rebuild branches stack
    while (!reverseStack.empty()) {
        branches.push(reverseStack.pop());
    }

    if (!found) cout << "Cannot rewind. There is no branch with ID " << branchId << "." << endl;
}

void TimeTravelEngine::placeTimeStone(const int branchId){
    Stack<TimeBranch> tempStack;
    Stack<TimeBranch> reverseStack;
    bool found = false;
    
    // Pop all branches and store them
    while (!branches.empty()) {
        tempStack.push(branches.pop());
    }
    
    // Process each branch in correct order
    while (!tempStack.empty()) {
        TimeBranch currentBranch = tempStack.pop();
        if (currentBranch.getID() == branchId) {
            currentBranch.placeTimeStone();
            found = true;
        }
        reverseStack.push(currentBranch);
    }
    
    // Rebuild branches stack
    while (!reverseStack.empty()) {
        branches.push(reverseStack.pop());
    }
    
    if (!found) cout << "Cannot place a timestone. There is no branch with ID " << branchId << "." << endl;
}

void TimeTravelEngine::activateTimeStone(const int branchId){
    Stack<TimeBranch> tempStack;
    Stack<TimeBranch> reverseStack;
    bool found = false;
    
    // Pop all branches and store them
    while (!branches.empty()) {
        tempStack.push(branches.pop());
    }
    
    // Process each branch in correct order
    while (!tempStack.empty()) {
        TimeBranch currentBranch = tempStack.pop();
        if (currentBranch.getID() == branchId) {
            currentBranch.activateTimeStone();
            found = true;
        }
        reverseStack.push(currentBranch);
    }
    
    // Rebuild branches stack
    while (!reverseStack.empty()) {
        branches.push(reverseStack.pop());
    }
    
    if (!found) cout << "Cannot activate timestone. There is no branch with ID " << branchId << "." << endl;
}

void TimeTravelEngine::printTimeBranch(const int branchId) const{
    Stack<TimeBranch> tempStack = branches;
    bool found = false;
    while (!tempStack.empty()) {
        TimeBranch currentBranch = tempStack.pop();
        if (currentBranch.getID() == branchId) {
            cout << currentBranch << endl;
            found = true; 
            break; 
        }
    }
    if (!found) cout << "Cannot print branch. There is no branch with ID " << branchId << "." << endl;
}

int TimeTravelEngine::mergeBranches(const int branchId1, const int branchId2, const int newBranchId){
    Stack<TimeBranch> checkStack = branches;
    while(!checkStack.empty()){
        if(checkStack.pop().getID() == newBranchId){
            cout<<"Cannot merge branches. A branch with ID "<<newBranchId<<" already exists."<<endl;
            return -1;
        }
    }

    bool found1 = false, found2 = false;
    TimeBranch branch1, branch2;
    Stack<TimeBranch> finder = branches;
    while (!finder.empty()) {
        TimeBranch currentBranch = finder.pop();
        if (currentBranch.getID() == branchId1) { branch1 = currentBranch; found1 = true; } 
        if (currentBranch.getID() == branchId2) { branch2 = currentBranch; found2 = true; }
    }

    if(!found1 || !found2 ){
        cout<<"Cannot merge branches. Missing branch IDs."<<endl;
        return -1;
    }

    if(branch1.getCurrentLocation() != branch2.getCurrentLocation()){
        cout<<"Cannot merge branches. Current locations do not match."<<endl;
        return -1;
    }

    TimeBranch mergedBranch(branch1.getPastSize() + branch2.getPastSize(),
                            branch1.getFutureSize() + branch2.getFutureSize(),
                            branch1.getCurrentLocation(), newBranchId);

    auto mergeStacks = [&](Stack<string>& dest, Stack<string> src) {
        Stack<string> rev;
        while(!src.empty()) rev.push(src.pop());
        while(!rev.empty()) dest.push(rev.pop());
    };

    mergeStacks(mergedBranch.getPast(), branch1.getPast());
    mergeStacks(mergedBranch.getPast(), branch2.getPast());
    mergeStacks(mergedBranch.getFuture(), branch1.getFuture());
    mergeStacks(mergedBranch.getFuture(), branch2.getFuture());
    mergeStacks(mergedBranch.getTimeStones(), branch1.getTimeStones());
    mergeStacks(mergedBranch.getTimeStones(), branch2.getTimeStones());

    Stack<TimeBranch> tempStack;
    while (!branches.empty()) {
        TimeBranch currentBranch = branches.pop();
        if (currentBranch.getID() != branchId1 && currentBranch.getID() != branchId2) {
            tempStack.push(currentBranch);
        }
    }
    while (!tempStack.empty()) branches.push(tempStack.pop());
    branches.push(mergedBranch);

    cout << "Time branches "<<branchId1<<" and "<<branchId2<<" merged into new branch "<<newBranchId<<"." << endl;
    return newBranchId; 
}
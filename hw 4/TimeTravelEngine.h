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
#ifndef TIMETRAVEL_H
#define TIMETRAVEL_H

#include <string>
#include "TimeBranch.h"
using namespace std;

class TimeTravelEngine
{
public:
	TimeTravelEngine();
	~TimeTravelEngine();

	int createTimeBranch(const int pastCapacity,
						const int futureCapacity,
						const string startLocation,
						const int branchId);

	void deleteTimeBranch(const int branchId);
	void printAllBranches() const;

	void travelTo(const int branchId, const string newLocation);

	void fastForward(const int branchId, const int k);
	void rewind(const int branchId, const int k);

	void placeTimeStone(const int branchId);
	void activateTimeStone(const int branchId);

	void printTimeBranch(const int branchId) const;

	int mergeBranches(const int branchId1,
					 const int branchId2,
					 const int newBranchId);

	Stack <TimeBranch> branches;
};

#endif
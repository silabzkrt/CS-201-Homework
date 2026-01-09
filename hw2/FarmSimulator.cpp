#include "FarmSimulator.h"
#include "Sheep.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <algorithm>
#include <set>
using namespace std;
FarmSimulator::FarmSimulator(){
    this->numberOfSheeps = 0;
    this->sheeps = nullptr;
}
FarmSimulator::FarmSimulator (int numberOfSheeps){
    this->numberOfSheeps = numberOfSheeps;
    this->sheeps = new Sheep[numberOfSheeps];

}
FarmSimulator::~FarmSimulator(){
    delete[] this->sheeps;
}
void FarmSimulator::createSheep(int number){
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, 10 * number);

    delete[] this->sheeps;
    this->numberOfSheeps = number;
    this->sheeps = new Sheep[numberOfSheeps];
    
    set<int> usedIds;
    
    for (int i = 0; i < numberOfSheeps; i++){
        int id;
        do {
            id = distr(gen);
        } while (usedIds.find(id) != usedIds.end());
        
        usedIds.insert(id);
        this->sheeps[i].setID(id);
    }
    
    sort(this->sheeps, this->sheeps + this->numberOfSheeps);
}
int* FarmSimulator::lineerSearch(int n, int k) {
    int index = numberOfSheeps; 
    int exactMatchIndex = -1;
    for (int i = 0; i < numberOfSheeps; i++) {
        if (sheeps[i].getId() == n) {
            exactMatchIndex = i;
            break; 
        }
        if (sheeps[i].getId() > n) {
            index = i; 
            break; 
        }
    }
    if (exactMatchIndex != -1) {
        int* result = new int[1];
        result[0] = sheeps[exactMatchIndex].getId();
        return result;
    } 
    else {
        int* result = new int[k];
        int left = index - 1;
        int right = index;
        int count = 0;

        while (count < k) {
            if (left < 0) {
                sheeps[right].infect();
                result[count] = sheeps[right].getId();
                right++;
            } 
            else if (right >= numberOfSheeps) {
                sheeps[left].infect();
                result[count] = sheeps[left].getId();
                left--;
            } 
            else {
                int distLeft = abs(n - sheeps[left].getId());
                int distRight = abs(sheeps[right].getId() - n);

                if (distLeft <= distRight) {
                    sheeps[left].infect();
                    result[count] = sheeps[left].getId();
                    left--;
                } else {
                    sheeps[right].infect();
                    result[count] = sheeps[right].getId();
                    right++;
                }
            }
            count++;
        }
        return result;
    }
}
int* FarmSimulator::binaryInfect(int n, int k){
    int deadSheepID = binarySearch(n);
    if (deadSheepID < numberOfSheeps && sheeps[deadSheepID].getId() == n) {
        int* result = new int[1];
        result[0] = sheeps[deadSheepID].getId();
        return result;
    }
    else{

        int* result = new int[k];
        
        int left = deadSheepID - 1; 
        int right = deadSheepID;    
        int count = 0;

        while (count < k) {
            if (left < 0) {
                result[count] = sheeps[right].getId();
                sheeps[right].infect(); 
                right++;
            } 
            else if (right >= numberOfSheeps) {
                result[count] = sheeps[left].getId();
                sheeps[left].infect(); 
                left--;
            } 
            else {
                int distLeft = abs(n - sheeps[left].getId());
                int distRight = abs(sheeps[right].getId() - n);

                if (distLeft <= distRight) {
                    result[count] = sheeps[left].getId();
                    sheeps[left].infect(); 
                    left--;
                } else {
                    result[count] = sheeps[right].getId();
                    sheeps[right].infect(); 
                    right++;
                }
            }
            count++;
        }
        return result;
    }
}
int FarmSimulator::binarySearch(int n) {
    int low = 0;
    int high = numberOfSheeps - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (sheeps[mid].getId() == n)
             return mid; 
        if (sheeps[mid].getId() < n)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}
int FarmSimulator::jumpSearch(int n){
    int step = numberOfSheeps;
    int prev = 0;

    while (prev + step < numberOfSheeps && sheeps[prev + step - 1].getId() < n) {
        prev += step;
    }

    int end = min(prev + step, numberOfSheeps);
    for (int i = prev; i < end; i++) {
        if (sheeps[i].getId() >= n) {
            return i; 
        }
    }
    return numberOfSheeps;
}
int* FarmSimulator::jumpInfect(int n, int k){
    int index = jumpSearch(n);

    if (index < numberOfSheeps && sheeps[index].getId() == n) {
        int* result = new int[1];
        result[0] = sheeps[index].getId();
        return result;
    }
    int* result = new int[k];
    int left = index - 1;
    int right = index;
    int count = 0;

    while (count < k) {
        if (left < 0) {
            result[count] = sheeps[right].getId();
            right++;
        } else if (right >= numberOfSheeps) {
            result[count] = sheeps[left].getId();
            left--;
        } else {
            int distLeft = abs(n - sheeps[left].getId());
            int distRight = abs(sheeps[right].getId() - n);

            if (distLeft <= distRight) {
                result[count] = sheeps[left].getId();
                left--;
            } else {
                result[count] = sheeps[right].getId();
                right++;
            }
        }
        count++;
    }
    return result;
}


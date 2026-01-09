#ifndef FARMSIMULATOR_H
#define FARMSIMULATOR_H

#include "Sheep.h"
class FarmSimulator{
    public:
    FarmSimulator();
    FarmSimulator (int numberOfSheeps);
    ~FarmSimulator();
    void createSheep(int number);
    int* lineerSearch(int n, int k);
    int* binaryInfect(int n,int k);
    int binarySearch(int n);
    int jumpSearch(int number);
    int* jumpInfect(int n, int k);

    private:
    Sheep* sheeps;
    int numberOfSheeps;
};
#endif
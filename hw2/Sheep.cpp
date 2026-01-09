#include "Sheep.h"
using namespace std;
Sheep::Sheep (const int id){
    this->id = id;
    this->hasDisease = false;
}
Sheep::Sheep (){
    this->id = 0;
    this->hasDisease = false;
}
Sheep::Sheep (const Sheep& other){
    this->id = other.id;
    this->hasDisease = other.hasDisease;
}
Sheep::~Sheep(){}
Sheep& Sheep::operator = (const Sheep& other){
    if (this != &other){
        this->id = other.id;
        this->hasDisease = other.hasDisease;
    }
    return *this;
}
bool Sheep::operator<(const Sheep& other) const {
        return this->id < other.id;
}
int Sheep:: getId(){
    return this->id;
}
int Sheep:: setID(const int id){
    this->id = id;
    return this->id;
}
bool Sheep:: isInfected(){
    return this->hasDisease;
}
void Sheep:: infect(){
    this->hasDisease = true;
}
void Sheep:: giveMedicine(){
    this->hasDisease = false;
}


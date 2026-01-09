/*
CS 201: Fundamental Structures of Computer Science I
Fall 2025
Homework Assignment 1
Student Name: Sıla Bozkurt
Student ID: 22401775
Section: 3
Instructor: Ercüment Çiçek
Assistants: Pınar Gül, Mehmet Alper Yılmaz
Submission Date: 30.10.2025
*/
#include <iostream>
#include <string>

using namespace std;

class Player{
public:
    Player(int id, const string& name);
    Player();
    Player (const Player& other);
    ~Player();
    Player& operator = (const Player& other);
    void addCard(const string& card);
    void discardCard(int index);
    int findCard(const string& cardToFind);
    void clearCards();
    string getUserName() const;
    int getID() const;
    void setUserName(const string& name);
    void setID(const int& id);
    int getCardCount() const;
    const string& getCardAtIndex(int index) const;

private:
    string name;
    int id;
    string* cards;
    int cardCount;
};

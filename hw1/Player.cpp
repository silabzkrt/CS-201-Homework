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
#include "Player.h"
#include <string>

using namespace std;
//constructor
Player::Player(int id, const string& name)
    : name(name),
    id(id),
    cardCount(0)
{
    cards = nullptr;
}

Player::Player()
    : name(""),
    id(0),
    cardCount(0)
{
    cards = nullptr;
}
// copy constructor
Player::Player(const Player& other)
    : name(other.name),
    id(other.id),
    cardCount(other.cardCount)
{
    cards = new string[cardCount];
    for (int i = 0; i < cardCount; ++i) {
        cards[i] = other.cards[i];
    }
}

Player::~Player(){
    delete[] cards;
}

// overriding "=" operator
Player& Player::operator=(const Player& other){
    if(this == &other){
        return *this;
    }

    delete[] cards;

    name = other.name;
    id = other.id;
    cardCount = other.cardCount;

    cards = new string [cardCount];
    for (int i = 0; i < cardCount; i++){
        cards [i] = other.cards[i];
    }
    return *this;
}

void Player:: addCard(const string& card){
    string* newCards = new string[cardCount + 1];
    for (int i = 0; i < cardCount; i++){
        newCards [i] = cards [i];
    }
    newCards [cardCount] = card;
    delete [] cards;
    cards = newCards;
    cardCount++;
}

void Player:: discardCard(int index){
    if (index < 0){
        cout<< "Invalid index!"<<endl;
        return;
    }
    if (index >= cardCount){
        cout<< "You cannot discard a card that doesn't exist in player's hand!"<<endl;
        return;
    }
    string* updatedHand = new string[cardCount - 1];

    for (int i = 0; i < index; i++){ //from 0 till index
        updatedHand [i] = cards [i];
    }
    for (int i = index; i < cardCount - 1; i++){ // from index till the end
        updatedHand[i] = cards[i + 1]; // Use i + 1 to skip the discarded card
    }

    delete [] cards;
    cards = updatedHand;
    cardCount--;

}

int Player::findCard(const string& cardToFind){
    for (int i = 0; i < cardCount; i++){
        if(this->cards[i] == cardToFind){ 
            discardCard(i); 
            return i;
        }
    }
    return -1; 
}

void Player::clearCards(){
    delete [] cards;
    cards = nullptr;
    cardCount = 0;
}

//Getters and Setters 

string Player:: getUserName()const{ // we add const because we want to be able to use this function with constant variables as well
    return this -> name;
}

int Player :: getID()const{
    return this -> id;
}

void Player::setUserName(const string& newName) {
    name = newName;
}

void Player::setID(const int& newId) {
    id = newId;
}


int Player:: getCardCount() const{
    return this -> cardCount;
}

const string& Player::getCardAtIndex(int index) const{
    if (index >= cardCount || index < 0){
        throw std::out_of_range("Invalid card index");
    }           
    return cards[index];
}

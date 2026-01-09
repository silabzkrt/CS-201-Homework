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
#include "Player.h"
using namespace std;

class MagicCard {
public:
MagicCard();
~MagicCard();

void addPlayer( const int playerID, const string name );
void removePlayer( const int playerID );
void printPlayers() const;

void setDrawPile( const string drawPile[], const int size );
void drawCardFromDeck( const int playerID, const int n );
void switchHands( const int player1ID, const int player2ID );
void listDrawPile() const;
void listDiscardPile() const;
void listCardsOfPlayer( const int playerID ) const;

void play( const int playerID, const string card );

private:
    Player* players;
    string* draw;
    string* discard;
    int playerCount;
    int drawSize;
    int discardSize;
};
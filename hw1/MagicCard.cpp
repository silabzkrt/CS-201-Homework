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
#include "MagicCard.h"
#include <iostream>
#include <string>

using namespace std;
MagicCard::MagicCard() {
    players = nullptr; 
    draw = nullptr;     
    discard = nullptr;  
    playerCount = 0;    
    drawSize = 0;      
    discardSize = 0;    
}

MagicCard::~MagicCard() { //deallocate
    delete[] players;
    delete[] discard;
    delete[] draw;
}

/*
* This method is to add players. We initilaize a new dynamically allocated array and add the new player on the last index then we 
* point our players pointer to this newly allocated array which also contains the new player before adding a player this method 
* also checks if a player with such id exists if yes it doesnt add and prints out an error message 
*/
void MagicCard::addPlayer(const int playerID, const string name) {
    if (playerCount!= 0){ //prevents null error
        for (int i = 0; i < playerCount; i++) {     // Check if player with this ID already exists
            if (players[i].getID() == playerID) {
                cout << "Cannot add player. ID " << playerID << " already exists." << endl;
                return;
            }
        }
        Player* newPlayer;
        newPlayer = new Player [playerCount + 1]; // adds the most recent player on the end of the list
        for (int i = 0; i < playerCount ; i++){
            newPlayer [i] = players [i];
            
        }
        newPlayer[playerCount] = Player(playerID, name); // calls the player constructor
        delete [] players;
        players = newPlayer;
        playerCount++;
        cout<< "Added player " << name << " with ID " << playerID << "."<<endl;
    }
    else{
        players = new Player [1]; // implements player count
        players[0] = Player(playerID, name);
        playerCount++;
        cout<< "Added player " << name << " with ID " << playerID << "."<<endl;
    }
}

/*
* This method removes a player and checks if a player with such ID exists if yes then it removes them from the player's array 
* by creating a new dynamically allocated array without that player and pointing players to that new array
*/
void MagicCard::removePlayer(const int playerID) {
    if (playerCount == 0) { //if there are no players to be removed
        cout << "No players to be removed!" << endl;
        return;
    }

    int index = -1; // we use this to check if we found a player with the wanted id exists or not
    for (int i = 0; i < playerCount; ++i) {
        if (players[i].getID() == playerID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Cannot remove player. There is no player with ID " << playerID << "." << endl;
        return;
    }

    if (playerCount == 1) { 
        delete[] players;
        players = nullptr;
        playerCount = 0;
        cout << "Removed player " << playerID << "." << endl;
        return;
    }

    Player* updatedPlayer = new Player[playerCount - 1];
    for (int i = 0; i < index; ++i) {
        updatedPlayer[i] = players[i];
    }
    for (int i = index; i < playerCount - 1; ++i) {
        updatedPlayer[i] = players[i + 1];
    }

    delete[] players;
    players = updatedPlayer;
    playerCount--;
    cout << "Removed player " << playerID << "." << endl;
}

/*
* This method prints out the currently playing characters in the game it sorts and prints them
*/
void MagicCard::printPlayers() const {
    if(playerCount == 0){
        cout<< "Cannot print players. There is no player in the game."<<endl;
        return;
    }
    //sorts existing players so that they will be printed by accordance to their ids
    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = 0; j < playerCount - i - 1; j++) {
            if (players[j].getID() > players[j + 1].getID()) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
    cout<<"Players :"<<endl;
    for (int i = 0; i < playerCount; i++){
        cout<< "Player " << players[i].getID() << " : " << players[i].getUserName()<<endl;
    }
}

/*
* This method initializes draw pile to an already existing array with a previosly initilized size
*/
void MagicCard::setDrawPile(const string drawPile[], const int size) {
    delete[] draw;
    draw = new string[size];
    for (int i = 0; i < size; i++){ 
        draw [i] = drawPile[i]; // adds from draw Pile to the number we want to add
    }
    drawSize = size;
    cout<< "Draw pile has been initialized."<<endl;
}

/*
* This method adds a card from draw pile to user's cards, checks if the cards index and players id is accurate then goes with it
*/
void MagicCard::drawCardFromDeck(const int playerID, const int n) {
    if (n < 0 || n >= drawSize) { //either has a negative index or a number bigger than decks's total 
        cout << "Cannot draw card. The input index is not valid." << endl;
        return;
    }
    for(int i = 0; i < playerCount; i++){
        if(players[i].getID() == playerID){
            players[i].addCard(draw[n]);
            string* updateDraw = new string [drawSize - 1];
            // Copy elements before index n
            for (int j = 0; j < n; j++){
                updateDraw [j] = draw [j];
            }
            // Copy elements after index n
            for (int j = n; j < drawSize - 1; j++){
                updateDraw[j] = draw[j + 1];
            }
            cout << players[i].getUserName() << " drew card " << draw[n] << " from the draw pile." << endl;
            delete [] draw;
            draw = updateDraw;
            drawSize--;
            return;
        }
    }
    cout << "Player not found!" << endl;
}

/*
* This method switches cards between two players by creating temporary arrays to store their cards, clearing their current hands,
* and then redistributing the cards to each other. If either player doesn't exist, it prints an error message.
*/
void MagicCard::switchHands(const int player1ID, const int player2ID) {
    Player* player1 = nullptr;
    Player* player2 = nullptr;
    bool found1 = false, found2 = false;
    
    for (int i = 0; i < playerCount; i++){
        if(players[i].getID() == player1ID){
            player1 = &players[i];
            found1 = true;
        }
        else if(players[i].getID() == player2ID){
            player2 = &players[i];
            found2 = true;
        }
    }
    
    if(found1 && found2){
        cout << "Switched hands between " << player1->getUserName() << " and " << player2->getUserName() << "." << endl;
        int count1 = player1->getCardCount();
        int count2 = player2->getCardCount();
        
        string* temp1 = new string[count1];
        string* temp2 = new string[count2];
        
        for(int i = 0; i < count1; i++){
            temp1[i] = player1->getCardAtIndex(i);
        }
        
        for(int i = 0; i < count2; i++){
            temp2[i] = player2->getCardAtIndex(i);
        }
        
        player1->clearCards();
        player2->clearCards();
        
        for(int i = 0; i < count2; i++){
            player1->addCard(temp2[i]);
        }
        
        for(int i = 0; i < count1; i++){
            player2->addCard(temp1[i]);
        }

        delete[] temp1;
        delete[] temp2;
        temp1 = nullptr;
        temp2 = nullptr;
    }

    else{ // when we couldn't find player 1 nor 2
        cout<<"Cannot switch hands. One or both players do not exist."<<endl;
    } 
}

/*
* Lists draw pile but checks if it's emoty first
*/
void MagicCard::listDrawPile() const {
    if(drawSize == 0){
        cout<< "Draw pile is empty."<<endl;
        return;
    }
    cout << "Draw pile: [";
    for (int i = 0; i < drawSize; i++){ 
        cout<< draw[i];
        if (i < drawSize - 1) {
            cout << ", ";
        }
    }
    cout<< "]" <<endl;
}

/*
Lists discard pile also checks for emptiness
*/
void MagicCard::listDiscardPile() const {
    if(discardSize == 0){
        cout<< "Discard pile is empty."<<endl;
        return;
    }
    cout<< "Discard pile: [";
    for (int i = 0; i < discardSize; i++){
        cout<< discard[i];
        if (i < discardSize - 1) {
            cout << ", ";
        }
    }
    cout<< "]" <<endl;
}
/*
* Lists cards of players based on players id we add const to be able to use in constant variables as well
*/
void MagicCard::listCardsOfPlayer(const int playerID) const {
    for (int i = 0; i < playerCount; i++){
        if(players[i].getID() == playerID){
            cout<< "Cards of " << players[i].getUserName() << ": ["; 
            for (int j = 0; j < players[i].getCardCount(); j++){
                cout << players[i].getCardAtIndex(j);
                if (j < players[i].getCardCount() - 1) {
                    cout << ", ";
                }
            }
            cout<< "]"<<endl;
            return; 
        }
    }
    cout << "Cannot list cards. Player with ID " << playerID << " does not exist." << endl; 
}

/*
*This play method implements the core game logic for what appears to be a card game similar to Uno. The method first validates if the player exists 
*and has the specified card, then checks if the played card matches either the color or number of the top card on the discard pile 
*(if any cards have been discarded). If the play is valid, the card is added to the discard pile and removed from the player's hand; if invalid, 
*the player must draw a card from the draw pile. Finally, the method checks win conditions: either when a player runs out of cards 
*(winning the game) or when the draw pile is empty and a player cannot make a valid play (ending the game with no winner).
*/
void MagicCard::play(const int playerID, const string card) {
    Player* player = nullptr;
    for (int i = 0; i < playerCount; i++) {
        if (players[i].getID() == playerID) {
            player = &players[i];
            break; 
        }
    }

    if (player == nullptr) {
        cout << "There is no player with ID " << playerID << "." << endl;
        return;
    }

    int cardIndex = player->findCard(card); 
    if (cardIndex == -1) {

        cout << "The player does not have " << card << " card." << endl; 
        return;
    }

    bool cont = false; // decides to let player play or not if it cannot it draws a card
    if (discardSize == 0) {
        cont = true; 
    } else {
        // initialized them as strings to visualise the select process
        string topCard = discard[discardSize - 1]; 
        string topColor = topCard.substr(0, 1);
        string topNum = topCard.substr(1);
        string playedColor = card.substr(0, 1);
        string playedNum = card.substr(1);

        if (playedColor == topColor || playedNum == topNum) { // if it matches it's color or number
            cont = true;
        }
    }

    string* newDiscard = new string[discardSize + 1];
    for (int k = 0; k < discardSize; k++) {
        newDiscard[k] = discard[k]; 
    }
    newDiscard[discardSize] = card; 
    delete[] discard;
    discard = newDiscard;
    discardSize++;

    if (cont) {
        cout << "Player " << playerID << " played " << card << "." << endl;
    } else {
        if (drawSize > 0) {
            string drawnCard = draw[0]; 
            
            cout << "Player " << playerID << " played " << card << " then drew " << drawnCard << "." << endl;

            player->addCard(drawnCard); 

            string* newDraw = new string[drawSize - 1];
            for (int k = 0; k < drawSize - 1; k++) {
                newDraw[k] = draw[k + 1];
            }
            delete[] draw;
            draw = newDraw;
            drawSize--;

        } else {
            cout << "Player " << playerID << " cannot play " << card << " and draws a card." << endl;
        }
    }
    
    if (player->getCardCount() == 0) { // when a player's cards have ended
        cout << "The game has ended. Player " << playerID << " won." << endl;
    } else if (drawSize == 0) {
        if (!cont) { //no card on p-draw pile, we assume noone was eligible to play here
             cout << "The game has ended. No cards remain in the draw pile." << endl;
        }
    }
}

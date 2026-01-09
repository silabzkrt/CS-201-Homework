#include <iostream>
#include <string>
#include "MagicCard.h" // Assumes MagicCard.h and Player.h are in the same directory or include path

using namespace std;

int main() {
    cout << "--- Comprehensive MagicCard Test ---" << endl << endl;

    MagicCard game;

    // --- Initial State Tests ---
    cout << "--- Testing Initial State ---" << endl;
    game.printPlayers();       // Boundary: Empty player list
    game.listDrawPile();       // Boundary: Empty draw pile
    game.listDiscardPile();    // Boundary: Empty discard pile
    game.listCardsOfPlayer(1); // Error: Player doesn't exist
    cout << endl;

    // --- Player Management Tests ---
    cout << "--- Testing Player Management ---" << endl;
    game.addPlayer(10, "Alice");
    game.addPlayer(5, "Bob");      // Add out of order to test sorting
    game.addPlayer(20, "Charlie");
    game.addPlayer(10, "David");   // Error: Duplicate ID
    game.printPlayers();           // Check sorting and correct additions
    cout << endl;

    game.removePlayer(99);         // Error: Player doesn't exist
    game.removePlayer(5);          // Remove middle player
    game.printPlayers();           // Check removal and sorting
    cout << endl;

    game.removePlayer(10);         // Remove first player (after sort)
    game.removePlayer(20);         // Remove last player (now the only player)
    game.printPlayers();           // Boundary: Empty player list again
    cout << endl;

    // Re-add players for further tests
    game.addPlayer(1, "PlayerOne");
    game.addPlayer(2, "PlayerTwo");
    game.addPlayer(3, "PlayerThree");
    cout << "Players added for game tests:" << endl;
    game.printPlayers();
    cout << endl;

    // --- Pile Setup and Drawing Tests ---
    cout << "--- Testing Pile Setup and Drawing ---" << endl;
    string initialDeck[] = {"R1", "G2", "B3", "Y4", "R5", "G6", "B7", "Y8", "R9", "G10"};
    game.setDrawPile(initialDeck, 10);
    game.listDrawPile();
    game.listDiscardPile(); // Should still be empty
    cout << endl;

    game.drawCardFromDeck(1, 0);   // Player 1 draws R1 (first card)
    game.drawCardFromDeck(2, 8);   // Player 2 draws G10 (last card, index becomes 8 after first draw)
    game.drawCardFromDeck(3, 3);   // Player 3 draws R5 (middle card)
    game.drawCardFromDeck(1, -1);  // Error: Invalid index (negative)
    game.drawCardFromDeck(1, 10); // Error: Invalid index (too high)
    game.drawCardFromDeck(99, 0); // Error: Player doesn't exist
    cout << endl;

    game.listDrawPile(); // Check cards removed
    game.listCardsOfPlayer(1); // Check P1 hand [R1]
    game.listCardsOfPlayer(2); // Check P2 hand [G10]
    game.listCardsOfPlayer(3); // Check P3 hand [R5]
    cout << endl;

    // Draw more cards
    game.drawCardFromDeck(1, 0); // P1 draws G2
    game.drawCardFromDeck(2, 0); // P2 draws B3
    game.drawCardFromDeck(3, 0); // P3 draws Y4
    game.drawCardFromDeck(1, 0); // P1 draws G6
    game.listCardsOfPlayer(1); // Check P1 hand [R1, G2, G6]
    game.listCardsOfPlayer(2); // Check P2 hand [G10, B3]
    game.listCardsOfPlayer(3); // Check P3 hand [R5, Y4]
    game.listDrawPile(); // [B7, Y8, R9] left
    cout << endl;


    // --- switchHands Tests ---
    cout << "--- Testing switchHands ---" << endl;
    game.switchHands(1, 2);       // Valid switch
    game.listCardsOfPlayer(1);    // Should have P2's cards [G10, B3]
    game.listCardsOfPlayer(2);    // Should have P1's cards [R1, G2, G6]
    cout << endl;
    game.switchHands(1, 99);      // Error: P2 doesn't exist
    game.switchHands(99, 2);      // Error: P1 doesn't exist
    game.switchHands(99, 100);    // Error: Both don't exist
    game.switchHands(3, 3);       // Switching player with self (should ideally do nothing gracefully)
    game.listCardsOfPlayer(3);    // Should be unchanged [R5, Y4]
    cout << endl;

    // Test switching with empty hand (remove P3's cards first)
    game.removePlayer(3);
    game.addPlayer(3, "PlayerThreeEmpty"); // Re-add P3 with no cards
    game.switchHands(1, 3);       // Switch P1 [G10, B3] with P3 []
    game.listCardsOfPlayer(1);    // Should be empty []
    game.listCardsOfPlayer(3);    // Should have P1's cards [G10, B3]
    game.switchHands(1, 3);       // Switch back
    game.listCardsOfPlayer(1);    // Should have cards again [G10, B3]
    game.listCardsOfPlayer(3);    // Should be empty []
    cout << endl;


    // --- Play Tests ---
    cout << "--- Testing play ---" << endl;
    game.listDiscardPile();    // Boundary: Empty discard pile
    game.play(1, "G10");       // Valid first play
    game.listCardsOfPlayer(1); // Hand: [B3]
    game.listDiscardPile();    // Pile: [G10]
    cout << endl;

    game.play(2, "G6");        // Valid play (matches color G)
    game.listCardsOfPlayer(2); // Hand: [R1, G2]
    game.listDiscardPile();    // Pile: [G10, G6]
    cout << endl;

    game.play(1, "B3");        // Valid play (matches number 3 - assuming rules allow this, PDF is ambiguous on number match?) Let's assume matches number OR color. No, PDF says matches number OR color of LAST card. Last card is G6. B3 is INVALID. Should draw.
                               // Let's correct the sequence based on PDF rules (match color/num of LAST card)
    game.listDiscardPile();    // Pile: [G10, G6] Top card is G6
    game.play(1, "B3");        // Invalid play (B3 matches neither G nor 6). P1 should draw B7.
    game.listCardsOfPlayer(1); // Hand should be empty (B3 was played and removed), then [B7] drawn.
    game.listDiscardPile();    // Pile: [G10, G6, B3] (Card added even if invalid)
    game.listDrawPile();       // Draw pile: [Y8, R9]
    cout << endl;

    game.play(2, "R1");        // Invalid play (R1 matches neither B nor 3). P2 should draw Y8.
    game.listCardsOfPlayer(2); // Hand: [G2, Y8]
    game.listDiscardPile();    // Pile: [G10, G6, B3, R1]
    game.listDrawPile();       // Draw pile: [R9]
    cout << endl;

    game.play(1, "B7");        // Valid play (matches color B or number 7 - no, must match R1. Invalid). P1 draws R9.
    game.listCardsOfPlayer(1); // Hand: [R9]
    game.listDiscardPile();    // Pile: [G10, G6, B3, R1, B7]
    game.listDrawPile();       // Draw pile: [] - Should trigger game end message
    cout << endl;


    // Boundary: Test playing when draw pile is empty
    game.play(2, "G2");        // Invalid play (G2 matches neither B nor 7). No cards to draw.
    game.listCardsOfPlayer(2); // Hand: [Y8] (G2 removed)
    game.listDiscardPile();    // Pile: [G10, G6, B3, R1, B7, G2]
    cout << endl;

    // Test playing card player doesn't have
    game.play(1, "Y4");        // Error: P1 doesn't have Y4
    game.listCardsOfPlayer(1); // Hand: [R9] (Unchanged)
    cout << endl;

    // Test playing by non-existent player
    game.play(99, "R9");       // Error: Player doesn't exist
    cout << endl;

    // Test winning condition
    game.play(1, "R9");        // Valid play (R9 matches R or 9? No, must match G2. Invalid) No cards to draw.
    game.listCardsOfPlayer(1); // Hand: []
    game.listDiscardPile();    // Pile: [G10, G6, B3, R1, B7, G2, R9]
                               // Game should have ended here because P1 has 0 cards.

    cout << endl << "--- Test Complete ---" << endl;

    return 0;
}
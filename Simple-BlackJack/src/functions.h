/*
 -------------------------------------
 File:    functions.c
 Project: Simple BJ
 file description
 -------------------------------------
 Author:  Spencer Kelly
 Email:   Kell6733@mylaurier.ca
 Version  2024-09-30
 -------------------------------------
 */
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deck.h"

//structures
typedef struct {
	Card *cards; //cards in hand
	int num_cards; //number of cards in hand
	int value; //value of cards in hand
	int d; //1 if player doubled, 0 if not
	int bust; //1 if bust, 0 if not
} Player_Hand;

typedef struct {
	Card *cards; //cards in hand
	int num_cards; //number of cards in hand
	int value; //value of cards in hand
	int bust; // 1 == bust, 0 == hit
	int nat_bj; // 1 == bj, 0 == no bj
} Dealer_Hand;
// Constants.

// Prototypes.

// Start of the game, prompts the user for the starting cash amount.
// Returns the starting cash.
int game_start();

// Gets the player's bet amount.
// Parameter:
// - cash: The amount of cash the player has.
// Returns the remaining cash.
int bet(int cash);

// Deals initial cards: one to the player, one hidden to the dealer, another to the player, and one to the dealer.
// Updates the Player_Hand and Dealer_Hand with the dealt cards and their values.
// Parameters:
// - deck: The deck of cards.
// - player_hand: The player's hand to be updated.
// - dealer_hand: The dealer's hand to be updated.
void deal_initial_cards(Deck *deck, Player_Hand *player_hand,
		Dealer_Hand *dealer_hand);

// Offers the player the option to buy insurance when the dealer shows an ace.
// If the dealer has a 10-value card and the player bought insurance, the player receives their bet * 2.
// If insurance is not bought and the dealer has Blackjack, the player loses the hand.
// Parameters:
// - bet: The player's bet amount.
// - player_hand: The player's hand.
// - dealer_hand: The dealer's hand.
// - deck: The deck of cards.
// Returns the updated cash amount.
int insurance(int bet, Player_Hand *player_hand, Dealer_Hand *dealer_hand,
		Deck *deck);

// Offers the player choices: hit, stand, double, or split, each in its own function.
// Parameters:
// - deck: The deck of cards.
// - player_hand: The player's hand to be updated.
// Returns the updated player hand.
Player_Hand player_choice(Deck *deck, Player_Hand *player_hand, int cash,
		int bet);

// Checks for player bust
// - player_hand: The player's hand to be updated.
// Returns the updated player hand.
Player_Hand check_bust(Player_Hand *player_hand);

// Deals cards to the dealer until the hand value reaches 17-21 or busts.
// Parameters:
// - deck: The deck of cards.
// - dealer_hand: The dealer's hand to be updated.
// Returns the updated dealer hand.
Dealer_Hand card_to_dhand(Deck *deck, Dealer_Hand *dealer_hand);

// Deals a card to the player's hand.
// Parameters:
// - deck: The deck of cards.
// - player_hand: The player's hand to be updated.
// Returns the updated player hand.
Player_Hand card_to_phand(Deck *deck, Player_Hand *player_hand);

// Compares the dealer's and player's hand values to determine the winner.
// Parameters:
// - bet_amount: The player's bet amount.
// - player_hand: The player's hand.
// - dealer_hand: The dealer's hand.
// Returns the result of the comparison (win/loss).
int win(int bet_amount, Player_Hand *player_hand, Dealer_Hand *dealer_hand);

// Clears the dealer's and player's cards, number of cards, and values.
// Parameters:
// - player_hand: The player's hand to be cleared.
// - dealer_hand: The dealer's hand to be cleared.
void clear_hands(Player_Hand *player_hand, Dealer_Hand *dealer_hand);

// Prints all stats of the player's and dealer's hands.
// Parameters:
// - player_hand: The player's hand.
// - dealer_hand: The dealer's hand.
void print_all(Player_Hand *player_hand, Dealer_Hand *dealer_hand);

#endif /* FUNCTIONS_H_ */

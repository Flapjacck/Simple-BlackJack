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
} Player_Hand;

typedef struct {
	Card *cards; //cards in hand
	Card *hidden_card; //second card dealt to dealer is hidden
	int num_cards; //number of cards in hand
	int value; //value of cards in hand
} Dealer_Hand;
// Constants.

// Prototypes.
//start of game, asks user for starting cash amount
//return cash
int game_start();

//gets the players bet amount
//param cash - amount of cash player has
//return remaining - cash
int bet(int cash);

//deals a card to the player than to the dealer thats hidden, then another to the player, and finally one to the dealer.
//add the cards and value to the Player_Hand and Dealer_Hand respectively
void deal_initial_cards(Deck *deck, Player_Hand *player_hand,
		Dealer_Hand *dealer_hand);

//offers the player to buy insurance when dealer is showing a ace, which is same amount as the bet.
//if the dealer has a 10 and the player bought insurance then they receive their bet * 2.
//if insurance not bought player losses the hand
int insurance(int bet, Player_Hand *player_hand, Dealer_Hand *dealer_hand,
		Deck *deck);

//offers the player the choice to hit, stand, double, or split
//each choice in its own function
//returns player hand
Player_Hand player_choice(Deck *deck, Player_Hand *player_hand);

//deals cards to dealer till hand reaches 17-21 or busts
//returns dealer hand
Dealer_Hand dealer_choice(Deck *deck, Dealer_Hand *dealer_hand);

//deals a card to the players hand
Player_Hand card_to_phand(Deck *deck, Player_Hand *player_hand);

#endif /* FUNCTIONS_H_ */

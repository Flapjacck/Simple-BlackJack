/*
 -------------------------------------
 File:    deck.h
 Project: Simple-BJ
 file description
 -------------------------------------
 Author:  Spencer Kelly
 Email:   Kell6733@mylaurier.ca
 Version  2024-10-03
 -------------------------------------
 */
#ifndef DECK_H_
#define DECK_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants

// Struct for a card
typedef struct {
	const char *face;
	const char *suit;
	int value; //value of card
	int is_ace;  //checks
} Card;

typedef struct {
	Card *cards;
	int size;
} Deck;

// Prototypes

// Function to initialize multiple decks of cards.
// Parameters:
// - deck: Array to hold the cards.
// - num_decks: Number of decks to initialize.
void init_decks(Deck *deck, int num_decks);

// Function to print a deck of cards.
// Parameters:
// - deck: Array that holds the cards.
void print_deck(const Deck *deck);

// Function to shuffle a deck of cards.
// Parameters:
// - deck: Array of cards to shuffle.
void shuffle_deck(Deck *deck);

// Function to add a cut card randomly between half deck_size and full deck_size to the deck with a value of NULL.
// Parameters:
// - deck: Array of cards to shuffle.
void cut_card(Deck *deck);

// Function to get a card to deal, removes one from deck_size and checks for cut card.
// Parameters:
// - deck: Array of cards to print.
// Returns the dealt card.
Card deal_card(Deck *deck);

// Function to print a card.
// Parameters:
// - card: The card to print.
void print_card(const Card card);

#endif /* DECK_H_ */

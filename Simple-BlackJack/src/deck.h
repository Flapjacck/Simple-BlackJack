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
} Card;

// Prototypes
// Function to initialize multiple decks of cards
// decks: array to hold the cards
// num_decks: number of decks to initialize
void init_decks(Card decks[], int num_decks);

// Function to print a deck of cards
// deck: array of cards to print
// deck_size: number of cards in the deck
void print_deck(const Card deck[], int deck_size);

// Function to shuffle a deck of cards
// deck: array of cards to shuffle
// deck_size: number of cards in the deck
void shuffle_deck(Card deck[], int deck_size);

#endif /* DECK_H_ */

/*
 -------------------------------------
 File:    Deck.c
 Project: Simple-BJ
 file description
 -------------------------------------
 Author:  Spencer Kelly
 Email:   Kell6733@mylaurier.ca
 Version  2024-10-03
 -------------------------------------
 */
#include "deck.h"

#include <stdio.h>
#include <stdlib.h>

//constants
const char *cardFaces[] = { "Ace", "Two", "Three", "Four", "Five", "Six",
		"Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
const char *cardSuits[] = { "Spades", "Hearts", "Clubs", "Diamonds" };

//functions
void init_decks(Card decks[], int num_decks) {
	int deck_index = 0; // Index to track position in the decks array

	// Loop through each deck
	for (int d = 0; d < num_decks; d++) {
		// Loop through each face value
		for (int f = 0; f < 13; f++) {
			// Loop through each suit
			for (int s = 0; s < 4; s++) {
				// Assign face, suit, and value to each card
				decks[deck_index].face = cardFaces[f];
				decks[deck_index].suit = cardSuits[s];
				// Assign value (Ace=11, Two=2, ..., Ten=10, Jack=10, Queen=10, King=10)
				if (f == 0) {
					decks[deck_index].value = 11; // Ace
				} else if (f >= 9) {
					decks[deck_index].value = 10; // Jacks, Queens, and Kings
				} else {
					decks[deck_index].value = f + 1; // Two through Ten
				}
				deck_index++; // Move to the next card in the array
			}
		}
	}
}

void print_deck(const Card deck[], int deck_size) {
	// Loop through each card in the deck and print its details
	for (int i = 0; i < deck_size; i++) {
		printf("%s of %s (Value: %d)\n", deck[i].face, deck[i].suit,
				deck[i].value);
	}
}

void shuffle_deck(Card deck[], int deck_size) {
	srand(time(NULL));  // Seed the random number generator

	// Loop through the deck from the last card to the second card
	for (int i = deck_size - 1; i > 0; i--) {
		int j = rand() % (i + 1); // Get a random index from 0 to i

		// Swap deck[i] with deck[j]
		Card temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}
}

Card deal_card(Card deck[], int deck_size) {

	//Gets the front card to deal
	Card dealt_card = deck[0];

	//Checks if deck is empty, -1 from 'deck_size'
	if (deck_size > 0) {
		for (int i = 1; i < deck_size; i++) {
			deck[i - 1] = deck[i];
		}
		(deck_size)--;
	} else {
		printf("Whoops, there are no more cards left in the shoe!!!");
	}

	return dealt_card;
}

void print_card(Card card) {

	//prints card
	printf("%s of %s (Value: %d)\n", card.face, card.suit, card.value);

}


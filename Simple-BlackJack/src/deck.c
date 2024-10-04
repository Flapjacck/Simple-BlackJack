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
void init_decks(Deck *deck, int num_decks) {
	int total_cards = num_decks * 52;
	deck->cards = (Card*) malloc(total_cards * sizeof(Card));
	deck->size = total_cards;

	int deck_index = 0; // Index to track position in the decks array
	for (int d = 0; d < num_decks; d++) {
		for (int f = 0; f < 13; f++) {
			for (int s = 0; s < 4; s++) {
				deck->cards[deck_index].face = cardFaces[f];
				deck->cards[deck_index].suit = cardSuits[s];
				if (f == 0) {
					deck->cards[deck_index].value = 11; // Ace
				} else if (f >= 9) {
					deck->cards[deck_index].value = 10; // Jacks, Queens, and Kings
				} else {
					deck->cards[deck_index].value = f + 1; // Two through Ten
				}
				deck_index++; // Move to the next card in the array
			}
		}
	}
}

void print_deck(const Deck *deck) {
	for (int i = 0; i < deck->size; i++) {
		printf("%s of %s (Value: %d)\n", deck->cards[i].face,
				deck->cards[i].suit, deck->cards[i].value);
	}
}

void shuffle_deck(Deck *deck) {
	srand(time(NULL)); // Seed the random number generator
	for (int i = deck->size - 1; i > 0; i--) {
		int j = rand() % (i + 1); // Get a random index from 0 to i
		Card temp = deck->cards[i];
		deck->cards[i] = deck->cards[j];
		deck->cards[j] = temp;
	}
}

void cut_card(Deck *deck) {
	// Seed the random number generator
	srand(time(NULL));

	// Generate a random index to place the cut card
	int cut_index = rand() % (deck->size - ((deck->size - 3) / 2) + 1)
			+ (deck->size / 2);

	// Create a cut card with NULL values
	Card cut_card = { NULL, NULL, 0 };

	// Place the cut card at the random index
	deck->cards[cut_index] = cut_card;

	// Print the index of the cut card
	printf("**Cut card placed at index %d**\n", cut_index);
}

Card deal_card(Deck *deck) {
	Card dealt_card = deck->cards[0];
	// Check if the dealt card is the cut card
	if (dealt_card.face == NULL) {
		printf("Cut card reached!\n");
		exit(0);
	}
	// Shift all the cards to the left by one and decrement the size by 1
	if (deck->size > 0) {
		for (int i = 1; i < deck->size; i++) {
			deck->cards[i - 1] = deck->cards[i];
		}
		deck->size--;
	}

	return dealt_card;
}

void print_card(Card card) {
	printf("%s of %s (Value: %d)\n", card.face, card.suit, card.value);
}


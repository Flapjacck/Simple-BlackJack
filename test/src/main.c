/*
 -------------------------------------
 File:    main.c
 Project: test
 file description
 -------------------------------------
 Author:  Spencer Kelly
 ID:      169066733
 Email:   Kell6733@mylaurier.ca
 Version  2024-10-03
 -------------------------------------
 */
// deck of cards demonstration
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define CARDS 52

const char *face[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
		"Eight", "Nine", "Ten", "Jack", "Queen", "King" };

const char *suit[] = { "Spades", "Hearts", "Clubs", "Diamonds" };

// function to shuffle the deck
int Shuffle(int *deck) {
	int i, temp, card;

	printf("\nShuffling...\n\n");
	for (i = CARDS - 1; i > 0; i--) {
		card = rand() % i;
		temp = deck[i];
		deck[i] = deck[card];
		deck[card] = temp;

	}
	return 0;
}

// program entry point
int main(void) {
	int deck[CARDS];  // deck
	int card = 53;    // card
	int fac, sut;     // face and suit
	int i;            // counter
	char ch = 0;      // keyboard

	printf("The card dealer....\n\n");

	srand(time(NULL));

	//initialize the deck
	for (i = 0; i < CARDS; i++)
		deck[i] = i;

	// deal cards
	do {
		if (card >= CARDS)
			card = Shuffle(deck);

		// face and suit
		fac = deck[card] % 13;
		sut = deck[card] / 13;

		// display the card
		printf("%2d > %s of %s\t\t", card, face[fac], suit[sut]);
		card++;

		printf("(Enter to deal, Q to quit)\n");
		ch = getchar();
	} while (toupper(ch) != 'Q');
	return 0;
}


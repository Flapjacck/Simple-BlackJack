/*
 -------------------------------------
 File:    main.c
 Project: Simple BJ
 main file for game
 -------------------------------------
 Author:  Spencer Kelly
 Email:   Kell6733@mylaurier.ca
 Version  2024-09-30
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "deck.h"

//variables

int cash = 100;
int dealer_total = 0;
int player_total = 0;

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	//user input for number of decks
	int num_decks = 0;
	printf("Enter the number of decks to use: ");
	scanf("%d", &num_decks);
	Card decks[num_decks * 52];

	init_decks(decks, num_decks);
	printf("Multiple decks initialized:\n");
	print_deck(decks, num_decks * 52);

	shuffle_deck(decks, num_decks * 52);
	printf("\nShuffled decks:\n");
	print_deck(decks, num_decks * 52);

	return 0;
}

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

int dealer_total = 0;
int player_total = 0;

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	//game start
	int cash = game_start();
	printf("You have $%d\n", cash);
	//user input for number of decks
	int num_decks = 0;
	printf("Enter the number of decks to use: ");
	scanf("%d", &num_decks);
	Card decks[num_decks * 52];

	init_decks(decks, num_decks);
	shuffle_deck(decks, num_decks * 52);
	printf("**%d deck(s) initialized and shuffled**\n", num_decks);
	cut_card(decks, num_decks * 52);
	print_deck(decks, num_decks * 52);

	while (num_decks * 52 > 0) {
		Card dealt_card = deal_card(decks, num_decks * 52);
		printf("Dealt card: %s of %s (Value: %d)\n", dealt_card.face,
				dealt_card.suit, dealt_card.value);
	}
	while (cash > 0) {
		//bet
		int bet_amount = bet(cash);
		cash -= bet_amount;

		//deal cards to player and dealer

	}

	return 0;
}

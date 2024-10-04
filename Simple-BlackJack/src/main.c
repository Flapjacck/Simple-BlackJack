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
int cash;
Player_Hand player_hand;
Dealer_Hand dealer_hand;

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	//game start
	cash = game_start();
	printf("You have $%d\n", cash);

	// User input for number of decks
	int num_decks = 0;
	printf("Enter the number of decks to use: ");
	scanf("%d", &num_decks);

	// Initialize, shuffle deck and place cut card
	Deck deck;
	init_decks(&deck, num_decks);
	shuffle_deck(&deck);
	printf("**%d deck(s) initialized and shuffled**\n", num_decks);
	cut_card(&deck);

	bet(cash);

	deal_initial_cards(&deck, &player_hand, &dealer_hand);

	printf("Player's hand: %s of %s and %s of %s\nTotal: %d\n",
			player_hand.cards[0].face, player_hand.cards[0].suit,
			player_hand.cards[1].face, player_hand.cards[1].suit,
			player_hand.value);
	printf("Dealer's hand: %s of %s\nPossilble :%d\n",
			dealer_hand.cards[0].face, dealer_hand.cards[0].suit,
			dealer_hand.value);
	//print_deck(&deck);
	/*
	 while (deck.size > 0) {
	 Card dealt_card = deal_card(&deck);
	 printf("Dealt card: %s of %s (Value: %d)\n", dealt_card.face,
	 dealt_card.suit, dealt_card.value);
	 }
	 */

	choose();

	return 0;
}


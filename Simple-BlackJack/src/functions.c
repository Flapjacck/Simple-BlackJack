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
#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

//function to start the game
int game_start() {
	int cash = 0;
	printf("Welcome to Simple Blackjack!\n");
	printf("How much cash would you like to start with?:");
	scanf("%d", &cash);
	return cash;
}

//function to get the bet amount
int bet(int cash) {
	int bet = 0;
	printf("How much would you like to bet?:");
	scanf("%d", &bet);
	if (bet > cash) {
		printf("You don't have that much money!\n");
		return -1;
	}
	return bet;
}

void deal_initial_cards(Deck *deck, Player_Hand *player_hand,
		Dealer_Hand *dealer_hand) {
	// Initialize the player's hand
	player_hand->cards = malloc(2 * sizeof(Card));
	player_hand->num_cards = 0;
	player_hand->value = 0;

	// Initialize the dealer's hand
	dealer_hand->cards = malloc(2 * sizeof(Card));
	dealer_hand->hidden_card = malloc(2 * sizeof(Card));
	dealer_hand->num_cards = 0;
	dealer_hand->value = 0;

	// Deal the first card to the player
	Card first_player_card = deal_card(deck);
	player_hand->cards[player_hand->num_cards] = first_player_card;
	player_hand->value += first_player_card.value;
	player_hand->num_cards++;
	printf("Dealt player %s of %s...\n", first_player_card.face,
			first_player_card.suit);

	// Deal the first card to the dealer (hidden)
	Card first_dealer_card = deal_card(deck);
	dealer_hand->hidden_card[dealer_hand->num_cards] = first_dealer_card;
	dealer_hand->value += first_dealer_card.value;
	dealer_hand->num_cards++;
	printf("Dealt dealers hidden card...\n");

	// Deal the second card to the player
	Card second_player_card = deal_card(deck);
	player_hand->cards[player_hand->num_cards] = second_player_card;
	player_hand->value += second_player_card.value;
	player_hand->num_cards++;
	printf("Dealt player %s of %s...\n", second_player_card.face,
			second_player_card.suit);

	// Deal the second card to the dealer (visible)
	Card second_dealer_card = deal_card(deck);
	dealer_hand->cards[0] = second_dealer_card;
	dealer_hand->value += second_dealer_card.value;
	dealer_hand->num_cards++;
	printf("Dealt dealer %s of %s...\n", second_dealer_card.face,
			second_dealer_card.suit);

}

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
	printf("How much cash would you like to start with?: ");
	scanf("%d", &cash);
	return cash;
}

//function to get the bet amount
int bet(int cash) {
	int bet = 0;
	while (bet <= 0 || bet > cash) {
		printf("Enter your bet amount: ");
		scanf("%d", &bet);
		if (bet <= 0) {
			printf("You must bet more than $0\n");
		} else if (bet > cash) {
			printf("You cannot bet more than you have\n");
		}
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
	dealer_hand->num_cards = 0;
	dealer_hand->value = 0;

	// Deal the first card to the player
	card_to_phand(deck, player_hand);

	// Deal the first card to the dealer (hidden)
	Card first_dealer_card = deal_card(deck);
	dealer_hand->cards[dealer_hand->num_cards] = first_dealer_card;
	dealer_hand->value += first_dealer_card.value;
	dealer_hand->num_cards++;
	printf("Dealt dealers hidden card...\n");

	// Deal the second card to the player
	card_to_phand(deck, player_hand);

	// Deal the second card to the dealer (visible)
	Card dealt_card = deal_card(deck);
	dealer_hand->value += dealt_card.value;
	dealer_hand->cards[dealer_hand->num_cards] = dealt_card;
	dealer_hand->num_cards++;
	printf("Dealt dealer %s of %s...\n", dealt_card.face, dealt_card.suit);

}

//function to check if the player wants insurance
int insurance(int bet, Player_Hand *player_hand, Dealer_Hand *dealer_hand,
		Deck *deck) {
	char input;
	int ibet = bet / 2;
	printf("Would you like insurance? (y/n): ");
	scanf(" %c", &input);
	if (input == 'y') {
		if (dealer_hand->value == 21) {
			printf("Dealer has blackjack! You win insurance! \n");
			return ibet * 3;
		} else {
			printf("Dealer does not have blackjack! \n");
			return 0;
		}
	} else {
		return ibet;

	}
}

//function that allows the player to handle turn
Player_Hand player_choice(Deck *deck, Player_Hand *player_hand) {

	char choosing = '\0';
	while (choosing == '\0') {
		printf("Hit(h) / Stand(s) / Double(d) / Split(l): ");
		scanf(" %c", &choosing);

		if (choosing == 'h') {
			// Handle 'h'
			card_to_phand(deck, player_hand);
			if (player_hand->value > 21) {
				player_hand->value = -1;
				return *player_hand;
			}
		} else if (choosing == 's') {
			// Handle 's'
			printf("Player stands!\n");
			player_hand->num_cards = -1;
			return *player_hand;
		} else if (choosing == 'd' && player_hand->num_cards == 2) {
			// Handle 'd'
			return *player_hand;
		} else if (choosing == 'l' && player_hand->num_cards == 2) {
			// Handle 'l'
			return *player_hand;
		} else {
			printf("You Entered Something Incorrectly, try again -->\n");
			choosing = '\0';
		}
	}
	return *player_hand;
}

Dealer_Hand card_to_dhand(Deck *deck, Dealer_Hand *dealer_hand) {
	Card dealt_card = deal_card(deck);
	dealer_hand->value += dealt_card.value;
	dealer_hand->cards[dealer_hand->num_cards] = dealt_card;
	dealer_hand->num_cards++;
	printf("Dealt dealer %s of %s...\n", dealt_card.face, dealt_card.suit);
	printf("Dealer's total: %d\n", dealer_hand->value);
	if (dealer_hand->value > 21) {
		printf("Dealer busts!\n");
		dealer_hand->value = -1;
	}
	return *dealer_hand;
}

Player_Hand card_to_phand(Deck *deck, Player_Hand *player_hand) {
	Card dealt_card = deal_card(deck);
	player_hand->value += dealt_card.value;
	player_hand->cards[player_hand->num_cards] = dealt_card;
	player_hand->num_cards++;
	printf("Dealt player %s of %s...\n", dealt_card.face, dealt_card.suit);
	printf("Player's total: %d\n", player_hand->value);
	return *player_hand;
}

int win(int bet_amount, Player_Hand *player_hand, Dealer_Hand *dealer_hand) {
	if (player_hand->value == -1) {
		printf("You bust. You lose your main bet!\n");
		return -1;
	} else if (dealer_hand->value == -1) {
		printf("You win!\n");
		return 1;
	} else if (player_hand->value > dealer_hand->value) {
		printf("You have more than dealer. You win your main bet!\n");
		return 1;
	} else if (player_hand->value < dealer_hand->value) {
		printf("You have less than dealer. You lose your main bet!\n");
		return -1;
	} else {
		printf("You push your main bet!\n");
		return 0;
	}

}

void clear_hands(Player_Hand *player_hand, Dealer_Hand *dealer_hand) {
	player_hand->num_cards = 0;
	player_hand->value = 0;
	dealer_hand->num_cards = 0;
	dealer_hand->value = 0;
}


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
	//user input for cash
	printf("How much cash would you like to start with?: ");
	scanf("%d", &cash);
	return cash;
}

//function to get the bet amount
int bet(int cash) {
	int bet = 0;
	//user input for bet amount, make sure it is valid
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
	player_hand->cards = malloc(10 * sizeof(Card));
	player_hand->num_cards = 0;
	player_hand->value = 0;

	// Initialize the dealer's hand
	dealer_hand->cards = malloc(10 * sizeof(Card));
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
	char input = '\0';  // Initialize input to a value that is not 'y' or 'n'
	int ibet = bet / 2;

	while (input != 'y' && input != 'n') {
		printf("Would you like insurance? (y/n): ");
		scanf(" %c", &input);

		if (input == 'y') {
			//check if dealer has blackjack
			if (dealer_hand->value == 21) {
				printf("Dealer has blackjack! You win insurance! \n");
				dealer_hand->nat_bj = 1;
				return ibet * 3;
			} else {
				printf("Dealer does not have blackjack! \n");
				return 0;
			}
		} else if (input == 'n') {
			printf("You declined insurance\n");
			//check if dealer has blackjack
			if (dealer_hand->value == 21) {
				printf("Dealer has blackjack! You lose insurance! \n");
				dealer_hand->nat_bj = 1;
			}
			return ibet;
		} else {
			printf("You entered something incorrectly, try again\n");
			input = '\0';  // Reset input to ensure the loop continues
		}
	}
	return 0; // This return statement will never be reached, but it's good practice to include it
}

//function that allows the player to handle turn
Player_Hand player_choice(Deck *deck, Player_Hand *player_hand) {

	char choosing = '\0';
	while (choosing == '\0') {
		printf("Hit(h) / Stand(s) / Double(d) / Split(l): ");
		scanf(" %c", &choosing);

		if (choosing == 'h') {
			// Handle 'hit'
			card_to_phand(deck, player_hand);
		} else if (choosing == 's') {
			// Handle 'stand'
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
	// Deal the card to the dealer_hand
	Card dealt_card = deal_card(deck);
	dealer_hand->value += dealt_card.value;
	dealer_hand->cards[dealer_hand->num_cards] = dealt_card;
	dealer_hand->num_cards++;
	printf("Dealt dealer %s of %s...\n", dealt_card.face, dealt_card.suit);
	printf("Dealer's total: %d\n", dealer_hand->value);
	//check if dealer busts
	if (dealer_hand->value > 21) {
		printf("Dealer busts!\n");
		dealer_hand->bust = 1;
	}
	return *dealer_hand;
}

Player_Hand card_to_phand(Deck *deck, Player_Hand *player_hand) {
	// Deal the card to the player_hand
	Card dealt_card = deal_card(deck);
	player_hand->value += dealt_card.value;
	player_hand->cards[player_hand->num_cards] = dealt_card;
	player_hand->num_cards++;
	printf("Dealt player %s of %s...\n", dealt_card.face, dealt_card.suit);
	printf("Player's total: %d\n", player_hand->value);
	return *player_hand;
}

int win(int bet_amount, Player_Hand *player_hand, Dealer_Hand *dealer_hand) {
	//check who wins
	//player busts
	if (player_hand->value > 21) {
		printf("You bust. You lose your main bet!\n");
		return -1;
	}
	//dealer busts
	else if (dealer_hand->value > 21) {
		printf("You win!\n");
		return 1;
	}
	//compare values and determine winner
	else if (player_hand->value > dealer_hand->value) {
		printf("You have more than dealer. You win your main bet!\n");
		return 1;
	} else if (player_hand->value < dealer_hand->value) {
		printf("You have less than dealer. You lose your main bet!\n");
		return -1;
	}
	//push
	else {
		printf("You push your main bet!\n");
		return 0;
	}

}

void clear_hands(Player_Hand *player_hand, Dealer_Hand *dealer_hand) {
	//clear hands
	free(player_hand->cards);
	free(dealer_hand->cards);
	player_hand->num_cards = 0;
	player_hand->value = 0;
	dealer_hand->num_cards = 0;
	dealer_hand->value = 0;
	dealer_hand->bust = 0;
}

void print_all(Player_Hand *player_hand, Dealer_Hand *dealer_hand) {

	printf("Player's hand: ");
	for (int i = 0; i < player_hand->num_cards; i++) {
		printf("%s of %s, ", player_hand->cards[i].face,
				player_hand->cards[i].suit);
	}
	printf("\nTotal: %d\n", player_hand->value);

	printf("Dealer's hand: ");
	for (int i = 0; i < dealer_hand->num_cards; i++) {
		printf("%s of %s, ", dealer_hand->cards[i].face,
				dealer_hand->cards[i].suit);
	}
	printf("\nTotal: %d\n", dealer_hand->value);
	printf("Dealer's bust status: %d\n", dealer_hand->bust);
}


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
	//user input for cash
	printf("How much cash would you like to start with?: $");
	scanf("%d", &cash);
	return cash;
}

//function to get the bet amount
int bet(int cash) {
	int bet = 0;
	//user input for bet amount, make sure it is valid
	while (bet <= 0 || bet > cash) {
		printf("Enter your bet amount: $");
		scanf("%d", &bet);
		if (bet <= 0) {
			printf("You must bet more than $0\n");
		} else if (bet > cash) {
			printf("You cannot bet more than you have\n");
		}
	}
	return bet;
}

void deal_initial_cards(Deck *deck, Hand *player_hand, Hand *dealer_hand) {
	// Initialize the player's hand
	player_hand->cards = malloc(20 * sizeof(Card));
	player_hand->num_cards = 0;
	player_hand->value = 0;

	// Initialize the dealer's hand
	dealer_hand->cards = malloc(20 * sizeof(Card));
	dealer_hand->num_cards = 0;
	dealer_hand->value = 0;

	// Deal the first card to the player
	card_to_hand(deck, player_hand);

	// Deal the first card to the dealer (hidden)
	Card first_dealer_card = deal_card(deck);
	dealer_hand->cards[dealer_hand->num_cards] = first_dealer_card;
	dealer_hand->value += first_dealer_card.value;
	dealer_hand->num_cards++;
	dealer_hand->cards[0].hidden = 1;

	// Deal the second card to the player
	card_to_hand(deck, player_hand);

	// Deal the second card to the dealer (visible)
	card_to_hand(deck, dealer_hand);

	//Print cards
	print_hands(dealer_hand);
	print_hands(player_hand);

}

//function to check if the player wants insurance
int insurance(int bet, Hand *dealer_hand) {
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
void player_choice(Deck *deck, Hand *player_hand, int cash, int bet) {

	char choosing = '\0';
	while (choosing == '\0') {
		printf("\nHit(h) / Stand(s) / Double(d): ");
		scanf(" %c", &choosing);

		if (choosing == 'h') {
			// Handle 'hit'
			card_to_hand(deck, player_hand);

		} else if (choosing == 's') {
			// Handle 'stand'
			printf("Player stands!\n");
			player_hand->stop = 1;
			break;

		} else if (choosing == 'd' && player_hand->num_cards == 2
				&& cash >= bet) {
			// Handle 'double'
			printf("Player doubles!\n");
			card_to_hand(deck, player_hand);
			player_hand->d = 1;
			player_hand->stop = 1;
			break;

		} else if (choosing == 'l' && player_hand->num_cards == 2) {
			// Handle 'l'
			break;

		} else if (choosing == 'd' && player_hand->num_cards != 2) {
			printf("You cannot double down\n");
			choosing = '\0';

		} else if (choosing == 'l' && player_hand->num_cards != 2) {
			printf("You cannot split\n");
			choosing = '\0';

		} else {
			printf("You Entered Something Incorrectly, try again -->\n");
			choosing = '\0';

		}
	}
}

void check_bust(Hand *hand) {
	hand->bust = 0;
	hand->value = 0;
	int ace_count = 0;

	for (int i = 0; i < hand->num_cards; i++) {
		hand->value += hand->cards[i].value;
		if (hand->cards[i].is_ace) {
			ace_count++;
		}
	}

	while (hand->value > 21 && ace_count > 0) {
		hand->value -= 10;
		ace_count--;
	}

	if (hand->value >= 21) {
		hand->stop = 1;
	}
}

void card_to_hand(Deck *deck, Hand *hand) {
// Deal the card to the dealer_hand
	Card dealt_card = deal_card(deck);
	hand->value += dealt_card.value;
	hand->cards[hand->num_cards] = dealt_card;
	hand->num_cards++;
	printf("Dealt %s %s of %s...\n", hand->name, dealt_card.face,
			dealt_card.suit);
	check_bust(hand);

}

void print_hands(Hand *hand) {

	printf("\n%s's hand:\n ", hand->name);
	for (int a = 0; a < hand->num_cards; a++) {
		printf("-----    ");
	}
	printf("\n");
	for (int b = 0; b < hand->num_cards; b++) {
		if (hand->cards[b].hidden == 1) {
			printf("|     |  ");
		} else
			printf("|%s    |  ", hand->cards[b].sign);
	}
	printf("\n");
	for (int c = 0; c < hand->num_cards; c++) {
		if (hand->cards[c].hidden == 1) {
			printf("|  ?  |  ");
		} else
			printf("|%s   %s|  ", hand->cards[c].suit, hand->cards[c].suit);
	}
	printf("\n");
	for (int d = 0; d < hand->num_cards; d++) {
		if (hand->cards[d].hidden == 1) {
			printf("|     |  ");
		} else
			printf("|    %s|  ", hand->cards[d].sign);
	}
	printf("\n ");
	for (int e = 0; e < hand->num_cards; e++) {
		printf("-----    ");
	}
	if (hand->cards[0].hidden == 1) {
		printf("\nTotal: %d\n", hand->cards[1].value);
	} else {
		printf("\nTotal: %d\n", hand->value);
	}

}

int win(Hand *player_hand, Hand *dealer_hand) {
//check who wins
//player busts
	if (player_hand->value > 21) {
		printf("\nYou bust. You lose your main bet!\n");
		return -1;
	}
//dealer busts
	else if (dealer_hand->value > 21) {
		printf("\nDealer busts. You win!\n");
		return 1;
	}
//compare values and determine winner
	else if (player_hand->value > dealer_hand->value) {
		printf("\n%d > %d. You have more than dealer. You win your main bet!\n",
				player_hand->value, dealer_hand->value);
		return 1;
	} else if (player_hand->value < dealer_hand->value) {
		printf(
				"\n%d < %d. You have less than dealer. You lose your main bet!\n",
				player_hand->value, dealer_hand->value);
		return -1;
	}
//push
	else {
		printf("You push your main bet!\n");
		return 0;
	}

}

void clear_hands(Hand *player_hand, Hand *dealer_hand) {
//clear hands
	free(player_hand->cards);
	free(dealer_hand->cards);
	player_hand->num_cards = 0;
	player_hand->value = 0;
	player_hand->d = 0;
	player_hand->bust = 0;
	player_hand->stop = 0;
	dealer_hand->num_cards = 0;
	dealer_hand->value = 0;
	dealer_hand->bust = 0;
	dealer_hand->nat_bj = 0;
	dealer_hand->stop = 0;

}

void highest_cash(int cash, Score *score) {

	if (cash > score->hcash) {
		score->hcash = cash;
	}
}

void print_all(Hand *player_hand, Hand *dealer_hand) {

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


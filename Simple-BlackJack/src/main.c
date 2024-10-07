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
#include <string.h>

#include "functions.h"
#include "deck.h"

//variables
int cash;
int insurance_bet;
int bet_amount;
Hand player_hand;
Hand dealer_hand;

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	//game start
	cash = game_start();

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

	//sets player and dealer hand names
	strcpy(player_hand.name, "Player");
	strcpy(dealer_hand.name, "Dealer");

	//game loop
	while (cash > 0) {
		//reset hands
		clear_hands(&player_hand, &dealer_hand);

		//prints line break per round
		printf("--------------------------------------------------------\n");

		//print cash
		printf("You have $%d\n", cash);

		//run functions for bet and deal
		bet_amount = bet(cash);
		cash -= bet_amount;
		deal_initial_cards(&deck, &player_hand, &dealer_hand);

		//check if player has natural blackjack
		if (player_hand.value == 21) {
			printf("Player's hand: %s of %s and %s of %s\nTotal: %d\n",
					player_hand.cards[0].face, player_hand.cards[0].suit,
					player_hand.cards[1].face, player_hand.cards[1].suit,
					player_hand.value);
			printf("Blackjack! You win!\n");
			cash += bet_amount * 2.5;
		} else {
			//print player and dealer hands if no nat bj
			printf("Player's hand: %s of %s and %s of %s\nTotal: %d\n",
					player_hand.cards[0].face, player_hand.cards[0].suit,
					player_hand.cards[1].face, player_hand.cards[1].suit,
					player_hand.value);
			printf("Dealer's visible card: %s of %s\n",
					dealer_hand.cards[1].face, dealer_hand.cards[1].suit);

			//run insurance function
			if (dealer_hand.cards[1].value == 11) {
				cash -= (bet_amount / 2);
				insurance_bet = insurance(bet_amount, &player_hand,
						&dealer_hand, &deck);
				cash += insurance_bet;
			}

			//run functions for player
			while (player_hand.bust != 1 && player_hand.num_cards != -1
					&& dealer_hand.nat_bj != 1) {
				player_choice(&deck, &player_hand, cash, bet_amount);
				//double down
				if (player_hand.d == 1) {
					cash -= bet_amount;
					bet_amount *= 2;
				}
				printf("%s total: %d\n", player_hand.name, player_hand.value);
			}
			//run dealer function
			if (player_hand.num_cards == -1 && player_hand.bust != 1) {
				printf("Dealer turns over his hidden card\n");
				printf("%s of %s\nTotal: %d\n", dealer_hand.cards[0].face,
						dealer_hand.cards[0].suit, dealer_hand.value);
				while (dealer_hand.bust != 1 && dealer_hand.value < 17) {
					card_to_hand(&deck, &dealer_hand);
					check_bust(&dealer_hand);
				}
			}

			//run win function
			int win_result = win(bet_amount, &player_hand, &dealer_hand);
			if (win_result == 1) {
				cash += bet_amount * 2;
			} else if (win_result == -1) {
				//do nothing
			} else {
				cash += bet_amount;
			}

		}
		//reset hands
		bet_amount = 0;

	}

	//ran out of cash
	printf("You ran out of cash! Game over!\n");
	printf("--------------------------------------------------------\n");

	return 0;
}


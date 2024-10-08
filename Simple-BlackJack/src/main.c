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
#include <windows.h>

#include "functions.h"
#include "deck.h"
#include "score.h"

//variables
int cash;
int insurance_bet;
int bet_amount;
Hand player_hand;
Hand dealer_hand;
Score curr_score;
Score high_score;
char done;
char input;

int main() {
	setbuf(stdout, NULL);

	// Set console output to UTF-8
	SetConsoleOutputCP(CP_UTF8);

	//initialize done and Welcome print
	done = 'n';
	printf("--------------------------------------------------------\n");
	printf("Welcome to Simple Blackjack!\n");

	while (done != 'y') {

		//game start
		cash = game_start();
		curr_score.scash = cash;

		//read the file
		FILE *file;
		char *file_path = "simple-blackjack/score.txt";
		open_file(&file, file_path, "r");
		read_file_highscores(file, &high_score);

		// User input for number of decks
		int num_decks = 0;
		printf("\nEnter the number of decks to use: ");
		scanf("%d", &num_decks);

		// Initialize, shuffle deck and place cut card
		Deck deck;
		init_decks(&deck, num_decks);
		shuffle_deck(&deck);
		printf("\n**%d deck(s) initialized and shuffled**\n", num_decks);
		cut_card(&deck);

		//sets player and dealer hand names
		strcpy(player_hand.name, "Player");
		strcpy(dealer_hand.name, "Dealer");

		//game loop
		while (cash > 0) {
			//reset hands
			clear_hands(&player_hand, &dealer_hand);

			//prints line break per round
			printf(
					"--------------------------------------------------------\n");

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
				//run insurance function
				if (dealer_hand.cards[1].value == 11) {
					cash -= (bet_amount / 2);
					insurance_bet = insurance(bet_amount, &dealer_hand);
					cash += insurance_bet;
				}

				//run functions for player
				while (player_hand.bust != 1 && player_hand.stop != 1
						&& dealer_hand.nat_bj != 1) {
					player_choice(&deck, &player_hand, cash, bet_amount);

					//double down
					if (player_hand.d == 1) {
						cash -= bet_amount;
						bet_amount *= 2;
					}
					//Checks for 6 cards
					if (player_hand.num_cards == 6 && player_hand.bust != 1) {
						player_hand.stop = 1;
						dealer_hand.bust = 1;
					}
					if (player_hand.stop != 1) {
						print_hands(&dealer_hand);
						print_hands(&player_hand);
					}
				}
				//run dealer function
				if (player_hand.stop == 1) {
					printf("Dealer turns over his hidden card\n");
					dealer_hand.cards[0].hidden = 0;
					print_hands(&dealer_hand);
					print_hands(&player_hand);
					if (dealer_hand.value >= 17) {
						dealer_hand.stop = 1;
					}

					while (dealer_hand.stop != 1) {
						check_bust(&dealer_hand);
						card_to_hand(&deck, &dealer_hand);
						print_hands(&dealer_hand);
						print_hands(&player_hand);
						if (dealer_hand.value >= 17) {
							dealer_hand.stop = 1;
						}

					}
				}

				//run win function
				int win_result = win(&player_hand, &dealer_hand);
				if (win_result == 1) {
					cash += bet_amount * 2;
				} else if (win_result == -1) {
					//do nothing
				} else {
					cash += bet_amount;
				}
			}

			//Checks for the most cash amount player has
			highest_cash(cash, &curr_score);

			//reset hands
			bet_amount = 0;
			// Check for quit input
			if (cash != 0) {
				printf("Press 'q' to quit or any other key to continue: ");
				scanf(" %c", &input); //space before %c is important
				if (input == 'q' || input == 'Q') {
					done = 'y';
					break;
				}
			}
		}

		//write score
		open_file(&file, "score.txt", "a");
		write_file_score(file, &curr_score);
		close_file(file);

		//Asks to keep playing
		if (done == 'n' || done == 'N') {
			done = 'a';
			while (done != 'y' && done != 'n' && done != 'Y' && done != 'N') {
				printf("Would you like to stop playing?(y/n): ");
				scanf(" %c", &done);
			}
		}
		if (done == 'y' || done == 'Y' || input == 'q' || input == 'Q') {
			//Breaks Loop
			printf("\nThanks For Playing\n");
			printf(
					"--------------------------------------------------------\n");
		}

	}

	return 0;
}


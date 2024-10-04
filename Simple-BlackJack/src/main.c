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
int insurance_bet;
int bet_amount;
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

	//game loop
	while (cash > 0) {
		bet_amount = bet(cash);
		cash -= bet_amount;
		deal_initial_cards(&deck, &player_hand, &dealer_hand);

		if (player_hand.value == 21) {
			printf("Player's hand: %s of %s and %s of %s\nTotal: %d\n",
					player_hand.cards[0].face, player_hand.cards[0].suit,
					player_hand.cards[1].face, player_hand.cards[1].suit,
					player_hand.value);
			printf("Blackjack! You win!\n");
			cash += bet_amount * 2.5;
		} else {
			printf("Player's hand: %s of %s and %s of %s\nTotal: %d\n",
					player_hand.cards[0].face, player_hand.cards[0].suit,
					player_hand.cards[1].face, player_hand.cards[1].suit,
					player_hand.value);
			printf("Dealer's visible card: %s of %s\n",
					dealer_hand.cards[0].face, dealer_hand.cards[0].suit);

			//run insurance function
			if (dealer_hand.cards[0].value == 11) {
				insurance_bet = insurance(&deck, &player_hand, &dealer_hand,
						bet_amount);
				if (insurance_bet == 0) {
				} else if (insurance_bet == bet_amount) {
					printf("You lose your insurance bet!\n");
					cash -= insurance_bet;
					break;
				} else {
					printf("You win your insurance bet!\n");
					cash += insurance_bet;
					break;
				}
			}
			//run choose function for players turn
			player_choice(&deck, &player_hand);

			//run dealer function
			dealer_choice(&deck, &dealer_hand);

		}

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

		return 0;
	}
}


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

//variables
int deck[52] = { 0 };
int cash = 100;
int dealer_total = 0;
int player_total = 0;

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	printf("Welcome to Simple Blackjack!\n");
	printf("You have $%d\n", cash);

	while (cash > 0) {
		int bet_amount = bet(cash);

	}

	return 0;
}

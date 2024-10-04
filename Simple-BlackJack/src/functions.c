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

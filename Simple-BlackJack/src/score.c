/*
 -------------------------------------
 File:    score.c
 Project: Simple-BlackJack
 file description
 -------------------------------------
 Author:  Spencer Kelly
 ID:      169066733
 Email:   Kell6733@mylaurier.ca
 Version  2024-10-07
 -------------------------------------
 */

#include "score.h"

#include <stdio.h>
#include <stdlib.h>

void open_file(FILE **file, const char *filename, const char *mode) {
	*file = fopen(filename, mode);
	if (*file == NULL) {
		printf("Error opening file %s\n", filename);
		exit(1);
	}
}

void read_file_highscores(FILE *file, Score *high_score) {
	char line[100];
	Score temp_score;
	float max_yield = -1.0; // Initialize with a value lower than any possible yield

	while (fgets(line, sizeof(line), file) != NULL) {
		sscanf(line, "%d|%d|%f", &(temp_score.scash), &(temp_score.hcash),
				&(temp_score.percent_yield));
		if (temp_score.percent_yield > max_yield) {
			max_yield = temp_score.percent_yield;
			*high_score = temp_score; // Update the high score with the highest yield
		}
	}

	printf(
			"Your High Score Stats:\n\tStart $: %d | Highest $: %d | Yield Gain: %f\n",
			high_score->scash, high_score->hcash, high_score->percent_yield);
}

void write_file_score(FILE *file, Score *curr_score) {
	curr_score->percent_yield = (float) (curr_score->hcash - curr_score->scash)
			/ curr_score->scash; //calculate the yield based on the starting cash and ending

	fprintf(file, "\n%d|%d|%f", curr_score->scash, curr_score->hcash,
			curr_score->percent_yield);
}

void close_file(FILE *file) {
	fclose(file);
}

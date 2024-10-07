/*
 -------------------------------------
 File:    highscore.h
 Project: Simple-BlackJack
 file description
 -------------------------------------
 Author:  Spencer Kelly
 ID:      169066733
 Email:   Kell6733@mylaurier.ca
 Version  2024-10-07
 -------------------------------------
 */
#ifndef SCORE_H_
#define SCORE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int scash; // starting cash
	int hcash; // highest cash
	float percent_yield; // yield value
} Score;

// Opens a file with the given filename and mode.
// Parameters:
// - file: Pointer to the file pointer to be opened.
// - filename: Name of the file to open.
// - mode: Mode in which to open the file.
void open_file(FILE **file, const char *filename, const char *mode);

// Reads and prints all lines from the given file.
// Parameters:
// - file: File pointer from which to read lines.
void read_file_highscores(FILE *file, Score *highscore);

// Writes the given score to the file.
// Parameters:
// - file: File pointer to which the score will be written.
// - score: The score to write to the file.
void write_file_score(FILE *file, Score *curr_score);

// Closes the given file.
// Parameters:
// - file: File pointer to be closed.
void close_file(FILE *file);

#endif /* SCORE_H_ */


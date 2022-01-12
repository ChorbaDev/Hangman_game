//
// Created by omar on 12/01/2022.
//
#ifndef PRJ_HANGMANC_HELP_H
#define PRJ_HANGMANC_HELP_H

int randomNumber(int from, int to);
int openFile(const char * path);
char ** readFile(int fileDescriptor, int * wordsTotal);
void clearBuffer();
int promptString(char *buffer, int length);
int promptChar(char *buffer);
int promptInt(char *buffer, int length, int min, int max);
#endif //PRJ_HANGMANC_HELP_H
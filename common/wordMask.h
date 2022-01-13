//
// Created by omar on 12/01/2022.
//

#ifndef PRJ_HANGMANC_WORDMASK_H
#define PRJ_HANGMANC_WORDMASK_H
#include <stdbool.h>
#include <string.h>
void initBoolMask(bool *pInt, int l);
void initWordMask(char *pInt, int l);
void editBoolMask(char* character, bool *pInt, char *word);
void editWordMask(char *wmask, const bool *bmask, char character);
#endif //PRJ_HANGMANC_WORDMASK_H

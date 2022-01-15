#ifndef PRJ_HANGMANC_WORDMASK_H
#define PRJ_HANGMANC_WORDMASK_H
#include <stdbool.h>
#include <string.h>
void initBoolMask(bool *pInt, int l);
void initWordMask(char *pInt, int l);
void editBoolMask(char* character, bool *pInt, char *word);
void editWordMask(char *wmask, const bool *bmask, char character);
bool winningGame(bool *pInt,int len);
#endif //PRJ_HANGMANC_WORDMASK_H

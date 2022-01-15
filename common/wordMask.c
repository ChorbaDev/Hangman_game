//
// Created by omar on 12/01/2022.
//

#include "wordMask.h"
void initBoolMask(bool *pInt, int l) {
    for (int i=0; i < l; i++)
        pInt[i] = false;
}
void initWordMask(char *pInt, int l) {
    for (int i=0; i < l; i++)
        pInt[i] = '-';
}
void editBoolMask(char* character, bool *pInt, char *word) {
    char car=character[0];
    for(int k=0; k < strlen(word); ++k) {
        if (toupper(word[k]) == toupper(car)) {
            pInt[k] = 1;
        }
    }
}
void editWordMask(char *wmask, const bool *bmask, char character){

    for(int k=0; k < strlen(wmask); ++k) {
        if (bmask[k]==1 && wmask[k]=='-') {
            wmask[k]=character;
        }
    }
}
bool winningGame(bool *b,int len){
    for (int i=0;i< len;i++){
        if(b[i]==false) return false;
    }
    return true;
}
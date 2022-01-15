//
// Created by omar on 08/01/2022.
//
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>       // "Fuctions added to work with characters"
#include <stdio.h>       // "Standard Header (In/Out)"
#include <stdlib.h>      // "Standard Header"
#include <string.h>      // "Manipulate Strings"
#include <time.h>        // "Used the chronological time"
#include <sys/socket.h>

#include "stream.h"
#include "hangman.h"
#include "playerInfo.c"
#include "wordMask.c"
#include "drawHangman.c"
#include "style.h"
#define MAX_ERRORS 6

bool checkLetter(char i);

void displayHangman(int length, int fdSocket) {
    stream_t stream;
    char serStream[STREAM_SIZE];
    long bufSize;
    size_t serStreamSize;
    char wordMask[length];
    char errors[MAX_ERRORS]={};
    bool* boolMask= malloc(length*sizeof(bool));
    int loop=1;

    initWordMask( wordMask, length);
    initBoolMask(boolMask,length);
    while(loop){
        system("clear");
        //
        printf(FONT_BLUE "\n*--------------------- PENDU ---------------------*" FONT_DEFAULT);
        printf(FONT_YELLOW"\n           BIENVENUE DANS LA JEU DE PENDU!!!\n"FONT_DEFAULT);

        wrongGuess((int)strlen(errors));
        if(strlen(errors)==MAX_ERRORS){
            printf(FONT_RED"\n           Vous avez perdu :( !"FONT_DEFAULT);
            break;
        }
        printf("\nVotre mot est: ");
        for (int i = 0; i < length; i++) {
            printf(FONT_GREEN"%c", toupper(wordMask[i]));
        }
        printf(FONT_RED"\nErreurs : ");
        for (int i = 0; i < MAX_ERRORS; i++) {
            printf(FONT_RED" %c ", toupper(errors[i]));
        }
        printf(FONT_YELLOW"\nIl vous reste %lu essais ",MAX_ERRORS- strlen(errors));
        //
        char *c;
        int input = 0;
        printf(FONT_DEFAULT"\nDonner une lettre alphabitique : ");
        while (!input || input == 10 || existIn((char)input,errors) || !isalpha((char)input)){
            input = getchar();
        }

        char inputChar = (char) input;
        //
        stream.content = NULL;
        init_stream(&stream, VERIFY_LETTER);
        set_content(&stream, &inputChar);
        serStreamSize = serialize_stream(&stream, serStream);
        send(fdSocket, serStream, serStreamSize, 0); // send buffer to server
        bufSize = recv(fdSocket, serStream, STREAM_SIZE, 0);
        if (bufSize < 1)
        {
            loop = 0; // set the loop at false, this will make the client go back to the lobby
            continue; // go to the next iteration of this while loop
        }
        unserialize_stream(serStream, &stream);
        boolMask= ((bool *) serStream);
        editWordMask(wordMask, boolMask, inputChar);
        if(!strchr(wordMask,inputChar)){
            strncat(errors, &inputChar,1);
        }
        if(!strchr(wordMask,'-')){
            loop=0;
            potenceGagnant();
            printf(FONT_GREEN"\n           Bien jouée vous avez gagnée!\n"
                             "               Le mot est: "FONT_DEFAULT);
            for (int i = 0; i < length; i++) {
                printf(FONT_GREEN"%c",wordMask[i]);
            }

        }
    }

}

bool existIn(char car, char errors[]) {
 return  strchr(errors,car);
}

int openFile(const char *path) {
    int fileDescriptor = open(path, O_RDONLY);

    if (fileDescriptor == -1) {
        printf("Error while opening file\n");
        exit(-1);
    }

    return fileDescriptor;
}

char **readFile(int fileDescriptor, int *wordsTotal) {
    // Internal variables
    char temp = 0;
    int cursor = 0;
    ssize_t bytesRead;

    // Setting up pointers
    char **wordsList = malloc(20 * sizeof(char *));
    *wordsTotal = 0;

    // Reading inside file
    do {
        bytesRead = read(fileDescriptor, &temp, sizeof(char));

        if (bytesRead == -1) {
            // Error while reading file
            printf("Error while reading file\n");
            exit(-1);
        } else if (bytesRead >= sizeof(char)) {
            if (cursor == 0) {
                // Allocate some memory to catch the word
                wordsList[*wordsTotal] = (char *) malloc(sizeof(char) * 30);
            }

            if (temp == '\n') {
                // Finish the current word and update the word count
                wordsList[*wordsTotal][cursor] = '\0';

                // Reallocate unused memory
                wordsList[*wordsTotal] = (char *) realloc(wordsList[*wordsTotal], (cursor + 1) * sizeof(char));

                // Update the word count
                (*wordsTotal)++;

                // Reset the cursor
                cursor = 0;
            } else {
                // Write the letter and update the cursor
                wordsList[*wordsTotal][cursor++] = temp;
            }
        }
    } while (bytesRead >= sizeof(char));

    // Update the word count
    if (*wordsTotal > 0)
        (*wordsTotal)++;

    return wordsList;
}

int randomNumber(int from, int to) {
    return rand() % (to - from) + from;
}


gameConfigStruct initGame() {
    gameConfigStruct gameConfig = *(gameConfigStruct *) malloc(
            sizeof(gameConfigStruct)); // allocate the size of a gameConfigStruct
    for (int i = 0;i < PLAYERS_AMOUNT; i++) {
        gameConfig.players[i] = initInfo();
    }                                                // init every player of the array
    return gameConfig;
}
//#############################################



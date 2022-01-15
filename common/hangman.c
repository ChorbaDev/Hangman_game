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

        printf(FONT_BLUE "\n*--------------------- PENDU ---------------------*" FONT_DEFAULT);
        printf(FONT_YELLOW"\n           BIENVENUE DANS LA JEU DE PENDU!!!\n"FONT_DEFAULT);

        //display the errors that client made
        wrongGuess((int)strlen(errors));

        //if number of errors made equals max number of errors the client lose the game
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

        //display number of errors permitted left
        printf(FONT_YELLOW"\nIl vous reste %lu essais ",MAX_ERRORS- strlen(errors));

        //ask for a char
        int input = 0;
        printf(FONT_DEFAULT"\nDonner une lettre alphabitique : ");
        while (!input || input == 10 || existIn((char)input,errors) || !isalpha((char)input)){
            input = getchar();
        }

        char inputChar = (char) input;

        //send the letter to the server to verify it
        stream.content = NULL;
        init_stream(&stream, VERIFY_LETTER);
        set_content(&stream, &inputChar);
        serStreamSize = serialize_stream(&stream, serStream);
        send(fdSocket, serStream, serStreamSize, 0); // send buffer to server

        //receive the response as a bool array
        bufSize = recv(fdSocket, serStream, STREAM_SIZE, 0);
        if (bufSize < 1)
        {
            loop = 0; // set the loop at false, this will make the client go back to the lobby
            continue; // go to the next iteration of this while loop
        }
        unserialize_stream(serStream, &stream);
        boolMask= ((bool *) serStream);

        //edit the word mask (looks like this: -----) if the response is true
        editWordMask(wordMask, boolMask, inputChar);

        //add the letter to the errors array if the response is false
        if(!strchr(wordMask,inputChar)){
            strncat(errors, &inputChar,1);
        }

        //if word mask has no - left that means that the player won
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

gameConfigStruct initGame() {
    gameConfigStruct gameConfig = *(gameConfigStruct *) malloc(
            sizeof(gameConfigStruct)); // allocate the size of a gameConfigStruct
    for (int i = 0;i < PLAYERS_AMOUNT; i++) {
        gameConfig.players[i] = initInfo();
    }                                                // init every player of the array
    return gameConfig;
}



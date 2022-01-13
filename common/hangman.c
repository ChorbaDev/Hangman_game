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
#include "style.h"
#define MAX_ERRORS 7
void displayHangman(int length, int fdSocket) {
    stream_t stream;
    char serStream[STREAM_SIZE];
    long bufSize;
    size_t serStreamSize;
    char wordMask[length];
    char* errors=(char*)malloc(MAX_ERRORS*sizeof(char));
    bool* boolMask= malloc(length*sizeof(bool));
    int loop=1;
    initWordMask( wordMask, length);
    initBoolMask(boolMask,length);
    while(loop){
        system("clear");
        //
        wrongGuess((int)strlen(errors));
        printf(FONT_BLUE "\n*--------------------- PENDU ---------------------*" FONT_DEFAULT);
        printf(FONT_YELLOW"\n           BIENVENUE DANS LA JEU DE PENDU!!!"FONT_DEFAULT);
        printf("\nVotre mot est: ");
        for (int i = 0; i < length; i++) {
            printf(FONT_GREEN"%c",wordMask[i]);
        }
        printf(FONT_RED"\nErreurs : ");
        for (int i = 0; i < MAX_ERRORS; i++) {
            printf(FONT_RED" %c ", toupper(errors[i]));
        }
        //
        printf(FONT_DEFAULT"\nDonner une lettre : ");
        char *c;
        int input = 0;
        while (!input || input == 10)
            input = getchar();
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
            if(strlen(errors)==MAX_ERRORS){
                free(errors);
                loop=0;
            }
        }
        if(!strchr(wordMask,'-')){
            potenceGagnant();
            printf(FONT_GREEN"\n           Bien jouée vous avez gagnée!\n               Le mot est: %s\n"FONT_DEFAULT,wordMask);
            free(errors);
            loop=0;
        }
    }

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

char *getDashedWord(char *word) {
    int i = 0;

    // Get the word length
    size_t wordLength = strlen(word);

    // Allocate same memory to new dashed word
    char *dashedWord = malloc(wordLength * sizeof(char));

    // Dash the word
    for (i = 0; i < strlen(word); i++) {
        dashedWord[i] = '_';
    }

    return dashedWord;
}
/*
void runGame(char *word) {
    int gameRunning = 1, availableTries = 10, mistake = 0;
    char letterTyped = 0;

    char *dashedWord = getDashedWord(word);

    do {
        // Ask for a letter
        printf("Type a letter: ");
        scanf("%c", &letterTyped);

        // Check the answer by looping though the word
        int replacedLetters = checkAnswer(letterTyped, word, dashedWord);

        // Check this try's results
        if (replacedLetters == 0) {
            // No letter has been replaced: wrong answer
            mistake++;
            wrongGuess(mistake);
            availableTries--;

        } else {
            // Good guess, display the dashed word updated
            printf("Good guess!\n%s\n", dashedWord);
        }

        // Check the game state
        if (strcmp(dashedWord, word) == 0) {
            gagne();
            gameRunning = 0;
            printf("You win!");
        }

        if (availableTries == 0) {
            gameRunning = 0;
            printf("No more tries, you lose! The word was %s\n", word);
        }

    } while (gameRunning == 1);
}
*/
/// need to check the validity with the bool change from server to client
int checkAnswer(char letterTyped, char *word, char *dashedWord) {
    size_t wordLength = strlen(word);
    int replacedLetters = 0;

    // Check the answer by looping though the word
    for (int i = 0; i < wordLength; i++) {
        if (word[i] == letterTyped) {
            // The letter exists: does it need to be replaced?
            if (dashedWord[i] == '_') {
                // Replace the letter
                dashedWord[i] = letterTyped;
                replacedLetters++;
            }
        }
    }

    return replacedLetters;
}

gameConfigStruct initGame() {
    gameConfigStruct gameConfig = *(gameConfigStruct *) malloc(
            sizeof(gameConfigStruct)); // allocate the size of a gameConfigStruct
    for (int i = 0;
         i < PLAYERS_AMOUNT; i++)                                                 // init every player of the array
        gameConfig.players[i] = initInfo();

    return gameConfig;
}
//#############################################

void wrongGuess(int mistake) {
    switch (mistake) {
        case 0:
            //0 erreurs on doit juste print la potence
            Potence();
            for(int Cont = 0; Cont < 9; Cont++)
                printf("\n    │ \n    │ ");

            printf("\n ───┴───\n");
            break;
        case 1:
            //1 erreur donc tete
            Head();
            for(int Cont = 0; Cont < 6; Cont++)
                printf("\n    │ \n    │ ");

            printf("\n    │ \n ───┴───\n");
            break;
        case 2:
            //2 erreurs donc corps
            Body();
            break;
        case 3:
            //3 erreurs donc bras droit
            rArm();
            break;
        case 4:
            //4 erreurs donc bras gauche
            lArm();
            for(int Cont = 0; Cont < 4; Cont++)
                printf("\n    │ \n    │");

            printf("\n ───┴───\n");
            break;
        case 5:
            //5 erreurs donc jambe droite
            rLeg();
            break;
        case 6:
            //6 erreurs donc jambe gauche
            lLeg();
            perdu();
            break;
        default:
            //perdu
            lLeg();
    }
}
//##############################################################
void Potence(){
    printf("    ┌");

    for(int Cont = 0; Cont < 5; Cont++)
        printf("──────");

    printf("┐ \n    │ \t\t\t\t   │ \n    │ \t\t\t\t   │");
}
void Head(){
    Potence();
    printf("\n    │ \t\t\t       ┌───┴───┐");
    printf("\n    │ \t\t\t       │ ^   ^ │");
    printf("\n    │ \t\t\t       │   .   │");
    printf("\n    │ \t\t\t       │  ---  │");
    printf("\n    │ \t\t\t       └───┬───┘");
}
void Body(){
    Head();

    for(int Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t\t   │ \n    │ \t\t\t\t   │");

    printf("\n    │ \t\t\t\t   │");

    for(int Cont = 0; Cont < 4; Cont++)
        printf("\n    │ \n    │");

    printf("\n ───┴───\n");
}
void rArm(){
    Head();

    printf("\n    │ \t\t\t\t   │");
    printf("\n    │ \t\t\t       ┌───┤");
    for(int Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │");

    printf("\n    │ \t\t\t       ┼   │");

    for(int Cont = 0; Cont < 4; Cont++)
        printf("\n    │ \n    │");

    printf("\n ───┴───\n");
}
void lArm(){
    Head();

    printf("\n    │ \t\t\t\t   │");
    printf("\n    │ \t\t\t       ┌───┼───┐");

    for(int Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │   │");

    printf("\n    │ \t\t\t       ┼   │   ┼");
}

void rLeg(){
    lArm();

    printf("\n    │ \t\t\t          / \n    │ \t\t\t         /");
    printf("\n    │ \t\t\t        / \n    │ \t\t\t       /");
    printf("\n    │  \t\t\t      / \n    │ ");
    printf("\n    │ \n    │ \n ───┴───\n");
}

void lLeg(){
    Potence();

    printf("\n    │ \t\t\t       ┌───┴───┐");
    printf("\n    │ \t\t\t       │ x   x │");
    printf("\n    │ \t\t\t       │   .   │");
    printf("\n    │ \t\t\t       │   +   │");
    printf("\n    │ \t\t\t       └───┬───┘");
    printf("\n    │ \t\t\t\t└──┼──┘");
    printf("\n    │ \t\t\t       ┌───┼───┐");

    for(int Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │   │");

    printf("\n    │ \t\t\t       ┼   │   ┼");
    printf("\n    │ \t\t\t          / \\ \n    │ \t\t\t         /   \\");
    printf("\n    │ \t\t\t        /     \\ \n    │ \t\t\t       /       \\");
    printf("\n    │  \t\t\t      /         \\ \n    │ ");
    printf("\n    │ \n    │ \n ───┴───\n");
}

void perdu(){
    // affichage du mot et dire que le gars à perdu on lui propose de recommencer
}
void gagne(){
    // affichage du message de victoire
}
void potenceGagnant(){
    Potence();
    printf("\n    │ \t\t\t\t  /┴\\ \n    │ \t\t\t\t /   \\ \n    │ \t\t\t\t/     \\");
    printf("\n    │ \t\t\t       └───────┘");
    printf("\n    │ \t\t┌───────┐");
    printf("\n    │      ┬    │ ^   ^ │    ┬    ");
    printf("\n    │      │    │   .   │    │    ");
    printf("\n    │      \\    │ [___] │    /   ");
    printf("\n    │       \\   └───────┘   / ");
    printf("\n    │ \t     \\      │      / ");
    printf("\n    │ \t      \\─────│─────/ ");
    printf("\n    │ \t\t    │ \n    │ \t\t    │ \n    │ \t\t    │");
    printf("\n    │ \t\t   / \\ \n    │ \t\t  /   \\       ");
    printf("\n    │ \t\t /     \\ \n    │ \t\t/       \\     ");
    printf("\n ───┴───      ──┘       └──\n");
}
int Restart_Or_Exit() {
    int Cont;
    char Output;

    do {
        Output = getchar();

        if (Output == 'n' || Output == 'N') {
            system("clear");

            printf("\n\n   ┌");

            for (Cont = 0; Cont < 8; Cont++)
                printf("──────");

            printf("┐ \n   │");

            printf("\t\t Bien joué!! A bientot!!");

            printf("\t    │ \n   └");

            for (Cont = 0; Cont < 8; Cont++)
                printf("──────");

            printf("┘ \n\n\n\n");

            return 0;
        }

        if (Output == 'y' || Output == 'Y') {
            system("clear");
            return 10;
        }
    } while (Output != 'Y' && Output != 'y' && Output != 'N' && Output != 'n');
}


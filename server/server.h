//
// Created by omar on 08/01/2022.
//

#ifndef PRJ_HANGMANC_SERVER_H
#define PRJ_HANGMANC_SERVER_H
#include <netinet/in.h>
#include <stdbool.h>
#include "hangman.h"
#include "../common/stream.h"

typedef struct
{
    int communicationID;
    struct sockaddr_in connectedAddr;
    gameConfigStruct *concertConfig;
} connectionStruct;

void *connectionThread(void *);
void clientConnected(int, gameConfigStruct *);
void disconnectUser(int, stream_t *, char *);
int sendString(int, stream_t *, char *, char *, bool, const char *, ...);
void promptUser(int, stream_t *, char *, int);
#endif //PRJ_HANGMANC_SERVER_H

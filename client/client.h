//
// Created by omar on 08/01/2022.
//

#ifndef PRJ_HANGMANC_CLIENT_H
#define PRJ_HANGMANC_CLIENT_H

#include "../common/stream.h"

void connectedToServer(int);
void clearBuffer();
int promptString(char *, int);
int promptInt(char *, int, int, int);

void startGame(int, stream_t *, char *, char *);
void dashboardPanel(int, stream_t *, char *, char *);
#endif //PRJ_HANGMANC_CLIENT_H

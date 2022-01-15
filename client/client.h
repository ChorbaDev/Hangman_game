#ifndef PRJ_HANGMANC_CLIENT_H
#define PRJ_HANGMANC_CLIENT_H

#include "../common/stream.h"

void connectedToServer(int);
void startGame(int, stream_t *, char *, char *);
void dashboardPanel(int,int, stream_t *, char *, char *);
#endif //PRJ_HANGMANC_CLIENT_H

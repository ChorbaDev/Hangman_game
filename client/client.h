#ifndef PRJ_HANGMANC_CLIENT_H
#define PRJ_HANGMANC_CLIENT_H

#include "../common/Stream/stream.h"

void connectedToServer(int);
void startGame(int, stream_t *, char *);
void dashboardPanel(int,int, stream_t *, char *);

#endif //PRJ_HANGMANC_CLIENT_H

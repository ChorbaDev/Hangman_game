#include <stdlib.h>
#include "playerInfo.h"
#include "help.c"
/**
 * Initialize a seatStruct instance
 * @return the seat
 */
infoStruct initInfo()
{
    infoStruct info=*(infoStruct*) malloc(sizeof(infoStruct)) ; // allocate the size of a infoStruct
    info.wins=0;
    info.connectionID=0;
    return info;
}
int existAt(int id, infoStruct players[]){
    for(int i=0;i<PLAYERS_AMOUNT;i++){
        if(players[i].connectionID==id)
            return i;
    }
    return -1;
}


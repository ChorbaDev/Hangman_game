//
// Created by omar on 08/01/2022.
//

#include <stdlib.h>
#include "playerInfo.h"
#include "help.c"
/**
 * Initialize a seatStruct instance
 * @return the seat
 */
infoStruct initInfo()
{
    infoStruct info = *(infoStruct *)malloc(sizeof(infoStruct)); // allocate the size of a seatStruct
    return info;
}


/**
 * Generate a code for a buffer
 * @param code the buffer that will contain the code string
 */
void generateCode(char *code)
{
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        code[i] = randomNumber(48, 57); // 48 is '0' and 57 is '9'
    }
    code[CODE_LENGTH] = '\0'; // set the end of the string
}


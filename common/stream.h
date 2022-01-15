//
// Created by omar on 08/01/2022.
//

#ifndef PRJ_HANGMANC_STREAM_H
#define PRJ_HANGMANC_STREAM_H

#include <stdint.h>
#include <stdlib.h>

#define PORT 6000
#define BUFFER_SIZE 1024
#define STREAM_SIZE BUFFER_SIZE + 128

typedef struct
{
    void *content;
    uint8_t type;
} stream_t;

enum
{
    INT,                           //? content : int
    SEND_DASHBOARD,
    ASK_FOR_DASHBOARD,
    SEND_HANGMAN,
    ASK_FOR_LENGTH,
    ASK_FOR_NBCLIENTS,
    ASK_FOR_ID,
    SEND_ID,
    SEND_MASK,
    VERIFY_LETTER,
    SEND_LENGTH,
    ERROR,                         //? content : NULL
    SUCCESS,                       //? content : NULL
    END_CONNECTION,                //? content : NULL
};

stream_t create_stream();
void init_stream(stream_t *, uint8_t);
void set_content(stream_t *, void *);
void destroy_stream(stream_t *);

size_t serialize_stream(stream_t *, void *);
void unserialize_stream(void *, stream_t *);

#endif //PRJ_HANGMANC_STREAM_H

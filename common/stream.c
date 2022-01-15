//
// Created by omar on 09/01/2022.
//

#include <string.h>
#include <stdbool.h>
#include "stream.h"

/**
 * Create a stream, initialize it, and return it
 * @return the stream
 */
stream_t create_stream()
{
    stream_t s;
    s.content = NULL;
    s.type = -1;

    return s;
}

/**
 * Reinitialize a stream with a type, and the content set to null
 * @param s the stream to reset
 * @param type the new type
 */
void init_stream(stream_t *s, uint8_t type)
{
    if (s->content != NULL) // free content allocation if not NULL
        free(s->content);
    s->content = NULL;
    s->type = type;
}

/**
 * Se the content of a stream
 * @param s the stream
 * @param content the new content
 */
void set_content(stream_t *s, void *content)
{
    if (s->content != NULL) // free content allocation if not NULL
        free(s->content);
    char * value;
    size_t len;
    switch (s->type)
    {
        case VERIFY_LETTER:
        case SEND_HANGMAN:
            s->content= malloc(strlen((char *)content)*sizeof(char));
            memcpy(s->content, (char *)content, strlen((char *)content)+1);
            break;
        case SEND_LENGTH:
            sprintf(value,"%lu", strlen((char *)content));
            s->content = malloc(sizeof(strlen(value)));
            memcpy(s->content, value, (int)sizeof(content));
            break;
        case SEND_ID:
        case INT:
            s->content = malloc(sizeof(int8_t));
            memcpy(s->content, content, 1);
            break;
        case SEND_DASHBOARD:
            s->content = malloc(PLAYERS_AMOUNT * sizeof(infoStruct)); // allocate the memory for the array
            memcpy(s->content, content, PLAYERS_AMOUNT * sizeof(infoStruct));        // copy content
            break;
        case SEND_MASK:
            s->content = malloc(sizeof(content) * sizeof(bool)); // allocate the memory for the array
            memcpy(s->content, content, sizeof (content));        // copy content
            break;
        default:
            s->content = NULL;
    }
}
void set_content_mask(stream_t *s, void *content,int length){
    s->content = malloc(length*sizeof(bool)); // allocate the memory for the array
    memcpy(s->content, content, length);        // copy content
}
/**
 * Free the memory used by the content of a stream
 * @param s the stream
 */
void destroy_stream(stream_t *s)
{
    if (s->content != NULL) // free content allocation if not NULL
        free(s->content);
}

/**
 * Serialize a stream into a buffer
 * @param s the stream
 * @param buffer the buffer to fill in
 * @return the size of the buffer
 */
size_t serialize_stream(stream_t *s, void *buffer)
{
    *((uint8_t *)buffer) = s->type;
    buffer += sizeof(uint8_t); // move in the buffer of the size of the type
    size_t len;
    switch (s->type)
    {
        // if content is NULL
        case END_CONNECTION:
        case ERROR:
        case ASK_FOR_LENGTH:
        case ASK_FOR_DASHBOARD:
        case ASK_FOR_NBCLIENTS:
        case ASK_FOR_ID:
            return sizeof(uint8_t);
        case SUCCESS:
            buffer += sizeof(uint8_t);
            len = strlen((char *)s->content);
            *((uint64_t *)buffer) = len;
            buffer += sizeof(uint64_t);
            memcpy(buffer,s->content , len);               // copy content
            return sizeof(uint8_t) + sizeof(uint64_t) + len;
            // if content is an int
        case VERIFY_LETTER:
        case SEND_LENGTH:
        case INT:
            memcpy(buffer, s->content, 1); // copy the int
            return sizeof(uint8_t) + sizeof(uint8_t);
        case SEND_ID:
            memcpy(buffer, s->content, 1); // copy the int
            return sizeof(uint8_t) + sizeof(char);
        case SEND_DASHBOARD:
            memcpy(buffer, s->content, sizeof(infoStruct)*PLAYERS_AMOUNT); // copy the array
            return sizeof(uint8_t) + sizeof(infoStruct)*PLAYERS_AMOUNT;
        case SEND_MASK:
            memcpy(buffer, s->content, sizeof(s->content) ); // copy the array
            return sizeof(uint8_t) + sizeof(s->content);
        default:
            return 0;
    }
}

/**
 * Unserialize a buffer into a stream
 * @param buffer the buffer
 * @param s the stream to fill in
 */
void unserialize_stream(void *buffer, stream_t *s)
{
    init_stream(s, *((uint8_t *)buffer)); // re init the stream
    buffer += sizeof(uint8_t); // move in the buffer of the size of the type
    size_t len;
    switch (s->type)
    {
        // if content is an int
        case VERIFY_LETTER:
        case SEND_LENGTH:
        case INT:
            s->content = malloc(sizeof(buffer)); // allocate the size of an int
            memcpy(s->content, buffer, (int)sizeof(buffer));       // copy the int
            break;
        case SUCCESS:
            len =  strlen((char *)buffer);                // get the length of the string
           // buffer += sizeof(uint64_t);                    // move is the buffer
            s->content = malloc((len + 1) * sizeof(char)); // allocate the size of the string
            memcpy(s->content, buffer, len);               // copy content
            ((char *)s->content)[len] = '\0';              // set the last char as '\0' to end the string
            break;
        case SEND_DASHBOARD:
            s->content = malloc(sizeof(infoStruct)*PLAYERS_AMOUNT); // allocate the size of an int
            memcpy(s->content, buffer,sizeof(infoStruct)*PLAYERS_AMOUNT );       // copy the int
            break;
        case SEND_MASK:
            s->content = malloc(sizeof(s->content)); // allocate the size of the array
            memcpy(buffer, s->content, sizeof(s->content) ); // copy the array
            break;
        default:
            break;
    }
}
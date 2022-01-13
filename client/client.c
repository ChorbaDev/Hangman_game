//
// Created by omar on 08/01/2022.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h> // for infinite parameters

#include "client.h"
#include "../common/style.h"
#include "../common/hangman.c"
#include "../common/stream.c"


#define ADDRESS "127.0.0.1"

int main(){
    // Get the socket
    int fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (fdSocket < 0)
    {
        printf(FONT_RED "Incorrect socket\n" FONT_DEFAULT);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverCoords;
    memset(&serverCoords, 0x00, sizeof(struct sockaddr_in)); // allocate memory
    serverCoords.sin_family = PF_INET;                       // Set protocal family
    inet_aton(ADDRESS, &serverCoords.sin_addr);              // put server address to our struct
    serverCoords.sin_port = htons(PORT);                     // set address port

    if (connect(fdSocket, (struct sockaddr *)&serverCoords, sizeof(serverCoords)) == -1)
    {
        printf(FONT_RED "Connection failed\n" FONT_DEFAULT);
        exit(EXIT_FAILURE);
    }
    printf(FONT_GREEN "\n \nConnected to %s:%d\n \n" FONT_DEFAULT, ADDRESS, PORT);
    // call the function that manage the connection
    connectedToServer(fdSocket);

    close(fdSocket);
    return EXIT_SUCCESS;
}
/**
 * Function that manage the client connection
 * @param fdSocket the socket of the communication
 */
void connectedToServer(int fdSocket)
{
    stream_t stream = create_stream(); // received stream

    size_t serStreamSize;        // variable that will contain the size of setStream
    char serStream[STREAM_SIZE]; // serialized stream
    char string[BUFFER_SIZE];    // buffer for strings
    int8_t promptedInt;          // integer that is used when an integer is prompted to the client
    bool loop = 1;               // loop that let the client do something until he leave

    do
    {
        printf(FONT_BLUE "\n*--------------------- BIENVENUE ---------------------*" FONT_DEFAULT "\n" FONT_RED "0/" FONT_DEFAULT
        " Quitter\n"
        "1/ Commencer une partie\n"
        "2/ Tableau de bord\n"
        "Choix : ");
        promptedInt = promptInt(string, BUFFER_SIZE, 0, 2); // prompt the client an int (choice)

        switch (promptedInt)
        {
            case 0:
                loop = 0;                             // set the loop at false, will disconnect the client
                init_stream(&stream, END_CONNECTION); // tell the server that this client left
                serStreamSize = serialize_stream(&stream, serStream);
                send(fdSocket, serStream, serStreamSize, 0); // send buffer to server
                break;
            case 1:
                startGame(fdSocket, &stream, string, serStream);
                break;
            case 2:
                dashboardPanel(fdSocket, &stream, string, serStream);
                break;
        }
    } while (loop == 1);

    destroy_stream(&stream);
}
/**
 * Function that starts a game
 * @param communicationID the id of the communication
 * @param stream the stream to send
 * @param string the buffer that contain the string
 * @param serStream the buffer that will contain the serialized stream
 */
int word_length;
void startGame(int fdSocket, stream_t *stream, char *string, char *serStream)
{
    size_t serStreamSize; // variable that will contain the size of setStream
    int bufSize;          // contain the return of recv()
    bool loop = 1;
    do{
        init_stream(stream, ASK_FOR_WORD); // ask the server for a word
        serStreamSize = serialize_stream(stream, serStream);
        send(fdSocket, serStream, serStreamSize, 0); // send buffer to server
        bufSize = recv(fdSocket, serStream, STREAM_SIZE, 0);
        if (bufSize < 1)
        {
            loop = 0; // set the loop at false, this will make the client go back to the lobby
            continue; // go to the next iteration of this while loop
        }
        char* word= ((char *) serStream);
        puts(word);
        word_length= atoi(&word[strlen(word)-1]);
        displayHangman(word_length,fdSocket);
        break;
    }while(loop);
}

/**
 * Function that shows the dashboard
 * @param communicationID the id of the communication
 * @param stream the stream to send
 * @param string the buffer that contain the string
 * @param serStream the buffer that will contain the serialized stream
 */
void dashboardPanel(int fdSocket, stream_t *stream, char *string, char *serStream)
{

}



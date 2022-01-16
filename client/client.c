#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include "client.h"
#include "../common/style.h"
#include "../common/Hangman/hangman.c"
#include "../common/Stream/stream.c"


#define ADDRESS "127.0.0.1"

int main(){
    system("clear");
    // Get the socket
    int fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (fdSocket < 0)
    {
        printf(FONT_RED "Incorrect socket\n" FONT_DEFAULT);
        exit(EXIT_FAILURE);
    }

    //set server coords
    struct sockaddr_in serverCoords;
    memset(&serverCoords, 0x00, sizeof(struct sockaddr_in)); // allocate memory
    serverCoords.sin_family = PF_INET;                               // Set protocal family
    inet_aton(ADDRESS, &serverCoords.sin_addr);              // put server address to our struct
    serverCoords.sin_port = htons(PORT);                    // set address port

    //connect to the server
    if (connect(fdSocket, (struct sockaddr *)&serverCoords, sizeof(serverCoords)) == -1)
    {
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
    int bufSize;

    do
    {
        //system("clear");
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
                startGame(fdSocket, &stream, serStream);
                break;
            case 2:
                //send the request ID to the server so we can color it in green in the
                init_stream(&stream, ASK_FOR_ID);
                serStreamSize = serialize_stream(&stream, serStream);
                send(fdSocket, serStream, serStreamSize, 0); // send buffer to server
                bufSize = recv(fdSocket, serStream, STREAM_SIZE, 0);
                unserialize_stream(serStream, &stream);
                int communicationId=0;
                char* id= ((char *) serStream);
                communicationId= atoi(&id[strlen(id)-1]);
                dashboardPanel(fdSocket,communicationId, &stream, serStream);
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
void startGame(int fdSocket, stream_t *stream, char *serStream)
{
    size_t serStreamSize; // variable that will contain the size of setStream
    int bufSize;          // contain the return of recv()

        init_stream(stream, ASK_FOR_LENGTH); // ask the server for the length of the word
        serStreamSize = serialize_stream(stream, serStream);
        send(fdSocket, serStream, serStreamSize, 0); // send buffer to server
        //receiving the length
        bufSize = recv(fdSocket, serStream, STREAM_SIZE, 0);
        if (bufSize < 1)
        {
            exit(EXIT_FAILURE);
        }
        char* word= ((char *) serStream);
        word_length= atoi(&word[strlen(word)-1]);
        //function that displays hangman
        displayHangman(word_length,fdSocket);
}
int compareFn (const void * a, const void * b) {
    int c=((infoStruct *)a)->wins,d=((infoStruct *)b)->wins;
    return ( d - c );
}
/**
 * Function that shows the dashboard
 * @param communicationID the id of the communication
 * @param stream the stream to send
 * @param string the buffer that contain the string
 * @param serStream the buffer that will contain the serialized stream
 */
void dashboardPanel(int fdSocket,int communicationID, stream_t *stream, char *serStream)
{
    size_t serStreamSize;
    int bufSize;

        init_stream(stream, ASK_FOR_NBCLIENTS); // ask the server for the total number of clients
        serStreamSize = serialize_stream(stream, serStream);
        send(fdSocket, serStream, serStreamSize, 0); // send buffer to server

        bufSize = recv(fdSocket, serStream, STREAM_SIZE, 0);
        if (bufSize >= 0)
        {
            char* word= ((char *) serStream);
            int len= atoi(&word[strlen(word)-1]);

            //ask for players info (id,score)
            init_stream(stream, ASK_FOR_DASHBOARD);
            serStreamSize = serialize_stream(stream, serStream);
            send(fdSocket, serStream, serStreamSize, 0); // send buffer to server
            bufSize = recv(fdSocket, serStream, STREAM_SIZE, 0);
            if (bufSize >= 0)
            {
                unserialize_stream(serStream, stream);
                infoStruct* players= (infoStruct*) stream->content;
                qsort(players,len,sizeof(infoStruct),compareFn );
                printf(FONT_BLUE "\n*--------------------- TABLEAU DE BORD ---------------------*\n" FONT_DEFAULT);
                puts("┌──────────────────────────────┐");
                puts("│      ID       │     Score    │");
                puts("└──────────────────────────────┘");
                puts("┌──────────────────────────────┐");
                for (int i = 0; i <len; ++i) {
                    if(players[i].connectionID==communicationID)
                        printf("│" FONT_GREEN "       %d"FONT_DEFAULT"       │"FONT_GREEN"       %d      "FONT_DEFAULT"│\n",players[i].connectionID,players[i].wins);
                    else
                        printf("│       %d       │       %d      │\n",players[i].connectionID,players[i].wins);
                }
                puts("└──────────────────────────────┘\n");
            }
        }
}



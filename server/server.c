//
// Created by omar on 08/01/2022.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <pthread.h>
#include <stdarg.h> // for infinite parameters
#include <time.h>   // for random functions
#include <semaphore.h>

#include "server.h"
#include "../common/style.h"
#include "../common/hangman.c"
#include "../common/stream.c"

sem_t semaphore;
bool loop = 1;
/**
 * Main function that create the socket, create the concert, and manage client connections
 * @return exit status (EXIT_FAILURE || EXIT_SUCCESS)
 */
int main(int argc, char *argv[]){
    printf("Waiting...\n");

    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        printf(FONT_RED "Incorrect socket\n" FONT_DEFAULT);
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));   // allocate memory
    serverAddr.sin_family = PF_INET;                                 // Set protocal family
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);          // set address
    serverAddr.sin_port = htons(PORT);                      // set address port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr,
             sizeof(serverAddr)) == -1)
    {
        printf(FONT_RED "Bind error, PORT may already be in use.\n" FONT_DEFAULT);
        exit(EXIT_FAILURE);
    }
    if (listen(serverSocket, 5) == -1)
    {
        printf(FONT_RED "Listen error.\n" FONT_DEFAULT);
        exit(EXIT_FAILURE);
    }
    //? init the hangman structure that will contain every player
    gameConfigStruct concertConfig = initGame();
    sem_init(&semaphore, PTHREAD_PROCESS_SHARED, 1);

    //? set the randomness of the program
    srand((unsigned int)time(NULL));

// Main loop
    int sockaddr_in_size = sizeof(struct sockaddr_in);
    while (loop)
    {
        connectionStruct myConnectionStruct;
        myConnectionStruct.gameConfig = &concertConfig; // set the address of the concertConfig variable

        //? waiting for a connection to come
        if ((myConnectionStruct.communicationID = accept(serverSocket, (struct sockaddr *)&myConnectionStruct.connectedAddr,
                                                         &sockaddr_in_size)) != -1)
        {
            //? create the thread that will manage the connection
            pthread_t thread;
            int threadReturn = pthread_create(&thread, NULL, connectionThread, (void *)&myConnectionStruct);
        }
        else
        {
            printf(FONT_RED "Connection acceptation error\n" FONT_DEFAULT);
        }
    }
    close(serverSocket);
    sem_destroy(&semaphore);

    return EXIT_SUCCESS;
}
/**
 * The thread that will manage the connection
 * @param args instance of connectionStruct as (void *)
 */
void *connectionThread(void *args)
{
    connectionStruct connection = *(connectionStruct *)args;
    printf("%d | Connected client : %s\n", connection.communicationID, inet_ntoa(connection.connectedAddr.sin_addr)); //? display client IP

    // function that will manage the client
    clientConnected(connection.communicationID, connection.gameConfig);

    close(connection.communicationID);
    pthread_exit(NULL);
}
void clientConnected(int communicationID, gameConfigStruct *gameConfig)
{
    stream_t stream = create_stream(); // stream that is used with this client
    char serStream[STREAM_SIZE];       // serialized stream
    size_t serStreamSize;              // buffer that contain the serialized stream
    char code[CODE_LENGTH + 1];      // string for the code
    char* word;
    int wordsTotal = 0, wordsFileDescriptor;
    char ** wordsList;
    while (loop)
    {
        // wait to receive a message from the client
        int bufSize = recv(communicationID, serStream, STREAM_SIZE, 0);
        if (bufSize < 1)
        {
            loop = 0;
            continue;
        }
        unserialize_stream(serStream, &stream);
        //the game
        switch (stream.type)
        {
            // stop the loop that manage the client
            case END_CONNECTION:
                loop = 0;
                break;
            case ASK_FOR_WORD:
                init_stream(&stream,SEND_LENGTH);
                wordsFileDescriptor = openFile("hangmanwords.txt");
                wordsList = readFile(wordsFileDescriptor, &wordsTotal);
                int random = randomInt(0, wordsTotal);
                close(wordsFileDescriptor);
                printf("Mot choisi: %s",wordsList[random]);
                set_content(&stream, (void *) strlen(wordsList[random]));
                serStreamSize = serialize_stream(&stream, serStream);
                send(communicationID, serStream, serStreamSize, 0); // send buffer to client
                break;
            case VERIFY_LETTER:
                puts(stream.content);
                break;
            default:
                break;
        }
    }
    printf("%d | Client disconnected\n", communicationID);
    destroy_stream(&stream);
}
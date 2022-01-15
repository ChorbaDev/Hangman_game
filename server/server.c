#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

#include "server.h"
#include "../common/style.h"
#include "../common/hangman.c"
#include "../common/stream.c"


struct sockaddr_in serverAddr;
gameConfigStruct gameConfig ;
int nbClient=0;
/**
 * Main function that create the socket, create the game, and manage client connections
 * @return exit status (EXIT_FAILURE || EXIT_SUCCESS)
 */
int main(int argc, char *argv[]){
    bool loop = 1;
    system("clear");
    //? set the randomness of the program
    srand((unsigned int)time(NULL));
    //
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        printf(FONT_RED "Incorrect socket\n" FONT_DEFAULT);
        exit(EXIT_FAILURE);
    }
    //
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
    gameConfig = initGame();

    // Main loop
    printf("En attendant...\n");
    int sockaddr_in_size = sizeof(struct sockaddr_in);
    while (loop)
    {
        connectionStruct myConnectionStruct;
        myConnectionStruct.gameConfig = &gameConfig; // set the address of the gameConfig variable
        bool availableLobbys=nbClient<PLAYERS_AMOUNT;
        // waiting for a connection to come
            if ((myConnectionStruct.communicationID = accept(serverSocket, (struct sockaddr *)&myConnectionStruct.connectedAddr,
                                                             &sockaddr_in_size)) != -1)
            {
                if(!availableLobbys){
                    close(myConnectionStruct.communicationID );
                    continue;
                }

                // create the thread that will manage the connection
                pthread_t thread;
                nbClient++;
                int threadReturn = pthread_create(&thread, NULL, connectionThread, (void *)&myConnectionStruct);
            }
            else
            {
                printf(FONT_RED "Connection acceptation error\n" FONT_DEFAULT);
            }


    }
    // closing the serveur
    close(serverSocket);

    return EXIT_SUCCESS;
}
/**
 * The thread that will manage the connection
 * @param args instance of connectionStruct as (void *)
 */
void *connectionThread(void *args)
{
    connectionStruct connection = *(connectionStruct *)args;
    printf(FONT_GREEN"Client connecté N°%d \n| Adresse IP : %s\n"FONT_DEFAULT, connection.communicationID, inet_ntoa(connection.connectedAddr.sin_addr)); //? display client IP
    printf(FONT_GREEN"| Port : %d\n"FONT_DEFAULT, (int) ntohs(connection.connectedAddr.sin_port)); //? display client IP
    gameConfig.players[nbClient-1].connectionID=connection.communicationID;
    // function that will manage the client
    clientConnected(connection.communicationID, connection.gameConfig);

    close(connection.communicationID);
    // Fin du thread actuel
    pthread_exit(NULL);
}




void clientConnected(int communicationID, gameConfigStruct *gameConfig)
{
    stream_t stream = create_stream(); // stream that is used with this client
    char serStream[STREAM_SIZE];       // serialized stream
    size_t serStreamSize;              // buffer that contain the serialized stream
    char word[10];
    int wordsTotal = 0, wordsFileDescriptor;
    char ** wordsList;
    char* character;
    char* chosenWord;
    bool* mask=malloc(1 * sizeof(bool));
    bool loop = 1;
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
            case ASK_FOR_LENGTH:
                init_stream(&stream,SEND_LENGTH);

                //choose randomly a word from the list
                wordsFileDescriptor = openFile("hangmanwords.txt");
                wordsList = readFile(wordsFileDescriptor, &wordsTotal);
                int random = randomNumber(0, wordsTotal);
                while(strlen(chosenWord=wordsList[random])<3);
                close(wordsFileDescriptor);

                //initialize the boolean mask
                initBoolMask((bool *) mask, strlen(chosenWord));

                printf(FONT_YELLOW"\nMot choisi pour client n°%d: "FONT_DEFAULT,communicationID);
                puts(chosenWord);
                set_content(&stream, chosenWord);
                serStreamSize = serialize_stream(&stream, serStream);
                send(communicationID, stream.content, serStreamSize, 0); // send buffer to client
                break;
            case VERIFY_LETTER:
                character= ((char *) stream.content);       //the character sent by the client
                editBoolMask(character, mask, chosenWord);

                // if last character sent is true so we increment the number of wins for the client
                if(winningGame(mask, strlen(chosenWord))){
                    printf(FONT_GREEN"\nBingo!"FONT_DEFAULT" le joueur "FONT_GREEN"%d"FONT_DEFAULT" a trouvé le mot ("FONT_YELLOW"%s"FONT_DEFAULT")\n",communicationID,chosenWord);
                    int index=existAt(communicationID,gameConfig->players);
                    gameConfig->players[index].wins++;
                }
                //sending the bool mask
                init_stream(&stream,SEND_MASK);
                set_content_mask(&stream, mask,strlen(chosenWord));
                serStreamSize = serialize_stream(&stream, serStream);
                send(communicationID, mask, serStreamSize, 0); // send buffer to client
                break;
            case ASK_FOR_NBCLIENTS:
                sprintf(word,"%d", nbClient);
                send(communicationID, word, sizeof(word) , 0);
                break;
            case ASK_FOR_DASHBOARD:
                // send all players info
                init_stream(&stream,SEND_DASHBOARD);
                set_content(&stream,gameConfig->players);
                serStreamSize = serialize_stream(&stream, serStream);
                send(communicationID, serStream, serStreamSize , 0);
                break;
            case ASK_FOR_ID:
                // the communication ID for the current client (to color the score in green in the dashboard)
                init_stream(&stream,SEND_ID);
                sprintf(word, "%d", communicationID);
                set_content(&stream, word);
                serStreamSize = serialize_stream(&stream, serStream);
                send(communicationID, serStream, serStreamSize , 0);
                break;
            case GAME_LOST:
                printf(FONT_RED"\nDommage :("FONT_DEFAULT" le joueur "FONT_GREEN"%d"FONT_DEFAULT" n'a pas trouvé le mot ("FONT_YELLOW"%s"FONT_DEFAULT")\n",communicationID,chosenWord);
                break;
            default:
                break;
        }
    }
    printf(FONT_RED"%d | Client disconnected\n"FONT_DEFAULT, communicationID);
    destroy_stream(&stream);
}



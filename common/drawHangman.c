
#include <ctype.h>       // "Fuctions added to work with characters"
#include <stdio.h>       // "Standard Header (In/Out)"
#include <stdlib.h>      // "Standard Header"
#include <string.h>      // "Manipulate Strings"
#include <time.h>        // "Used the chronological time"

#include <sys/socket.h>
/// PRITING BASIC STRUCTURE OF GALLOWS
void Basic_Structure_Gallows (int );

/// PRITING HEAD
void Head (int );

/// PRITING BODY
void Body (int );

/// PRITING RIGHT ARM
void Right_Arm (int );

/// PRITING LEFT ARM
void Left_Arm (int );

/// PRITING RIGHT LEG
void Right_Leg (int );

/// PRITING LEFT LEG
void Left_Leg (int );

int main(){
  int Cont=0, int mistake=0;
    printf("    \u250C");

    for(Cont = 0; Cont < 5; Cont++)
        printf("\u2500\u2500\u2500\u2500\u2500\u2500");

    printf("\u2510 \n    \u2502 \t\t\t\t   \u2502 \n    \u2502 \t\t\t\t   \u2502");

    printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2510");
    printf("\n    \u2502 \t\t\t       \u2502 ^   ^ \u2502");
    printf("\n    \u2502 \t\t\t       \u2502   .   \u2502");
    printf("\n    \u2502 \t\t\t       \u2502  ---  \u2502");
    printf("\n    \u2502 \t\t\t       \u2514\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u2518");
    for(Cont = 0; Cont < 2; Cont++)
        printf("\n    \u2502 \t\t\t\t   \u2502 \n    \u2502 \t\t\t\t   \u2502");

    printf("\n    \u2502 \t\t\t\t   \u2502");

    for(Cont = 0; Cont < 4; Cont++)
        printf("\n    \u2502 \n    \u2502");

    printf("\n \u2500\u2500\u2500\u2534\u2500\u2500\u2500\n");
    printf("\n    \u2502 \t\t\t\t   \u2502");
    printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u2524");

    for(Cont = 0; Cont < 2; Cont++)
        printf("\n    \u2502 \t\t\t       \u2502   \u2502");

    printf("\n    \u2502 \t\t\t       \u253C   \u2502");

    for(Cont = 0; Cont < 4; Cont++)
        printf("\n    \u2502 \n    \u2502");

    printf("\n \u2500\u2500\u2500\u2534\u2500\u2500\u2500\n");
    printf("\n    \u2502 \t\t\t\t   \u2502");
    printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u2510");

    for(Cont = 0; Cont < 2; Cont++)
        printf("\n    \u2502 \t\t\t       \u2502   \u2502   \u2502");

    printf("\n    \u2502 \t\t\t       \u253C   \u2502   \u253C");

    printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2510");
    printf("\n    \u2502 \t\t\t       \u2502 x   x \u2502");
    printf("\n    \u2502 \t\t\t       \u2502   .   \u2502");
    printf("\n    \u2502 \t\t\t       \u2502   +   \u2502");
    printf("\n    \u2502 \t\t\t       \u2514\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u2518");
    printf("\n    \u2502 \t\t\t\t\u2514\u2500\u2500\u253C\u2500\u2500\u2518");
    printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u2510");

    for(Cont = 0; Cont < 2; Cont++)
        printf("\n    \u2502 \t\t\t       \u2502   \u2502   \u2502");

    printf("\n    \u2502 \t\t\t       \u253C   \u2502   \u253C");
    printf("\n    \u2502 \t\t\t          / \\ \n    \u2502 \t\t\t         /   \\");
    printf("\n    \u2502 \t\t\t        /     \\ \n    \u2502 \t\t\t       /       \\");
    printf("\n    \u2502  \t\t\t      /         \\ \n    \u2502 ");
    printf("\n    \u2502 \n    \u2502 \n \u2500\u2500\u2500\u2534\u2500\u2500\u2500\n");


    //###############################################################################

/// PRITING BASIC STRUCTURE OF GALLOWS
    void Basic_Structure_Gallows(int Cont)
    {
        printf("    \u250C");

        for(Cont = 0; Cont < 5; Cont++)
            printf("\u2500\u2500\u2500\u2500\u2500\u2500");

        printf("\u2510 \n    \u2502 \t\t\t\t   \u2502 \n    \u2502 \t\t\t\t   \u2502");
    }
//###############################################################################

/// PRITING HEAD
    void Head(int Cont)
    {
        Basic_Structure_Gallows(Cont);

        printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2510");
        printf("\n    \u2502 \t\t\t       \u2502 ^   ^ \u2502");
        printf("\n    \u2502 \t\t\t       \u2502   .   \u2502");
        printf("\n    \u2502 \t\t\t       \u2502  ---  \u2502");
        printf("\n    \u2502 \t\t\t       \u2514\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u2518");
    }
//###############################################################################

/// PRITING BODY
    void Body(int Cont)
    {
        Head(Cont);

        for(Cont = 0; Cont < 2; Cont++)
            printf("\n    \u2502 \t\t\t\t   \u2502 \n    \u2502 \t\t\t\t   \u2502");

        printf("\n    \u2502 \t\t\t\t   \u2502");

        for(Cont = 0; Cont < 4; Cont++)
            printf("\n    \u2502 \n    \u2502");

        printf("\n \u2500\u2500\u2500\u2534\u2500\u2500\u2500\n");
    }
//###############################################################################

/// PRITING RIGHT ARM
    void Right_Arm(int Cont)
    {
        Head(Cont);

        printf("\n    \u2502 \t\t\t\t   \u2502");
        printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u2524");

        Body(Cont);
    }
//###############################################################################

/// PRITING LEFT ARM
    void Left_Arm(int Cont)
    {
        Head(Cont);

        printf("\n    \u2502 \t\t\t\t   \u2502");
        printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u2510");

        for(Cont = 0; Cont < 2; Cont++)
            printf("\n    \u2502 \t\t\t       \u2502   \u2502   \u2502");

        printf("\n    \u2502 \t\t\t       \u253C   \u2502   \u253C");
    }
//###############################################################################

/// PRITING RIGHT LEG
    void Right_Leg(int Cont)
    {
        Left_Arm(Cont);

        printf("\n    \u2502 \t\t\t          / \n    \u2502 \t\t\t         /");
        printf("\n    \u2502 \t\t\t        / \n    \u2502 \t\t\t       /");
        printf("\n    \u2502  \t\t\t      / \n    \u2502 ");
        printf("\n    \u2502 \n    \u2502 \n \u2500\u2500\u2500\u2534\u2500\u2500\u2500\n");
    }
//###############################################################################

/// PRITING LEFT LEG
    void Left_Leg(int Cont)
    {
        Basic_Structure_Gallows(Cont);

        printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2510");
        printf("\n    \u2502 \t\t\t       \u2502 x   x \u2502");
        printf("\n    \u2502 \t\t\t       \u2502   .   \u2502");
        printf("\n    \u2502 \t\t\t       \u2502   +   \u2502");
        printf("\n    \u2502 \t\t\t       \u2514\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u2518");
        printf("\n    \u2502 \t\t\t\t\u2514\u2500\u2500\u253C\u2500\u2500\u2518");
        printf("\n    \u2502 \t\t\t       \u250C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u2510");

        for(Cont = 0; Cont < 2; Cont++)
            printf("\n    \u2502 \t\t\t       \u2502   \u2502   \u2502");

        printf("\n    \u2502 \t\t\t       \u253C   \u2502   \u253C");
        printf("\n    \u2502 \t\t\t          / \\ \n    \u2502 \t\t\t         /   \\");
        printf("\n    \u2502 \t\t\t        /     \\ \n    \u2502 \t\t\t       /       \\");
        printf("\n    \u2502  \t\t\t      /         \\ \n    \u2502 ");
        printf("\n    \u2502 \n    \u2502 \n \u2500\u2500\u2500\u2534\u2500\u2500\u2500\n");
    }
//###############################################################################


}

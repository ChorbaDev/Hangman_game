
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
    printf("    ┌");

    for(Cont = 0; Cont < 5; Cont++)
        printf("──────");

    printf("┐ \n    │ \t\t\t\t   │ \n    │ \t\t\t\t   │");

    printf("\n    │ \t\t\t       ┌───┴───┐");
    printf("\n    │ \t\t\t       │ ^   ^ │");
    printf("\n    │ \t\t\t       │   .   │");
    printf("\n    │ \t\t\t       │  ---  │");
    printf("\n    │ \t\t\t       └───┬───┘");
    for(Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t\t   │ \n    │ \t\t\t\t   │");

    printf("\n    │ \t\t\t\t   │");

    for(Cont = 0; Cont < 4; Cont++)
        printf("\n    │ \n    │");

    printf("\n ───┴───\n");
    printf("\n    │ \t\t\t\t   │");
    printf("\n    │ \t\t\t       ┌───┤");

    for(Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │");

    printf("\n    │ \t\t\t       ┼   │");

    for(Cont = 0; Cont < 4; Cont++)
        printf("\n    │ \n    │");

    printf("\n ───┴───\n");
    printf("\n    │ \t\t\t\t   │");
    printf("\n    │ \t\t\t       ┌───┼───┐");

    for(Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │   │");

    printf("\n    │ \t\t\t       ┼   │   ┼");

    printf("\n    │ \t\t\t       ┌───┴───┐");
    printf("\n    │ \t\t\t       │ x   x │");
    printf("\n    │ \t\t\t       │   .   │");
    printf("\n    │ \t\t\t       │   +   │");
    printf("\n    │ \t\t\t       └───┬───┘");
    printf("\n    │ \t\t\t\t└──┼──┘");
    printf("\n    │ \t\t\t       ┌───┼───┐");

    for(Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │   │");

    printf("\n    │ \t\t\t       ┼   │   ┼");
    printf("\n    │ \t\t\t          / \\ \n    │ \t\t\t         /   \\");
    printf("\n    │ \t\t\t        /     \\ \n    │ \t\t\t       /       \\");
    printf("\n    │  \t\t\t      /         \\ \n    │ ");
    printf("\n    │ \n    │ \n ───┴───\n");


    //###############################################################################

/// PRITING BASIC STRUCTURE OF GALLOWS
    void Basic_Structure_Gallows(int Cont)
    {
        printf("    ┌");

        for(Cont = 0; Cont < 5; Cont++)
            printf("──────");

        printf("┐ \n    │ \t\t\t\t   │ \n    │ \t\t\t\t   │");
    }
//###############################################################################

/// PRITING HEAD
    void Head(int Cont)
    {
        Basic_Structure_Gallows(Cont);

        printf("\n    │ \t\t\t       ┌───┴───┐");
        printf("\n    │ \t\t\t       │ ^   ^ │");
        printf("\n    │ \t\t\t       │   .   │");
        printf("\n    │ \t\t\t       │  ---  │");
        printf("\n    │ \t\t\t       └───┬───┘");
    }
//###############################################################################

/// PRITING BODY
    void Body(int Cont)
    {
        Head(Cont);

        for(Cont = 0; Cont < 2; Cont++)
            printf("\n    │ \t\t\t\t   │ \n    │ \t\t\t\t   │");

        printf("\n    │ \t\t\t\t   │");

        for(Cont = 0; Cont < 4; Cont++)
            printf("\n    │ \n    │");

        printf("\n ───┴───\n");
    }
//###############################################################################

/// PRITING RIGHT ARM
    void Right_Arm(int Cont)
    {
        Head(Cont);

        printf("\n    │ \t\t\t\t   │");
        printf("\n    │ \t\t\t       ┌───┤");
        for(Cont = 0; Cont < 2; Cont++)
            printf("\n    │ \t\t\t       │   │");

        printf("\n    │ \t\t\t       ┼   │");

        for(Cont = 0; Cont < 4; Cont++)
            printf("\n    │ \n    │");

        printf("\n ───┴───\n");
        
    }
//###############################################################################

/// PRITING LEFT ARM
    void Left_Arm(int Cont)
    {
        Head(Cont);

        printf("\n    │ \t\t\t\t   │");
        printf("\n    │ \t\t\t       ┌───┼───┐");

        for(Cont = 0; Cont < 2; Cont++)
            printf("\n    │ \t\t\t       │   │   │");

        printf("\n    │ \t\t\t       ┼   │   ┼");
    }
//###############################################################################

/// PRITING RIGHT LEG
    void Right_Leg(int Cont)
    {
        Left_Arm(Cont);

        printf("\n    │ \t\t\t          / \n    │ \t\t\t         /");
        printf("\n    │ \t\t\t        / \n    │ \t\t\t       /");
        printf("\n    │  \t\t\t      / \n    │ ");
        printf("\n    │ \n    │ \n ───┴───\n");
    }
//###############################################################################

/// PRITING LEFT LEG
    void Left_Leg(int Cont)
    {
        Basic_Structure_Gallows(Cont);

        printf("\n    │ \t\t\t       ┌───┴───┐");
        printf("\n    │ \t\t\t       │ x   x │");
        printf("\n    │ \t\t\t       │   .   │");
        printf("\n    │ \t\t\t       │   +   │");
        printf("\n    │ \t\t\t       └───┬───┘");
        printf("\n    │ \t\t\t\t└──┼──┘");
        printf("\n    │ \t\t\t       ┌───┼───┐");

        for(Cont = 0; Cont < 2; Cont++)
            printf("\n    │ \t\t\t       │   │   │");

        printf("\n    │ \t\t\t       ┼   │   ┼");
        printf("\n    │ \t\t\t          / \\ \n    │ \t\t\t         /   \\");
        printf("\n    │ \t\t\t        /     \\ \n    │ \t\t\t       /       \\");
        printf("\n    │  \t\t\t      /         \\ \n    │ ");
        printf("\n    │ \n    │ \n ───┴───\n");
    }
//###############################################################################


}

#include <stdio.h>       // "Standard Header (In/Out)"
#include <stdlib.h>      // "Standard Header"
#include "drawHangman.h"
///##############################################################

void wrongGuess(int mistake) {
    switch (mistake) {
        case 0:
            //0 erreurs on doit juste print la potence
            Potence();
            for(int Cont = 0; Cont < 9; Cont++)
                printf("\n    │ \n    │ ");

            printf("\n ───┴───\n");
            break;
        case 1:
            //1 erreur donc tete
            Head();
            for(int Cont = 0; Cont < 6; Cont++)
                printf("\n    │ \n    │ ");

            printf("\n    │ \n ───┴───\n");
            break;
        case 2:
            //2 erreurs donc corps
            Body();
            break;
        case 3:
            //3 erreurs donc bras droit
            rArm();
            break;
        case 4:
            //4 erreurs donc bras gauche
            lArm();
            for(int Cont = 0; Cont < 4; Cont++)
                printf("\n    │ \n    │");

            printf("\n ───┴───\n");
            break;
        case 5:
            //5 erreurs donc jambe droite
            rLeg();
            break;
        case 6:
            //6 erreurs donc jambe gauche
            lLeg();
            break;
    }
}

//dessine la potence
void Potence(){
    printf("\n    ┌");

    for(int Cont = 0; Cont < 5; Cont++)
        printf("──────");

    printf("┐ \n    │ \t\t\t\t   │ \n    │ \t\t\t\t   │");
}
//dessine la tête
void Head(){
    Potence();
    printf("\n    │ \t\t\t       ┌───┴───┐");
    printf("\n    │ \t\t\t       │ ^   ^ │");
    printf("\n    │ \t\t\t       │   .   │");
    printf("\n    │ \t\t\t       │  ---  │");
    printf("\n    │ \t\t\t       └───┬───┘");
}
// dessine le corps
void Body(){
    Head();

    for(int Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t\t   │ \n    │ \t\t\t\t   │");

    printf("\n    │ \t\t\t\t   │");

    for(int Cont = 0; Cont < 4; Cont++)
        printf("\n    │ \n    │");

    printf("\n ───┴───\n");
}
// dessine le bras droit
void rArm(){
    Head();

    printf("\n    │ \t\t\t\t   │");
    printf("\n    │ \t\t\t       ┌───┤");
    for(int Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │");

    printf("\n    │ \t\t\t       ┼   │");

    for(int Cont = 0; Cont < 4; Cont++)
        printf("\n    │ \n    │");

    printf("\n ───┴───\n");
}
// dessine le bras gauche
void lArm(){
    Head();

    printf("\n    │ \t\t\t\t   │");
    printf("\n    │ \t\t\t       ┌───┼───┐");

    for(int Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │   │");

    printf("\n    │ \t\t\t       ┼   │   ┼");
}
//dessine la jambe droite
void rLeg(){
    lArm();

    printf("\n    │ \t\t\t          / \n    │ \t\t\t         /");
    printf("\n    │ \t\t\t        / \n    │ \t\t\t       /");
    printf("\n    │  \t\t\t      / \n    │ ");
    printf("\n    │ \n    │ \n ───┴───\n");
}
// dessine la jambe gauche
void lLeg(){
    Potence();

    printf("\n    │ \t\t\t       ┌───┴───┐");
    printf("\n    │ \t\t\t       │ x   x │");
    printf("\n    │ \t\t\t       │   .   │");
    printf("\n    │ \t\t\t       │   +   │");
    printf("\n    │ \t\t\t       └───┬───┘");
    printf("\n    │ \t\t\t\t└──┼──┘");
    printf("\n    │ \t\t\t       ┌───┼───┐");

    for(int Cont = 0; Cont < 2; Cont++)
        printf("\n    │ \t\t\t       │   │   │");

    printf("\n    │ \t\t\t       ┼   │   ┼");
    printf("\n    │ \t\t\t          / \\ \n    │ \t\t\t         /   \\");
    printf("\n    │ \t\t\t        /     \\ \n    │ \t\t\t       /       \\");
    printf("\n    │  \t\t\t      /         \\ \n    │ ");
    printf("\n    │ \n    │ \n ───┴───\n");
}

void perdu(){
    // affichage du mot et dire que le gars à perdu on lui propose de recommencer
}
void gagne(){
    // affichage du message de victoire
}
// dessine le pendu en position gagnante
void potenceGagnant(){
    Potence();
    printf("\n    │ \t\t\t\t  /┴\\ \n    │ \t\t\t\t /   \\ \n    │ \t\t\t\t/     \\");
    printf("\n    │ \t\t\t       └───────┘");
    printf("\n    │ \t\t┌───────┐");
    printf("\n    │      ┬    │ ^   ^ │    ┬    ");
    printf("\n    │      │    │   .   │    │    ");
    printf("\n    │      \\    │ [___] │    /   ");
    printf("\n    │       \\   └───────┘   / ");
    printf("\n    │ \t     \\      │      / ");
    printf("\n    │ \t      \\─────│─────/ ");
    printf("\n    │ \t\t    │ \n    │ \t\t    │ \n    │ \t\t    │");
    printf("\n    │ \t\t   / \\ \n    │ \t\t  /   \\       ");
    printf("\n    │ \t\t /     \\ \n    │ \t\t/       \\     ");
    printf("\n ───┴───      ──┘       └──\n");
}
int Restart_Or_Exit() {
    int Cont;
    char Output;

    do {
        Output = getchar();

        if (Output == 'n' || Output == 'N') {
            system("clear");

            printf("\n\n   ┌");

            for (Cont = 0; Cont < 8; Cont++)
                printf("──────");

            printf("┐ \n   │");

            printf("\t\t Bien joué!! A bientot!!");

            printf("\t    │ \n   └");

            for (Cont = 0; Cont < 8; Cont++)
                printf("──────");

            printf("┘ \n\n\n\n");

            return 0;
        }

        if (Output == 'y' || Output == 'Y') {
            system("clear");
            return 10;
        }
    } while (Output != 'Y' && Output != 'y' && Output != 'N' && Output != 'n');
}
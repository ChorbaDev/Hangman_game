#ifndef PRJ_HANGMANC_DRAWHANGMAN_H
#define PRJ_HANGMANC_DRAWHANGMAN_H
/// PRITING BASIC STRUCTURE OF GALLOWS
void Potence ();

/// PRITING HEAD
void Head ( );

/// PRITING BODY
void Body ( );

/// PRITING RIGHT ARM
void rArm ( );

/// PRITING LEFT ARM
void lArm ( );

/// PRITING RIGHT LEG
void rLeg ( );

/// PRITING LEFT LEG
void lLeg ( );

///PRINTING THE WINNING HANGMAN
void potenceGagnant();

///DECIDE THE PART TO DRAW
void wrongGuess(int mistake);

#endif //PRJ_HANGMANC_DRAWHANGMAN_H

/* Christopher Lam
 * Testing the following:
NOT DONE * void makeAction (Game g, action a);
DONE * int getMostARCs (Game g);
FAIL DONE * int getCampus(Game g, path pathToVertex);
DONE * int getARCs (Game g, int player);
DONE * int getIPs (Game g, int player);
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Game.h"
 
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
#define MAX_DICE 12
#define MIN_DICE 2
#define NUM_UNIS 3
 
// player ID of each university
#define NO_ONE 0
#define UNI_A 1
#define UNI_B 2
#define UNI_C 3
 
// contents of an ARC
#define VACANT_ARC 0
#define ARC_A 1
#define ARC_B 2
#define ARC_C 3
 
// contents of a VERTEX
#define VACANT_VERTEX 0
#define CAMPUS_A 1
#define CAMPUS_B 2
#define CAMPUS_C 3
#define GO8_A 4
#define GO8_B 5
#define GO8_C 6
 
// action codes
#define PASS 0
#define BUILD_CAMPUS 1
#define BUILD_GO8 2
#define OBTAIN_ARC 3
#define START_SPINOFF 4
#define OBTAIN_PUBLICATION 5
#define OBTAIN_IP_PATENT 6
#define RETRAIN_STUDENTS 7
 
// disciplines
#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5
 
#define NUM_REGIONS 19
#define PATH_LIMIT 150
 
#define TRUE 1
#define FALSE 0
 
int main (int argc, char *argv[]) {
 
    int defaultDisciplines[] = DEFAULT_DISCIPLINES;
    int defaultDice[] = DEFAULT_DICE;

    Game aGame = newGame(defaultDisciplines, defaultDice);

	// Testing getMostARCs ();
	// int getMostARCs (Game g);
	// which university currently has the prestige award for the most ARCs?
    printf ("Testing getMostARCs... \n");
    	assert (getMostARCs (aGame) == 0);
    printf ("All tests passed! \n");
	// END OF TEST


	// Testing getARCs ();
	// int getARCs (Game g, int player);
	// return the number of ARC grants the specified player currently has
    printf ("Testing getARCs... \n");
    assert (getARCs (aGame, UNI_A) == 0);
    assert (getARCs (aGame, UNI_B) == 0);
    assert (getARCs (aGame, UNI_C) == 0);
    printf ("All tests passed! \n");
	// END OF TEST


	// Testing getIPs ();
	// int getIPs (Game g, int player);C
	// return the number of IP Patents the specified player currently has
    printf ("Testing getIPs... \n");
    assert (getIPs (aGame, UNI_A) == 0);
    assert (getIPs (aGame, UNI_B) == 0);
    assert (getIPs (aGame, UNI_C) == 0);
    printf ("All tests passed! \n");
	// END OF TEST


	// Testing getCampus ();
	// int getCampus(Game g, path pathToVertex);
	// return the contents of the given vertex (ie campus code or 
	// VACANT_VERTEX)
    printf ("Testing getCampus... \n"); //testing initial campuses
		assert (getCampus (aGame, "") == CAMPUS_A);
		assert (getCampus (aGame, "RLRLRLRLRLL") == CAMPUS_A);

		assert (getCampus (aGame, "RRLRL") == CAMPUS_B);
		assert (getCampus (aGame, "LRLRLRRLRL") == CAMPUS_B);

		assert (getCampus (aGame, "LRLRL") == CAMPUS_C);
		assert (getCampus (aGame, "RRLRLLRLRL") == CAMPUS_C);

		assert (getCampus (aGame, "LR") == VACANT_VERTEX); //Random empty vertex
		assert (getCampus (aGame, "LRRRRR") == CAMPUS_A); //Loop back to start
    //Not sure how to test different paths, or if the path goes outside the game

    printf ("All tests passed! \n");
	// END OF TEST


	// Testing makeAction ();
	// void makeAction (Game g, action a);
	// make the specified action for the current player and update the 
	// game state accordingly.  
	// The function may assume that the action requested is legal.
	// START_SPINOFF is not a legal action here
	printf ("Testing makeAction... \n");

    disposeGame(aGame);
    aGame = newGame(defaultDisciplines, defaultDice);
    Game initialGame = aGame;

    //testing for initial state action PASS
    action initialPASS = {PASS,};
       makeAction (aGame, initialPASS);
       assert (initialGame == aGame);

    //testing for initial state action BUILD_CAMPUS
    disposeGame(aGame);
    aGame = newGame(defaultDisciplines, defaultDice);
    action initialBUILDCAMPUS = {BUILD_CAMPUS, "L" ,};
        makeAction (aGame, initialBUILDCAMPUS);
        assert (getCampuses (aGame, UNI_A) == 1);
        assert (aGame != initialGame);
        assert (getCampus (aGame, "L") == CAMPUS_A);

    //testing for initial state action BUILD_GO8
    disposeGame(aGame);
    aGame = newGame(defaultDisciplines, defaultDice);
    action initialBUILDGO8 = {BUILD_GO8, "", };
        makeAction (aGame, initialBUILDGO8);
        assert (getGO8s (aGame, UNI_A) == 1);
        assert (aGame != initialGame);
        assert (getCampus (aGame, "") == GO8_A);

    //testing for initial state action OBTAIN_ARC
    disposeGame(aGame);
    aGame = newGame(defaultDisciplines, defaultDice);
    action initialOBTAINARC = {OBTAIN_ARC, "L", };
        makeAction (aGame, initialOBTAINARC);
        assert (getARCs (aGame, UNI_A) == 1);
        assert (aGame != initialGame);
        assert (getARC (aGame, "L") == ARC_A);

    //testing for initial state action RETRAIN_STUDENTS
    disposeGame(aGame);
    aGame = newGame(defaultDisciplines, defaultDice);
    action initialRETRAINSTUDENTS = {RETRAIN_STUDENTS, "L", STUDENT_BQN, STUDENT_THD};
        makeAction (aGame, initialRETRAINSTUDENTS);
        assert (aGame != initialGame);
        assert(getStudents (aGame, UNI_A, STUDENT_BQN) == 0);
        assert(getStudents (aGame, UNI_A, STUDENT_THD) == 1);

    printf ("All tests passed! \n");
	// END OF TEST


    printf("All tests passed! You are awesome!\n");

}


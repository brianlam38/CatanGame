/*
BRIAN LAM
	
Game is a TYPE. Variable = g
path is a TYPE. Variable = pathToVertex

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "Game.h"

#define CYAN STUDENT_BQN
#define PURP STUDENT_MMONEY
#define YELL STUDENT_MJ
#define RED STUDENT_BPS
#define GREE STUDENT_MTV 
#define BLUE STUDENT_THD

#define TEST_DISCIPLINES {CYAN,PURP,YELL,PURP,YELL,RED,GREE,GREE,RED,GREE,CYAN,YELL,CYAN,BLUE,YELL,PURP,GREE,CYAN,RED}
#define TEST_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,9,9,2,8,10,5}

/* FUNCTION DECLARATIONS */
void createGame (void); //Intializes the game;
void testGetCampus (Game g, path pathToVertex);
void testGetArc (Game g, path pathToEdge);
void getDiscipline (void);

/* MAIN FUNCTION */
int main (int argc, const char * argv[]) {
    printf ("Testing the game\n");

    void testCreateGame(Game g);
    void getCampus(Game g, path pathToVertex);
    void testGetARC (Game g, path pathToEdge);
    void testGetDiscipline (Game g, int regionID);
    void testGetDiceValue (Game g, int regionID);
    // Test Function 7
    // Test Function 8
    // Test Function 9

    printf ("All tests passed! You are awesome!\n");
    return EXIT_SUCCESS;
}

/* CREATE GAME TEST FUNCTION */ 
void testCreateGame (void) {
    printf ("Testing create new Game...\n");
    int disciplines[NUM_REGIONS];
    int dice [NUM_REGIONS];
   
    int regionID = 0;
    while (regionID < NUM_REGIONS) {
        disciplines[regionID] = STUDENT_THD;
        dice [regionID] = 12;
        regionID++;
    }
 
    Game g = newGame (disciplines, dice);
   
    assert (getTurnNumber(g) == -1);
    disposeGame (g);
    printf ("All tests passed!\n");
}

/* GET CAMPUS TEST FUNCTION */
// Returns the contents of the given vertex (i.e. campus code or VACANT_VERTEX)
// Create a "hardcoded path" that you can assert
// E.g. From PLAYER A CAMPUS, move LEFT / RIGHT / BACKWARDS --> Is there a campus/G08 there?
void testGetCampus (Game g, path pathToVertex) {
    printf("Testing get campus\n");

    assert (getCampus (g, "") == CAMPUS_A);
    assert (getCampus (g, "RLRLRLRLRLL") == CAMPUS_A);

    assert (getCampus (g, "RRLRL") == CAMPUS_B);
    assert (getCampus (g, "LRLRLRRLRL") == CAMPUS_B);

    assert (getCampus (g, "LRLRL") == CAMPUS_C);
    assert (getCampus (g, "RRLRLLRLRL") == CAMPUS_C);

    assert (getCampus (aGame, "LR") == VACANT_VERTEX); // Path to a random empty vertex
    assert (getCampus (aGame, "LRRRRR") == CAMPUS_A); // Path to loop back to the start
    //Not sure how to test different paths, or if the path goes outside the game

    printf ("All getCampus tests passed!\n");
}

/* GET ARC TEST FUNCTION */
void testGetArc (Game g, path pathToEdge) {
    printf ("Testing getARCs\n");
    // Testing initial game state
    assert (getARCs (aGame, UNI_A) == 0);
    assert (getARCs (aGame, UNI_B) == 0);
    assert (getARCs (aGame, UNI_C) == 0);

	makeAction();
	assert if (a == 0){
		      testGetARC = 1;
		      a++;
	       } else {
		      testGetARC = 0;
		      a++;
	}
	testGetDiscipline();
	assert if (g == 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 || 10 || 11 || 12){
		  regionID = region ID[NUM_REGIONS];
		  testGetARC = 1;
	       } else {
		  testGetARC = 0;
	       }
	assert(pathToEdge => 0);
	assert(pathToEdge <= 150);
	assert(NUM_REGIONS <= 19);
	assert(NUM_REGIONS => 0);
	assert(RETRAIN_STUDENTS <= 7);
}

/* GET DISCIPLINE TEST FUNCTION */
void testGetDiscipline (Game g, int regionID) {
    assert (getDiscipline (g, 0) == CYAN);
    assert (getDiscipline (g, 1) == PURP);
    assert (getDiscipline (g, 2) == YELL);
    assert (getDiscipline (g, 3) == PURP);
    assert (getDiscipline (g, 4) == YELL);
    assert (getDiscipline (g, 5) == RED);
    assert (getDiscipline (g, 6) == GREE);
    assert (getDiscipline (g, 7) == GREE);
    assert (getDiscipline (g, 8) == RED);
    assert (getDiscipline (g, 9) == GREE);
    assert (getDiscipline (g, 10) == CYAN);
    assert (getDiscipline (g, 11) == YELL);
    assert (getDiscipline (g, 12) == CYAN);
    assert (getDiscipline (g, 13) == BLUE);
    assert (getDiscipline (g, 14) == YELL);
    assert (getDiscipline (g, 15) == PURP);
    assert (getDiscipline (g, 16) == GREE);
    assert (getDiscipline (g, 17) == CYAN);
    assert (getDiscipline (g, 18) == RED);
}

/* GET DICE VALUE TEST FUNCTION */
void testGetDiceValue (Game g, int regionID) {
   assert (getDiceValue (g, 0) == 9);
   assert (getDiceValue (g, 1) == 10);
   assert (getDiceValue (g, 2) == 8);
   assert (getDiceValue (g, 3) == 12);
   assert (getDiceValue (g, 4) == 6);
   assert (getDiceValue (g, 5) == 5);
   assert (getDiceValue (g, 6) == 3);
   assert (getDiceValue (g, 7) == 11);
   assert (getDiceValue (g, 8) == 3);
   assert (getDiceValue (g, 9) == 11);
   assert (getDiceValue (g, 10) == 4);
   assert (getDiceValue (g, 11) == 6);
   assert (getDiceValue (g, 12) == 4);
   assert (getDiceValue (g, 13) == 7);
   assert (getDiceValue (g, 14) == 9);
   assert (getDiceValue (g, 15) == 2);
   assert (getDiceValue (g, 16) == 8);
   assert (getDiceValue (g, 17) == 10);
   assert (getDiceValue (g, 18) == 5);
}

//void testNewGame (void);
//void makeAction (Game g, action a);
//int testGetDiceValue (Game g, int regionID);


//int testGetMostPublications (Game g)
//int testGetTurnNumber (Game g);
//int testGetWhoseTurn (Game g);
//int testIsLegalAction (Game g, action a);
//int testGetKPIpoints (Game g, int player);

/* GET G08s TEST FUNCTION */
int testGetGO8s (Game g, int player) {
    printf("Testing initial state of player G08s");
    assert (testGetGO8s (g, UNI_A) == 0);
    assert (testGetGO8s (g, UNI_B) == 0);
    assert (testGetGO8s (g, UNI_C) == 0);
return 0;
}

//int testGetCampuses (Game g, int player);
//int testGetIPs (Game g, int player);
//int testGetPublications (Game g, int player);
//int testGetStudents (Game g, int player, int discipline);
//int testGetExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo);

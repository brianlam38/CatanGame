/*

testGame.c

Project Team: WeAreTheBest

Members: Brian Lam
         David Riesenberg
         Mehri Amin
         Sharon Park
         Ven Katesh Vasudevan

Class: wed-16 kora  Tutor: Jordan Brown


INSTRUCTIONS
To implement unit tests for the interface functions in Game.h

    1. Pretend all functions in Game.c have already been written.
    2. Plan and write testGame.c - which #includes Game.h and which
       contains a main function that:
           1. creates a Game (or several Games) and uses them to
           2. extensively test the Game adt interface functions.
           3. At the end, if you have passed all tests,
              printf"All tests passed, you are Awesome!".

*/



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}

#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}


// Declaring our test functions //
void testgetTurnNumber(void);
void testgetCampus(void);
void testgetARC(void);
void testgetDiscipline(void);
void testgetDiceValue(void);

// Main Function //
int main (int argc, const char * argv[]) {
    printf ("Testing the game\n");

    testgetTurnNumber();
    testgetCampus();
    testgetARC();
    testgetDiscipline();
    testgetDiceValue();


    printf ("All tests passed! You are Awesome!\n");

    return EXIT_SUCCESS;
}

//getTurnNumber//
void testgetTurnNumber(void){

    printf("Testing getTurnNumber\n");

    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game test = newGame(disciplines,dice);

    assert(getTurnNumber(test) == -1);

    throwDice(test,dice[0]);
    assert(getTurnNumber(test) == 0);

    throwDice(test,dice[1]);
    assert(getTurnNumber(test) == 1);

    throwDice(test,dice[2]);
    assert(getTurnNumber(test) == 2);

    throwDice(test,dice[3]);
    assert(getTurnNumber(test) == 3);

    disposeGame(test);

    printf("getTurnNumber tests passed!\n");
}

//getCampus//
void testgetCampus(void){

    printf("Testing getCampus\n");

    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game test = newGame(disciplines,dice);

    path path1 = "RLLLLLL";
    path path2 = "L";
    path path3 = "R";
    path path4 = "LRLRL";
    path path5 = "RRLRL";
    path path6 = "RLRLRLRRLR";
    path path7 = "RLRLRLRLLRR";
    path path8 = "LRRLRLRLLLRR";
    path path9 = "RLRLRL";
    path path10 = "RLRLRLLLRR";

    assert(getCampus(test,path1) == CAMPUS_A);
    assert(getCampus(test,path2) == VACANT_VERTEX);
    assert(getCampus(test,path3) == VACANT_VERTEX);
    assert(getCampus(test,path4) == CAMPUS_C);
    assert(getCampus(test,path5) == CAMPUS_B);
    assert(getCampus(test,path6) == CAMPUS_C);
    assert(getCampus(test,path7) == CAMPUS_A);
    assert(getCampus(test,path8) == CAMPUS_B);
    assert(getCampus(test,path9) == VACANT_VERTEX);
    assert(getCampus(test,path10) == VACANT_VERTEX);

    disposeGame(test);

    printf("getCampus tests passed!\n");
}

//getARC//
void testgetARC (void) {

    printf("Testing getARC\n");

    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game test = newGame(disciplines,dice);

    path path1 = "L";
    path path2 = "R";
    path path3 = "RL";
    path path4 = "LR";
    path path5 = "LRRRL";
    path path6 = "RRLLL";
    path path7 = "RLR";

    assert(getCampus(test,path1) == VACANT_ARC);
    assert(getCampus(test,path2) == VACANT_ARC);
    assert(getCampus(test,path3) == VACANT_ARC);
    assert(getCampus(test,path4) == VACANT_ARC);
    assert(getCampus(test,path5) == VACANT_ARC);
    assert(getCampus(test,path6) == VACANT_ARC);
    assert(getCampus(test,path7) == VACANT_ARC);

    disposeGame(test);

    printf("getArc tests passed!\n");
}

//getDiscipline//
void testgetDiscipline(void) {

    printf("Testing getDiscipline...\n");

    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game test = newGame(disciplines, dice);

    int dt=0;
    while (dt<=NUM_REGIONS){
      assert(getDiscipline(test,dt)==disciplines[dt]);
      dt++;
   }
   disposeGame(test);

   printf("getDiscipline tests passed!\n");
}

//getDiceValue//
void testgetDiceValue(void){

    printf("Testing getDiceValue\n");

    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game test = newGame(disciplines,dice);

    assert(getDiceValue(test,7) == STUDENT_THD);
    assert(getDiceValue(test,12) == STUDENT_MMONEY);
    assert(getDiceValue(test,11) == STUDENT_MTV);
    assert(getDiceValue(test,5) == STUDENT_BPS);
    assert(getDiceValue(test,9) == STUDENT_MJ);
    assert(getDiceValue(test,10) == STUDENT_BQN);

    disposeGame(test);

    printf("getDiceValue tests passed!\n");
}
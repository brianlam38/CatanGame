/* Mechanical Turk.c 
   This was done by our group of 3
   Venkatesh Vasudevan 
   Dovid Riesenberg
   Brian Lam
   Our AI is gonna beat all the other Ai
   To shreds
*/

/*  GENERAL COMMENTS
* Build ARC to extend territory, and then campuses
* STUDENT_BPS + STUDENT_BQN= OBTAIN_ARC  
*
* Problem: How do we direct the AI?
* Jordan's advice: (1) Can I buy X? (2) What do I need to buy? (3) Where do I want to be?
*
*/

/*  COMMENTS ABOUT CURRENT STRATEGY
*
*   Should bulding ARC/CAMPUS/GO8 be in separate functions?
*   Should different AI strategies be in separate functions? Or combined in one? Or just stick with one good AI?
*
*   At turn -1, everyone has enough to build 2 x ARCS, 1 x CAMPUS
*   - At the beginning of the game, aim should be to build ARCS towards resources that you DON'T HAVE
*   - Build 2 x ARCS towards resources that you don't have (so that you are 2 x vertices away)
*   - Build 1 x CAMPUS on the vertex with resources that you don't have
*
*   READ JORDAN'S FACEBOOK COMMENT.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "mechanicalTurk.h"

//#define TRUE 1      // exists in game.h
//#define FALSE 0     // exists in game.h

/* function declarations */
//int checkArc (Game g);
//int checkCampus (Game g);
//int basicAI (Game g, int checkArc, int checkCampus);

    
/*  Main basicAI program */
int basicAI (Game g, int checkArc, int checkCampus) {
    action a;

    int numTHD = getStudents (g, getWhoseTurn (g), STUDENT_THD);
    int numBPS = getStudents (g, getWhoseTurn (g), STUDENT_BPS);
    int numBQN = getStudents (g, getWhoseTurn (g), STUDENT_BQN);
    int numMJ = getStudents (g, getWhoseTurn (g), STUDENT_MJ);
    int numMTV = getStudents (g, getWhoseTurn (g), STUDENT_MTV);
    int numMMONEY = getStudents (g, getWhoseTurn (g), STUDENT_MMONEY);

    // turn 1 strategy
    // Build two arcs first, in the direction of resource that you are missing
    // Build a campus right after the two arcs, so you can begin gathering resources that you are missing
    /* insert code for turn 1 strategy */

    if ((checkArc (g) == FALSE) && (numMJ >= 1) && (numMTV >= 1)) {         // If yes independent res for CAMPUS, don't build arcs.
        a.actionCode = PASS;                                               
    } else if ((checkArc (g) == TRUE) && (numMJ == 0) || (numMTV == 0)) {  // If no independent campus res, build ARC. 
        a.actionCode = OBTAIN_ARC;                                         
    } else if (checkArc (g) == FALSE) {                                    // If no res for ARC, turn PASS.
        a.actionCode = PASS;
    }

    if ((checkArc (g) == TRUE) && (numMJ == 0) || (numMTV == 0) {
        a.actionCode = PASS;
    }
    return a;
}

/* AI checks ARC resources */
int checkArc (Game g) {
    int returnValue;
    // check each ARC resource
    int numBPS = getStudents (g, getWhoseTurn (g), STUDENT_BPS);
    int numBQN = getStudents (g, getWhoseTurn (g), STUDENT_BQN);

    if (numBQN >= 1 && numBPS >= 1) {
        returnValue = TRUE;   
    } else {
        returnValue = FALSE; // or nextAction?
    }
    return returnValue;
}

/* AI checks CAMPUS resources */
int checkCampus (Game g) {
    int returnValue;
    // check each CAMPUS resource
    int numBPS = getStudents (g, getWhoseTurn (g), STUDENT_BPS);
    int numBQN = getStudents (g, getWhoseTurn (g), STUDENT_BQN);
    int numMJ = getStudents (g, getWhoseTurn (g), STUDENT_MJ);
    int numMTV = getStudents (g, getWhoseTurn (g), STUDENT_MTV);

    if (numBQN >= 1 && numBPS >= 1 && numMJ >= 1 && numMTV >= 1) {
        returnValue = TRUE;    
    } else {
        returnValue = FALSE;
    }
    return returnValue;
}




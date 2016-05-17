/* Mechanical Turk.c 
   This was done by our group of 3
   Venkatesh Vasudevan 
   Dovid Riesenberg
   Brian Lam
   Our AI is gonna beat all the other Ai
   To shreds
*/

/*  COMMENTs
* Build ARC to extend territory, and then campuses
* STUDENT_BPS + STUDENT_BQN= OBTAIN_ARC  
*
* Problem: How do we direct the AI?
* Jordan's advice: (1) Can I buy X? (2) What do I need to buy? (3) Where do I want to be?
  
*/

// declarations
int isLegalFunction ();
int buildArcFunction ();
int buildCampusFunction ();
int buildXXX ();

// AI strategy #1
void executionFunction (Game g) {
	// build this, else pass
    // build this, else pass
    // build this, else pass    
}

// AI checks resources, builds ARC
int buildArc (Game g) {
    action a;
    if (getStudents (g, getWhoseTurn (g), (STUDENT_BQN>= 1) && (STUDENT_BPS >= 1))) {
        a.actionCode = OBTAIN_ARC;
    } 
    return a;
}

// AI checks resources, builds CAMPUS
int buildCampus (Game g) {
    action a;
    if (getStudents (g, getWhoseTurn (g), ((STUDENT_BQN >= 1) && (STUDENT_BPS >= 1) && (STUDENT_MJ >= 1) && (STUDENT_MTV >= 1))) {
        action.actionCode = BUILD_CAMPUS;s
    }
    return a;
}

// AI checks if action is legal or not
int checkAction (Game g) {

}





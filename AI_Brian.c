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

// AI execution
executionFunction (Game g) {
	// build this, else pass
  // build this, else pass
  // build this, else pass
}

// AI build ARC
int buildArcFunction (Game g) {
  if ((STUDENT_BQN >= 1) && (STUDENT_BPS >= 1)) {
    action.actionCode = OBTAIN_ARC;
  } else {
    action.actionCode = PASS;
  }
  return actionCode;
}
  
// AI build CAMPUS
int buildCampusFunction (Game g) {
  if ((STUDENT_BQN >= 1) && (STUDENT_BPS >= 1) && ((STUDENT_MJ >= 1) && (STUDENT_MTV >= 1)) {
    action.actionCode = BUILD_CAMPUS;
  } else {
    action.actionCode = PASS;
  }
  return actionCode;
}

// AI isLegalFunction
int isLegalFunction (Game g) {


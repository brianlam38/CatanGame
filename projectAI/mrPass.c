/*
 *  Mr Pass.  Brain the size of a planet!
 *
 *  Proundly Created by Richard Buckland
 *  Share Freely Creative Commons SA-BY-NC 3.0. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

action decideAction (Game g) {
  action nextAction;
  if ((STUDENT_MJ >= 1) && (STUDENT_MTV >= 1) && (STUDENT_MMONEY >= 1)){
     nextAction.actionCode = START_SPINOFF;
  } else {
   nextAction.actionCode = PASS;
  }
   return nextAction;
}
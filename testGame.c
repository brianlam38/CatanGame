#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "Game.h"

#define PATH_LIMIT 150

/* Function declarations
int getCampus(Game g, path pathToVertex); // return the contents of the given vertex (ie campus code or // VACANT_VERTEX) 
int getARC (Game g, path pathToEdge); // the contents of the given edge (ie ARC code or vacent ARC)
int getDiscipline (Game g, int regionID);
int getDiceValue (Game g, int regionID);
*/

void getCampus (void); 

int main (int argc, char *argv[]) {

assert (getCampus(Game g, pcath pathToVertex) == VACANT_VERTEX); // 0
assert (getCampus(Game g, path pathToVertex) == CAMPUS_A);		// 1
assert (getCampus(Game g, path pathToVertex) == CAMPUS_B);		// 2
assert (getCampus(Game g, path pathToVertex) == CAMPUS_C);		// 3
assert (getCampus(Game g, path pathToVertex) == GO8_A);         // 4
assert (getCampus(Game g, path pathToVertex) == GO8_B); 		// 5
assert (getCampus(Game g, path pathToVertex) == GO8_C); 		// 6

return EXIT_SUCCESS;
}

void getCampus (void) {

}

// Game is a TYPE. Variable = g
// path is "probably" a TYPE. Variable = pathToVertex
// (1) Write a few tests on the initial game state including at least one test for:
// (2) Write a few tests to demonstrate how you might test throwDice and makeAction.




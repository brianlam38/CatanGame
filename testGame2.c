#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define PATH_LIMIT 150

// Game is a TYPE. Variable = g
// path is "probably" a TYPE. Variable = pathToVertex

// (1) Write a few tests on the initial game state including at least one test for:
// (2) Write a few tests to demonstrate how you might test throwDice and makeAction.

/* Function declarations */
int getCampus(Game g, path pathToVertex); // return the contents of the given vertex (ie campus code or // VACANT_VERTEX) 
int getARC(Game g, path pathToEdge); // the contents of the given edge (ie ARC code or vacent ARC)
int getDiscipline (Game g, int regionID);
int getDiceValue (Game g, int regionID);

/* ASSERTS */
assert (getCampus(Game g, path pathToVertex) == VACANT_VERTEX); // 0
assert (getCampus(Game g, path pathToVertex) == CAMPUS_A);		// 1
assert (getCampus(Game g, path pathToVertex) == CAMPUS_B);		// 2
assert (getCampus(Game g, path pathToVertex) == CAMPUS_C);		// 3
assert (getCampus(Game g, path pathToVertex) == GO8_A);         // 4
assert (getCampus(Game g, path pathToVertex) == GO8_B); 		// 5
assert (getCampus(Game g, path pathToVertex) == GO8_C); 		// 6





int main (int argc, char *argv[]){

return EXIT_SUCCESS;
}




EXTRA INFO

// Example assert from Doomsday
// assert (dayOfWeek (THURSDAY,  FALSE,  4,  4) == THURSDAY);

--> Game g
// newGame (disciplines, dice);
// Make a new game, given the disciplines produced by each region
// and the value on the dice discs in each region.
--> path pathToVertex
// a path is a sequence of L=left R=right B=back steps
// starting from the initial campus of player 1 / A at the top 
// of the map facing inwards represented as a string of length 
// PATH_LIMIT or less (including the terminating 0).  
// a path can specify a vertex (the vertex at the end of the path)
// and a path can specify an ARC (the last ARC in the path)
// it is fine and legal for a path to not be the shortest path
// to the destination, it can even contain loops if you like.
// The length of a path (including the terminating 0) must never 
// exceed PATH_LIMIT.  Every edge in the path must lie on the 		// PATH_LIMIT = 150
// island, paths cannot include edges which are in the sea.

CONTENTS OF A VERTEX MAY INCLUDE:













#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "game.h"

// user defined
#define NUM_DISCIPLINES  6
#define NUM_ARCS        72
#define NUM_VERTICES    54

/* game.h defines - take out later */
#define NUM_UNIS 3

// player ID of each university
#define NO_ONE 0
#define UNI_A  1
#define UNI_B  2
#define UNI_C  3

// disciplines
#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5

/* uni RESOURCES DATA - Each index represents a data value for each uni */
typedef struct _uni {
    int students[NUM_UNIS * NUM_DISCIPLINES];   // 0 to 15 index
    int KPI[NUM_UNIS];                          // 0 to 2 index
    int arcs[NUM_UNIS]; 
    int campuses[NUM_UNIS]; 
    int GO8[NUM_UNIS];
    int IPs[NUM_UNIS];  
    int publications[NUM_UNIS];
} uni;

/* GAME DATA */
typedef struct _game {
    int diceValue;
    int discipline;
    int currentTurn;
    int whoseTurn;
   	uni *resources;
    int mostArcs;
    int mostPubs;
    edge *edgeData;
    vertex *vertexData;
} game;

/* EDGE DATA - PATHING STRUCT 1 */
typedef struct _edge {                  // Not sure how to represent this yet
    int edgeID[NUM_ARCS]
} edge;

/* VERTEX DATA - PATHING STRUCT 2 */
typedef struct _vertex {
    int vertexID[NUM_VERTICES]                        // An array of VERTEX IDs (representing each vertex on the board)
} vertex;

/* ACTIONS DATA */
typedef struct _action {
   int actionCode;          // see #defines in game.h
   path destination;        // if the action operates on a vertex or ARC this
                            // specifies *which* vertex or path. Unused otherwise
   int disciplineFrom;      // used for the retrain students action
   int disciplineTo;        // used for the retrain students action
} action;

/* DECLARE STATIC FUNCTIONS - Functions unique to this game */
static void disposeGameData (Game g) {      // EXAMPLE Free game struct data
}

static void disposePlayerData (uni player) {     // EXAMPLE Free player struct data
}
						

/* SETTERS - Functions which change the game */
Game newGame (int discipline[], int dice[]) {           // BRIAN
    Game g = malloc (sizeof (game))                     // Setting memory for game
    g.currentTurn = -1;                                 // Initialise game
    g.discipline = malloc (sizeof (int) * NUM_REGIONS); // Set memory for game board disciplines
    g.diceValue = malloc (sizeof (int) * NUM_REGIONS)); // Set memory for dice rolls

    int i = 0;
    while (i < NUM_REGIONS) {                           // Matching struct data with interface inputs    
        g.discipline[i] = discipline[i];
        g.diceValue[i] = dice[i];
        i++;
    }

    g->resources = malloc (sizeof (uni));            // Set memory for player resources struct

    g->edgeData = malloc (sizeof (edge));               // Set memory for edge data
    g->vertexData = malloc (sizeof (vertex));           // Set memory for vertex data


    /* Insert code for starting player campuses */
    /* Insert code for starting player's surrounding discipline types??? */

    return g;
}

void disposeGame (Game g) {	    // BRIAN
    assert (g != NULL);         // Checks that game data exists                                    

    free (g.diceValue);         // Free each allocation of game data
    free (g.discipline);
    free (g.currentTurn);
    free (g.whoseTurn;
    free (g.mostArcs);
    free (g.mostPubs);
    //free (g.uni)              // Free player data - MAY NOT NEED

    free (edge.edgeID);         // Free edgeID data
    free (vertex.vertexID);     // Free vertexID data

    free (g);                   // Free created game memory last so 
                                // there are no memory leakages

    g = NULL;                   // Sets game data to null
}

void makeAction (Game g, action a);						            // MEHRI

void throwDice (Game g, int diceScore);			           			// MEHRI

/* GAME BOARD GETTERS - Functions which get game board data */
int getDiscipline (Game g, int regionID) {				        	// DAVID
	return g-> discipline[region ID];
}

int getDiceValue (Game g, int regionID) {				           	// DONE (SHARON)
	return g-> diceValue[regionID];
}

int getMostARCs (Game g) {								            // VEN
   int mostARCs = g->mostARCs;
   
   if (getARCs(g, UNI_A) > getARCs(g, mostARCs)) {
      mostARCs = UNI_A;
   }
   if (getARCs(g, UNI_B) > getARCs(g, mostARCs)) {
      mostARCs = UNI_B;
   }
   if (getARCs(g, UNI_C) > getARCs(g, mostARCs)) {
      mostARCs = UNI_C;
   }
   return mostARCs;
}

int getMostPublications (Game g) {							         // DONE (SHARON)
   int mostPubs = g->mostPublications;
 
   if (getPublications(g, UNI_A) > getPublications(g, mostPubs)) {
      mostPubs = UNI_A;
   }
   if (getPublications(g, UNI_B) > getPublications(g, mostPubs)) {
      mostPubs = UNI_B;
   }
   if (getPublications(g, UNI_C) > getPublications(g, mostPubs)) {
      mostPubs = UNI_C;
   }
   return mostPubs;
}

int getTurnNumber (Game g) {								         // DONE (SHARON)
   return g->currentTurn;
}

int getWhoseTurn (Game g) {									         // DONE (SHARON)
   return g->whoseTurn;
}

int getCampus(Game g, path pathToVertex) {				        	 // DONE (BRIAN)
	int vertexElement = 0;                                           // NEEDS CHANGES TO REFLECT NEW MAP STRUCTURE
	int returnValue = 0;

	vertexElement = getVertexArrayFunction(v);

	if (vertexElement = -1) { // -1 is an illegal vertex
		returnValue = -1;
	} else {
		returnValue = g->getVertexArrayFunction[vertexElement];
	}
	return returnValue;
}

int getARC(Game g, path pathToEdge);						         // VEN

int isLegalAction (Game g, action a);					             // VEN




/* PLAYER INFO GETTERS - Functions which get specific player data */

int getKPIpoints (Game g, int player);					            	// MEHRI

int getARCs (Game g, int player);						               	// VEN

int getGO8s (Game g, int player) {						               	// BRIAN
    int numGO8 = 0;
    int i = 0;

    while (i < NUM_VERTICES) {
        player.GO8[player] = returnValue;
    }
    i++;
    return returnValue;
}


int getCampuses (Game g, int player);					            	// BRIAN
	int i = 0;
	int numCampus = 0;

	while (i < NUM_VERTICES) {
		;
	}
	counter++;
	return returnValue;
}

int getIPs (Game g, int player) {							            // DONE
    return g.uni[player].IPs
}


int getPublications (Game g, int player);				             	// DONE
    int i = 0
    int 

int getStudents (Game g, int player, int discipline);	    	        // DAVID

int getExchangeRate (Game g, int player, 					            // DAVID
                     int disciplineFrom, int disciplineTo);



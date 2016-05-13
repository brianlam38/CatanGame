#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "game.h"

/* PLAYER RESOURCES DATA */
typedef struct _player {
    int students[13]
    int KPI;
    int arcs;
    int campuses;
    int GO8;
    int IPs;
    int publications;
} player;

/* GAME DATA */
typedef struct _game {
    int diceValue;
    int discipline;
    int currentTurn;
    int whoseTurn;
   	int player;
    int mostArcs;
    int mostPubs;
} game;

/* EDGE DATA - PATHING STRUCT 1 */
typedef struct _edge {                  // Not sure how to represent this yet
    int edgeID
} edge;

/* VERTEX DATA - PATHING STRUCT 2 */
typedef struct _vertex {
    int vertexID                        // An array of VERTEX IDs (representing each vertex on the board)
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

static void disposePlayerData (player) {     // EXAMPLE Free player struct data
}
						

/* SETTERS - Functions which change the game */
Game newGame (int discipline[], int dice[]) {           // BRIAN
    Game g = malloc (sizeof (game))                     // Setting memory for game
    g.currentTurn = -1;                                 // Initialise game
    g.discipline = malloc (sizeof (int) * NUM_REGIONS); // Setting memory for game board disciplines
    g.diceValue = malloc (sizeof (int) * NUM_REGIONS)); // Setting memory for dice rolls

    int i = 0;
    while (i < NUM_REGIONS) {                           // Setting struct data = interface inputs    
        g.discipline[i] = discipline[i];
        g.diceValue[i] = dice[i];
        i++;
    }

    /* Insert code for edge data (set aside memory) */
    /* Insert code for vertex data (set aside memory) */
    /* Insert code for starting player campuses */
    /* Insert code for starting player's surrounding discipline types??? */

    return g;
}

void disposeGame (Game g) {	    // BRIAN
    free (g);                   // Free created game memory                                      

    free (g.diceValue);   
    free (g.discipline);
    free (g.currentTurn);
    free (g.whoseTurn;
    free (g.player);
    free (g.mostArcs);
    free (g.mostPubs);

    free (player.students); 
    free (player.KPI);
    free (player.campuses);
    free (player.GO8);
    free (player.IPs);
    free (player.publications);

    free (edge.edgeID);         // Free edge struct data   
    free (vertex.vertexID);     // Free vertex struct data

typedef struct _player {
    int students[13]
    int KPI;
    int arcs;
    int campuses;
    int GO8;
    int IPs;
    int publications;
} player;

/* GAME DATA */
typedef struct _game {
    int diceValue;
    int discipline;
    int currentTurn;
    int whoseTurn;
    int player;
    int mostArcs;
    int mostPubs;
} game;
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
	int vertexElement = 0;
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

int getGO8s (Game g, int player);						               	// BRIAN

int getCampuses (Game g, int player);					            	// BRIAN
	int counter = 0;
	int numCampus = 0;

	while (counter < NUM_VERTICES) {
		;
	}
	counter++;
	return returnValue;
}

int getIPs (Game g, int player) {							            // DONE
    return g.player[player].IPs
}


int getPublications (Game g, int player);				             	// DONE

int getStudents (Game g, int player, int discipline);	    	        // DAVID

int getExchangeRate (Game g, int player, 					            // DAVID
                     int disciplineFrom, int disciplineTo);



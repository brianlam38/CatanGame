#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "game.h"

/* PLAYER RESOURCES DATA */
typedef struct _player {
    int students[13]
    int KPI;
    int arcs;
    int Campuses;
    int G08;
    int IPs;
    int publications;
} player;

/* GAME DATA */
typedef struct _game {
    int diceValue;
    int discipline;
    int currentTurn;
    int whoseTurn;
    // int arcs; --> put in a EDGE struct for pathing data
    // int vertices; --> put in a VERTEX struct for pathing data
   	int player;
    int mostArcs;
    int mostPubs;
} game;

/* ACTIONS DATA */
typedef struct _action {
   int actionCode;  // see #defines above
   path destination; // if the action operates on a vertex or ARC this
                     // specifies *which* vertex or path.  unused 
                     // otherwise
   int disciplineFrom;  // used for the retrain students action
   int disciplineTo;    // used for the retrain students action
} action;

/* EDGE DATA - PATHING STRUCT 1 */
typedef struct _edge {   
} edge;

/* VERTEX DATA - PATHING STRUCT 2 */
typedef struct _vertex {
} vertex;
						

/* SETTERS - Functions which change the game */
Game newGame (int discipline[], int dice[]) {		        		// BRIAN




}

void disposeGame (Game g);						                			// BRIAN

void makeAction (Game g, action a);						             	// MEHRI

void throwDice (Game g, int diceScore);			           			// MEHRI

/* GAME BOARD GETTERS - Functions which get game board data */
int getDiscipline (Game g, int regionID) {				        	// DAVID
	return g-> discipline[region ID];
}

int getDiceValue (Game g, int regionID) {				           	// DONE (SHARON)
	return g-> diceValue[regionID];
}

int getMostARCs (Game g) {								                	// VEN
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

int getMostPublications (Game g) {							             // DONE (SHARON)
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
int getTurnNumber (Game g) {								                // DONE (SHARON)
   return g->currentTurn;
}

int getWhoseTurn (Game g) {									                // DONE (SHARON)
   return g->whoseTurn;
}
int getCampus(Game g, path pathToVertex) {				        	// DONE (BRIAN)
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

int getARC(Game g, path pathToEdge);						            // VEN

int isLegalAction (Game g, action a);					              // VEN




/* PLAYER INFO GETTERS - Functions which get specific player data */

int getKPIpoints (Game g, int player);					           	// MEHRI

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

int getIPs (Game g, int player) {							              // DONE
    return g.player[player].IPs
}


int getPublications (Game g, int player);				           	// DONE

int getStudents (Game g, int player, int discipline);	    	// DAVID

int getExchangeRate (Game g, int player, 					          // DAVID
                     int disciplineFrom, int disciplineTo);



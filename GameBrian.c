#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "game.h"

// player resources data (disciplines, publications, IPs)
typedef struct _playerResources {
	int *disciplineArray[6] = {THD, BPS, BQN, MJ, MTV, MMONEY}; // type int due to #define in game.h
	int publications;
	int IPs;
} playerResources;

// game data
typedef struct _game {
	// data type 1
	// data type 2
	// data type 3
	// data type 4
} game;

// returns the content of the given vertex (campus code or VACANT_VERTEX)
void getCampus (Game g, "insert getVertexArrayFunction + var input") {
	int vertexElement = 0;
	int returnValue = 0;

	vertexElement = getVertexArrayFunction(v);

	if (vertexElement = -1) {	// illegal vertex, does not correspond to any vertex array index
		returnValue = -1;
	} else {
		returnValue = g->getVertexArrayFunction[vertexElement];
	}

	return returnValue;
}

// returns the no. of normal campuses that a specified player currently has
void getCampuses (Game g, "insert getVertexArrayFunction + var input") {
	int vertexElement = 0;
	int returnValue = 0;

	return returnValue;
}









// getVertexArrayIndex () is a function that returns an element value within a Vertex Array (array of vertex values???)

/* EXAMPLE CODE BELOW */

static int getVertexArrayIndex (vertex v) {
    int result = 0;
    
    Game dummy = NULL;
    
    if (areHexAdjacent (v.region0, v.region1, v.region2)
     && !(isSea (dummy, v.region0) && isSea (dummy, v.region1) && isSea (dummy, v.region2))) {  //is a real vertex
        
        if (v.region0.x == v.region1.x) {  //regions 0 & 1 are vertically adjacent so region 2 must be to one side (but which?)
            if (v.region2.x > v.region0.x) {  //region 2 is to the left (catagory 1: Right Handed)
                if (v.region2.x == -2) {  //col 1
                    result = v.region2.y;
                } else if (v.region2.x == -1) {  //col 2
                    result = v.region2.y + 4;
                } else if (v.region2.x == 0) {  //col 3
                    result = v.region2.y + 9;
                } else if (v.region2.x == 1) {  //col 4
                    result = v.region2.y + 15;
                } else if (v.region2.x == 2) {  //col 5
                    result = v.region2.y + 21;
                } else if (v.region2.x == 3) {  //col 6
                    result = v.region2.y + 26;
                }
            } else {  //region 2 is to the right (category 2: Left Handed)
                if (v.region2.x == -3) {  //col 1
                    result = v.region2.y + 27;
                } else if (v.region2.x == -2) {  //col 2
                    result = v.region2.y + 32;
                } else if (v.region2.x == -1) {  //col 3
                    result = v.region2.y + 38;
                } else if (v.region2.x == 0) {  //col 4
                    result = v.region2.y + 44;
                } else if (v.region2.x == 1) {  //col 5
                    result = v.region2.y + 49;
                } else if (v.region2.x == 2) {  //col 6
                    result = v.region2.y + 53;
                }
            }
        } else if (v.region0.x == v.region2.x) {  //regions 0 & 2 are vertically adjacent so region 1 is to one side
            if (v.region1.x > v.region0.x) {  //(cat 1)
                if (v.region1.x == -2) {  //col 1
                    result = v.region1.y;
                } else if (v.region1.x == -1) {  //col 2
                    result = v.region1.y + 4;
                } else if (v.region1.x == 0) {  //col 3
                    result = v.region1.y + 9;
                } else if (v.region1.x == 1) {  //col 4
                    result = v.region1.y + 15;
                } else if (v.region1.x == 2) {  //col 5
                    result = v.region1.y + 21;
                } else if (v.region1.x == 3) {  //col 6
                    result = v.region1.y + 26;
                }
            } else {  //(cat 2)
                if (v.region1.x == -3) {  //col 1
                    result = v.region1.y + 27;
                } else if (v.region1.x == -2) {  //col 2
                    result = v.region1.y + 32;
                } else if (v.region1.x == -1) {  //col 3
                    result = v.region1.y + 38;
                } else if (v.region1.x == 0) {  //col 4
                    result = v.region1.y + 44;
                } else if (v.region1.x == 1) {  //col 5
                    result = v.region1.y + 49;
                } else if (v.region1.x == 2) {  //col 6
                    result = v.region1.y + 53;
                }
            }
        } else {  //region 0 is to one side
            if (v.region0.x > v.region1.x) {  //(cat 1)
                if (v.region0.x == -2) {  //col 1
                    result = v.region0.y;
                } else if (v.region0.x == -1) {  //col 2
                    result = v.region0.y + 4;
                } else if (v.region0.x == 0) {  //col 3
                    result = v.region0.y + 9;
                } else if (v.region0.x == 1) {  //col 4
                    result = v.region0.y + 15;
                } else if (v.region0.x == 2) {  //col 5
                    result = v.region0.y + 21;
                } else if (v.region0.x == 3) {  //col 6
                    result = v.region0.y + 26;
                }
            } else {  //(cat 2)
                if (v.region0.x == -3) {  //col 1
                    result = v.region0.y + 27;
                } else if (v.region0.x == -2) {  //col 2
                    result = v.region0.y + 32;
                } else if (v.region0.x == -1) {  //col 3
                    result = v.region0.y + 38;
                } else if (v.region0.x == 0) {  //col 4
                    result = v.region0.y + 44;
                } else if (v.region0.x == 1) {  //col 5
                    result = v.region0.y + 49;
                } else if (v.region0.x == 2) {  //col 6
                    result = v.region0.y + 53;
                }
            }
        }
    } else {  //is not a real vertex
        result = -1;
    }
    
    return result;
}
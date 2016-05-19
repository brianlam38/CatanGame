/*
 *  Game.c
 *  1917 2013 ver 0.0.1
 *  Add to and change this file as you wish to implement the
 *  interface functions in Game.h
 *
 *  Created by Richard Buckland on 2/5/2013 (modified by the team of Thursday-11-Moog(13s1) 17/05/2013)
 *  Licensed under Creative Commons SA-BY-NC 3.0. *
 */

#define DEBUG

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#ifdef DEBUG
    #include <stdio.h>
#endif

#include "Game.h"

#define NUM_ARCS     72
#define NUM_VERTICES 54
#define NUM_UNIS      3

#define INITIAL_CAMPUS_A1 12
#define INITIAL_CAMPUS_A2 41
#define INITIAL_CAMPUS_B1  2
#define INITIAL_CAMPUS_B2 51
#define INITIAL_CAMPUS_C1 26
#define INITIAL_CAMPUS_C2 27

#define ARCMULT       2
#define MOSTPUBSMULT 10
#define MOSTARCSMULT 10
#define CAMPUSMULT   10
#define GO8MULT      20
#define IPMULT       10

typedef struct _uniRes {
    int thD, bPs, bQn, mJ, mTv, mMoney;
    int iPs;
    int pubs;
} uniRes;

// your tutorial class designs this type (not us)
// store in this struct all the things you might want to know about
// the Game so you can write the interface functions in this header
// eg you might want to store the current turn number (so i've put
// it in for you as an example but take it out if you don't want it)
typedef struct _game {
    // your group puts here the details of the data
    // you want to store in the _game struct
    int *degrees;
    int *dice;
    int currentTurn;
    int *arcs;
    int *vertices;
    uniRes *players;
    uni lastMostArcs;
    uni lastMostPubs;
} game;

//returns the index of the degree[] and dice[] arrays corespoinding to a given region
static int getHexArrayIndex (region r); //(y)
static int isHexAdjacent (region r1, region r2); //(y)
static int areHexAdjacent (region r1, region r2, region r3); //(y)
static int getArcArrayIndex (arc a); //(y)
static int getVertexArrayIndex (vertex v); //(y)
static void clearIntArray (int* pointer, int length); //(y)
static int getStudentMultiplier (Game g, uni player, int regionIndex); //(y)
static region getHexCoords (int regionIndex);  //(y)
static vertex* getAdjacentVertices (vertex v);  //(y)
static arc* getAdjacentArcs (vertex v);  //(y)
static arc* getAdjacentArcsToArc (arc a);  //(y)
static vertex* getAdjacentVerticesToArc (arc a);
static vertex makeVertex (int* coords);  //(y)
static int getTotalGO8s (Game g);  //(y)
static double max (double a, double b);  //(y)

#ifdef DEBUG
    void testGetHexArrayIndex (void);
    void testIsHexAdjacent (void);
    void testAreHexAdjacent (void);
    void testGetArcArrayIndex (void);
    void testGetVertexArrayIndex (void);
    void testClearIntArray (void);
    void testGetStudentMultiplier (void);
    void testGetHexCoords (void);
    void testGetAdjacentVertices (void);
    void testGetAdjacentArcs (void);
    void testGetAdjacentArcsToArc (void);
    void testGetAdjacentVerticesToArc (void);
    void testMakeVertex (void);
    void testGetTotalGO8s (void);
    void testMax (void);
#endif

/* **** Functions which change the Game aka SETTERS **** */
// given a Game this function makes it a new Game, resetting everything and
// setting the type of degree produced by each
// region, and the value on the dice discs in each region.
//
Game newGame (int degree[], int dice[]) {
    Game g = malloc (sizeof (game));  // set memory aside for Game
    assert (g != NULL);                 // check it worked
    g->currentTurn = -1;               // initialise currentTurn field
    g->degrees = malloc (NUM_REGIONS*sizeof (int));
    g->dice = malloc (NUM_REGIONS*sizeof (int));
    
    #ifdef DEBUG
        testGetHexArrayIndex ();
        testIsHexAdjacent ();
        //testAreHexAdjacent ();
        //testGetArcArrayIndex ();
        //testGetVertexArrayIndex ();
        //testClearIntArray ();
        //testGetStudentMultiplier (void);
        //testGetHexCoords ();
        //testGetAdjacentVertices ();
        //testGetAdjacentArcs ();
        //testGetAdjacentArcsToArc ();
        //testGetAdjacentVerticesToArc ();
        //testMakeVertex ();
        //testGetTotalGO8s ();
        //testMax ();
    #endif
    
    int i = 0;
    
    while (i < NUM_REGIONS) {
        //printf("%d", i);
        
        g->degrees[i] = degree[i];
        g->dice[i] = dice[i];
        
        i++;
    }
    
    g->arcs = malloc (NUM_ARCS*sizeof (int));          // set memory aside for arc and vertex arrays
    clearIntArray (g->arcs, NUM_ARCS);                 // and zero them (clear memory so all arcs and vertices are vacant)
    g->vertices = malloc (NUM_VERTICES*sizeof (int));
    clearIntArray (g->vertices, NUM_VERTICES);
    
    g->vertices[INITIAL_CAMPUS_A1] = CAMPUS_A;    // set the initial campuses for A, B & C
    g->vertices[INITIAL_CAMPUS_A2] = CAMPUS_A;
    g->vertices[INITIAL_CAMPUS_B1] = CAMPUS_B;
    g->vertices[INITIAL_CAMPUS_B2] = CAMPUS_B;
    g->vertices[INITIAL_CAMPUS_C1] = CAMPUS_C;
    g->vertices[INITIAL_CAMPUS_C2] = CAMPUS_C;
    
    g->players = malloc (NUM_UNIS*sizeof (uniRes));  // allocate an array for the uniRes information
    
    i = 0;
    
    while (i < NUM_UNIS) {
        g->players[i].thD = 0;  // set initial values for each student type and attribute
        g->players[i].bPs = 3;  // for each uni
        g->players[i].bQn = 3;
        g->players[i].mJ  = 1;
        g->players[i].mTv = 1;
        g->players[i].mMoney = 1;
        
        g->players[i].iPs = 0;
        g->players[i].pubs = 0;
        
        i++;
    }
    
    g->lastMostArcs = UNI_C;
    g->lastMostPubs = UNI_C;
    
    return g;
}

// after week 8 we will talk about implementing this. for now
// you can leave it to just do this free
void disposeGame (Game g) {
    assert (g != NULL);  // check that memory has been allocated
    free (g->arcs);      // then free each allocation
    free (g->vertices);
    free (g->players);
    free (g->degrees);
    free (g->dice);
    free (g);
    g = NULL;
}

// advance the Game to the next turn,
// assuming that the dice has just been rolled and produced diceScore
// the Game starts in turn -1 (we call this state "Terra Nullis") and
// moves to turn 0 as soon as the first dice is thrown.
void throwDice (Game g, int diceScore) {
    int i = 0;
    
    while (i < NUM_REGIONS) {
        if (g->dice[i] == diceScore) {    // check all regions to test if they have
            int j = 0;                    // the given dice value
            
            while (j < NUM_UNIS) {
                if (g->degrees[i] == STUDENT_THD) {                       // for each uni, check how many students they get
                    g->players[j].thD += getStudentMultiplier (g, j, i);  // and of which type for the given region and
                } else if (g->degrees[i] == STUDENT_BPS) {                // add those to the uni's total
                    g->players[j].bPs += getStudentMultiplier (g, j, i);
                } else if (g->degrees[i] == STUDENT_BQN) {
                    g->players[j].bQn += getStudentMultiplier (g, j, i);
                } else if (g->degrees[i] == STUDENT_MJ ) {
                    g->players[j].mJ  += getStudentMultiplier (g, j, i);
                } else if (g->degrees[i] == STUDENT_MTV) {
                    g->players[j].mTv += getStudentMultiplier (g, j, i);
                } else if (g->degrees[i] == STUDENT_MMONEY) {
                    g->players[j].mMoney += getStudentMultiplier (g, j, i);
                }
                
                j++;
            }
        }
        
        i++;
    }
    
    
    if (diceScore == 7) {
        int j = 0;
        
        while (j < NUM_UNIS) {
            g->players[j].thD += g->players[j].mTv;
            g->players[j].thD += g->players[j].mMoney;
            
            g->players[j].mTv = 0;
            g->players[j].mMoney = 0;
            
            j++;
        }
    }
    
    g->currentTurn++;  // julian wrote this line it might need debugging (and has now been debugged maybe...)
}                      // i.e. increment the turn number

// make the specified action for the current player and update the
// Game state accordingly.
// The function may assume that the action requested is legal.
// START_SPINOFF is not a legal action here
void makeAction (Game g, action a) {
    uni currentPlayer = getWhoseTurn (g);

    if (a.actionCode == BUILD_CAMPUS) {
        g->players[currentPlayer].bPs--;  // uni pays for campus
        g->players[currentPlayer].bQn--;
        g->players[currentPlayer].mJ--;
        g->players[currentPlayer].mTv--;
    
        g->vertices[getVertexArrayIndex (a.targetVertex)] = currentPlayer + 1;  // build campus for uni on vertex
    } else if (a.actionCode == BUILD_GO8) {
        g->players[currentPlayer].mJ -= 2;  // uni pays for GO8
        g->players[currentPlayer].mMoney -= 3;
        
        g->vertices[getVertexArrayIndex (a.targetVertex)] = currentPlayer + 4;  // build GO8 for uni on vertex
    } else if (a.actionCode == CREATE_ARC) {
        g->players[currentPlayer].bPs--;  // uni pays fo ARC
        g->players[currentPlayer].bQn--;
        
        g->arcs[getArcArrayIndex (a.targetARC)] = currentPlayer + 1;  // build ARC for uni on ARC
    } else if (a.actionCode == OBTAIN_PUBLICATION) {
        g->players[currentPlayer].mJ--;  // uni pays for spinoff
        g->players[currentPlayer].mTv--;
        g->players[currentPlayer].mMoney--;
        
        g->players[currentPlayer].pubs++;  // uni obtains publication
    } else if (a.actionCode == OBTAIN_IP_PATENT) {
        g->players[currentPlayer].mJ--;  // uni pays for spinoff
        g->players[currentPlayer].mTv--;
        g->players[currentPlayer].mMoney--;
        
        g->players[currentPlayer].iPs++;  // uni obtains ip patent
    } else if (a.actionCode == RETRAIN_STUDENTS) {
        if (a.retrainFrom == STUDENT_BPS) {
            g->players[currentPlayer].bPs -= getExchangeRate (g, currentPlayer, a.retrainFrom, a.retrainTo);  // uni pays for retrain
        } else if (a.retrainFrom == STUDENT_BQN) {
            g->players[currentPlayer].bQn -= getExchangeRate (g, currentPlayer, a.retrainFrom, a.retrainTo);
        } else if (a.retrainFrom == STUDENT_MJ) {
            g->players[currentPlayer].mJ -= getExchangeRate (g, currentPlayer, a.retrainFrom, a.retrainTo);
        } else if (a.retrainFrom == STUDENT_MTV) {
            g->players[currentPlayer].mTv -= getExchangeRate (g, currentPlayer, a.retrainFrom, a.retrainTo);
        } else if (a.retrainFrom == STUDENT_MMONEY) {
            g->players[currentPlayer].bQn -= getExchangeRate (g, currentPlayer, a.retrainFrom, a.retrainTo);
        }
        
        if (a.retrainTo == STUDENT_THD) {
            g->players[currentPlayer].thD++;      // uni recieves retrained student
        } else if (a.retrainTo == STUDENT_BPS) {
            g->players[currentPlayer].bPs++;
        } else if (a.retrainTo == STUDENT_BQN) {
            g->players[currentPlayer].bQn++;
        } else if (a.retrainTo == STUDENT_MJ) {
            g->players[currentPlayer].mJ++;
        } else if (a.retrainTo == STUDENT_MTV) {
            g->players[currentPlayer].mTv++;
        } else if (a.retrainTo == STUDENT_MMONEY) {
            g->players[currentPlayer].mMoney++;
        }
    }
}

/* **** Functions which GET data about the Game aka GETTERS **** */

// true if the region is not one of the land regions of knowledge island
int isSea (Game g, region r) {
    int result = TRUE;
    
    //printf ("\nx,y: (%d, %d)\n", r.x, r.y);
    
    if ((r.x >= -2) && (r.x <= 2) && (r.y >= -2) && (r.y <= 2) && (r.x + r.y >= -2) && (r.x + r.y <= 2)) {
        result = FALSE;
    }
    
    //printf ("result: %d\n", result);
    
    return result;
}

// what type of students are produced by the specified land region?
// see degree discipline codes above
degree getDegree (Game g, region r) {
    degree result;
    
    if (getHexArrayIndex (r) == -1) {
        result = -1;
    } else {
        result = g->degrees[getHexArrayIndex (r)];
    }
    
    return result;
}

// what dice value produces students in the specified land region?
// 2..12
int getDiceValue (Game g, region r) {
    int result;
    
    if (getHexArrayIndex (r) == -1) {
        result = -1;
    } else {
        result = g->dice[getHexArrayIndex (r)];
    }
    
    return result;
}

// which university currently has the prestige award for the most ARCs?
// this deemed to be UNI_C at the start of the Game.
uni getMostARCs (Game g) {
    uni result = g->lastMostArcs;
    int i = 0;
    
    while (i < NUM_UNIS) {
        if (getARCs (g, UNI_B) > getARCs (g, result)) {
            result = i;
        }
        
        i++;
    }
    
    g->lastMostArcs = result;
    
    return result;
}

// which university currently has the prestige award for the most pubs?
// this is deemed to be UNI_C at the start of the Game.
uni getMostPublications (Game g) {
    uni result = g->lastMostPubs;
    int i = 0;
    
    while (i < NUM_UNIS) {
        if (getPublications (g, i) > getPublications (g, result)) {
            result = i;
        }
        
        i++;
    }
    
    g->lastMostPubs = result;
    
    return result;
}

// return the current turn number of the Game -1,0,1, ..
int getTurnNumber (Game g) {
    return g->currentTurn;
}

// return the player id of the player whose turn it is
// the result of this function is UNI_C during Terra Nullis
uni getWhoseTurn (Game g) {
    uni whoseTurn;
    
    if (g->currentTurn == -1) {
        whoseTurn = UNI_C;
    } else {
        whoseTurn = g->currentTurn % NUM_UNIS;
    }
    
    return whoseTurn;
}

// return the contents of the given vertex (ie campus code or
// VACANT_VERTEX)
int getCampus (Game g, vertex v){   
    int elementVal = 0;
    int returnVal = 0;   
    
    elementVal = getVertexArrayIndex(v); //tristans awesome function which returns an element value
    
    if (elementVal == -1) {
        returnVal = -1;
    } else {    
        returnVal = g->vertices[elementVal]; //contents of the element (ie what occupies a vertex)
    }
    
    return (returnVal);
}

// the contents of the given edge (ie ARC code or vacent ARC)
int getARC (Game g, arc a) { // returns whos arc is located on a line or if its a free arc
    int returnVal = 0;
    int elementVal = 0;
    
    elementVal = getArcArrayIndex (a);
    
    if (elementVal == -1) {
        returnVal = -1;
    } else {    
        returnVal = g->arcs[elementVal];
    }
    
    return (returnVal);
}

// returns TRUE if it is legal for the current player
// to make the specified move, FALSE otherwise.
// legal means everything is legal eg when placing a campus consider
// such things as:
//   * is the specified vertex a valid land vertex?
//   * is it vacant?
//   * under the rules of the Game is the current player allowed to
//     place a campus at that vertex?  (eg is it adjacent to one of
//     their ARCs?)
//   * does the player have the 4 specific students required to pay for
//     that campus?
// It is not legal to make any action during Terra Nullis ie
// before the Game has started.
// It is not legal for a player to make the moves OBTAIN_PUBLICATION
// or OBTAIN_IP_PATENT (they can make the move START_SPINOFF)
//
int isLegalAction (Game g, action a) {
    // Set intial state of isLegal to false. Only set on valid conditions
    int isLegal = FALSE;

    #ifdef DEBUG
        printf ("entering isLegalAction...\n");
    #endif

    if ((a.actionCode >= PASS) && (a.actionCode <= MAX_LEGAL_ACTION)) {  // Is the action code valid?
        
        #ifdef DEBUG
            printf ("recognizes actionCode...\n");
        #endif
        
        if (g->currentTurn != -1) {  // Is the game in 'Terra Nullis' mode?
            
            
            if (a.actionCode == PASS) {  // If the turn is a pass, the action is always valid
                isLegal = TRUE;
            
            
            } else if (a.actionCode == BUILD_CAMPUS) {  // Validate a 'build campus'
                
                #ifdef DEBUG
                    printf ("actionCode is BUILD_CAMPUS...\n");
                    printf ("vertexArrayIndex: %d\n", getVertexArrayIndex (a.targetVertex));
                #endif
                
                vertex v = a.targetVertex;
                vertex *adjVerts = getAdjacentVertices (v);
                arc *adjArcs = getAdjacentArcs (v);

                if (getVertexArrayIndex (v) != -1) {  // is a legal vertex corresponding to an array index
                
                    #ifdef DEBUG
                        printf ("is legit vertex...\n");
                    #endif
                    
                    if (getCampus (g, v) == VACANT_VERTEX) {  // the vertex is not already occupied
                        if (getARC (g, adjArcs[0]) == getWhoseTurn (g) + 1
                         || getARC (g, adjArcs[1]) == getWhoseTurn (g) + 1
                         || getARC (g, adjArcs[2]) == getWhoseTurn (g) + 1) {  // the uni must own an arc to this vertex    
                            if (getCampus (g, adjVerts[0]) == VACANT_VERTEX
                             && getCampus (g, adjVerts[1]) == VACANT_VERTEX
                             && getCampus (g, adjVerts[2]) == VACANT_VERTEX) {  // are all adjacent vertices free?
                                if (g->players[getWhoseTurn (g)].bPs >= 1
                                 && g->players[getWhoseTurn (g)].bQn >= 1     // can the uni afford
                                 && g->players[getWhoseTurn (g)].mJ  >= 1     // to build this campus?
                                 && g->players[getWhoseTurn (g)].mTv >= 1) {
                             
                                    isLegal = TRUE;
                                }
                            }
                        }
                    }
                }
            
            
            } else if (a.actionCode == BUILD_GO8) {  // Validate a 'build GO8'
                vertex v = a.targetVertex;

                if (getVertexArrayIndex (v) != -1) {  // is a legal vertex corresponding to an array index
                    if (getCampus (g, v) == getWhoseTurn (g) + 1) {  // the uni must already have a normal campus on this vertex!!
                        if (getTotalGO8s (g) < 8) {  // check that there are not already too many GO8s
                            if (g->players[getWhoseTurn (g)].mJ >= 2         // can the uni afford
                             && g->players[getWhoseTurn (g)].mMoney >= 3) {  // to build this campus?
                                 
                                isLegal = TRUE;
                            }
                        }
                    }
                }
            
            
            } else if (a.actionCode == CREATE_ARC) {  // Validate a 'create arc'
                
                #ifdef DEBUG
                    printf ("actionCode is CREATE_ARC...\n");
                    printf ("arcArrayIndex: %d\n", getArcArrayIndex (a.targetARC));
                #endif
                
                if (getArcArrayIndex (a.targetARC) != -1) {  // is a legal arc corresponding to an array index
                    
                    #ifdef DEBUG
                        printf ("is a legit ARC...\n");
                    #endif
                    
                    if (getARC (g, a.targetARC) == VACANT_ARC) {  // check that the arc is not occupied
                        arc *adjArcs = getAdjacentArcsToArc (a.targetARC);
                        vertex *adjVerts = getAdjacentVerticesToArc (a.targetARC);
                        
                        #ifdef DEBUG
                            printf ("Arc0: ((%d, %d), (%d, %d)) Arc1: ((%d, %d), (%d, %d)) "
                                    "Arc2: ((%d, %d), (%d, %d)) Arc3: ((%d, %d), (%d, %d)) "
                                    "Arc4: ((%d, %d), (%d, %d))\n", a.targetARC.region0.x, a.targetARC.region0.y,
                                    a.targetARC.region1.x, a.targetARC.region1.y, adjArcs[0].region0.x,
                                    adjArcs[0].region0.y, adjArcs[0].region1.x, adjArcs[0].region1.y,
                                    adjArcs[1].region0.x, adjArcs[1].region0.y, adjArcs[1].region1.x,
                                    adjArcs[1].region1.y, adjArcs[2].region0.x, adjArcs[2].region0.y,
                                    adjArcs[2].region1.x, adjArcs[2].region1.y, adjArcs[3].region0.x,
                                    adjArcs[3].region0.y, adjArcs[3].region1.x, adjArcs[3].region1.y);
                        #endif
                        
                        if (getARC (g, adjArcs[0])    == getWhoseTurn (g) + 1
                         || getARC (g, adjArcs[1])    == getWhoseTurn (g) + 1     // uni must have an arc to this arc already
                         || getARC (g, adjArcs[2])    == getWhoseTurn (g) + 1
                         || getARC (g, adjArcs[3])    == getWhoseTurn (g) + 1
                         || getCampus (g, adjVerts[0]) == getWhoseTurn (g) + 1     // or a campus on one end i.e. on
                         || getCampus (g, adjVerts[1]) == getWhoseTurn (g) + 1) {  // the first turn for each uni
                            
                            if (g->players[getWhoseTurn (g)].bPs >= 1     // can the uni afford
                             && g->players[getWhoseTurn (g)].bQn >= 1) {  // to build this arc?
                            
                                isLegal = TRUE;
                            }
                        }
                    }
                }
            
            
            } else if (a.actionCode == START_SPINOFF) {  // Validate a 'spinoff'
                if (g->players[getWhoseTurn (g)].mJ  >= 1
                 && g->players[getWhoseTurn (g)].mTv >= 1        // can the uni afford
                 && g->players[getWhoseTurn (g)].mMoney >= 1) {  // to start a spinoff?
                    
                    isLegal = TRUE;
                }
            
            
            } else if (a.actionCode == RETRAIN_STUDENTS) {  // Validate a student retraining
                if ((a.retrainFrom > STUDENT_THD && a.retrainFrom <= STUDENT_MMONEY)     // retraining from a valid student (not THD)
                 && (a.retrainTo  >= STUDENT_THD && a.retrainTo   <= STUDENT_MMONEY)) {  // retraining to a valid student
                    if ((a.retrainFrom == STUDENT_BPS
                     && g->players[getWhoseTurn (g)].bPs >= getExchangeRate (g, getWhoseTurn (g), a.retrainFrom, a.retrainTo))
                     || (a.retrainFrom == STUDENT_BQN
                     && g->players[getWhoseTurn (g)].bQn >= getExchangeRate (g, getWhoseTurn (g), a.retrainFrom, a.retrainTo))    // can the student
                     || (a.retrainFrom == STUDENT_MJ                                                                              // afford to pay
                     && g->players[getWhoseTurn (g)].mJ  >= getExchangeRate (g, getWhoseTurn (g), a.retrainFrom, a.retrainTo))    // for the given
                     || (a.retrainFrom == STUDENT_MTV                                                                             // trade??
                     && g->players[getWhoseTurn (g)].mTv >= getExchangeRate (g, getWhoseTurn (g), a.retrainFrom, a.retrainTo))
                     || (a.retrainFrom == STUDENT_MMONEY
                     && g->players[getWhoseTurn (g)].mMoney >= getExchangeRate (g, getWhoseTurn (g), a.retrainFrom, a.retrainTo))) {
                        
                        isLegal = TRUE;
                    }
                }
            }
        }
    }           // all legal cases are now accounted for and return TRUE (... I hope)
    
    //free (*adjArcs);
    //free (*adjVerts);

    return isLegal;
}

// --- get data about a specified player ---

// return the number of KPI points the specified player currently has
int getKPIpoints (Game g, uni player) {
    int kpiTotal = 0;
    
    kpiTotal += ARCMULT*getARCs (g, player);  //calculates total KPI for arcs owned
    kpiTotal += CAMPUSMULT*getCampuses (g, player);  //calculates total KPI for campus owned
    kpiTotal += GO8MULT*getGO8s (g, player);  //calculates total KPI for G08s owned
    kpiTotal += IPMULT*getIPs (g, player);  //calculates total KPI for IPs owned
    
    if (getMostARCs (g) == player) {  //get most arcs returns a player.
        kpiTotal += MOSTARCSMULT;
    }
    if (getMostPublications (g) == player) {  //calculates bonus KPI for most publications
        kpiTotal += MOSTPUBSMULT;
    }
    
    return kpiTotal;
}

// return the number of ARC grants the specified player currently has
int getARCs (Game g, uni player) {    //returns the total number of ARCs held by a player
    int counter = 0;
    int arcCounter = 0;
    
    while (counter < NUM_ARCS) {
        if (g->arcs[counter] == (player + 1)) {
            arcCounter++;
        }
        
        counter++;
    }
    
    return arcCounter;
}

// return the number of GO8 campuses the specified player currently has
int getGO8s (Game g, uni player) { // returns the total number of G08's held by a player
    int counter = 0;
    int G08Count = 0;
    
    while (counter < NUM_VERTICES) {
        if (g->vertices[counter] == (player + 4)) {
            G08Count++;
        }
        
        counter++;
    }
    
    return G08Count;
}

// return the number of normal Campuses the specified player currently has
int getCampuses (Game g, uni player) {  // returns the total number of campuses held by a player
   int counter = 0;
   int campCount = 0;
   
   while (counter < NUM_VERTICES) {
      if (g->vertices[counter] == (player + 1)) {
         campCount++;
      }
      
      counter++;
   }
   
   return campCount;
}


// return the number of IP Patents the specified player currently has
int getIPs (Game g, uni player) {
    return g->players[player].iPs;
}

// return the number of Publications the specified player currently has
int getPublications (Game g, uni player) {
    return g->players[player].pubs;
}

// return the number of students of the specified discipline type
// the specified player currently has
int getStudents (Game g, uni player, degree discipline) {
    int numStudents = 0;
    
    if (discipline == STUDENT_THD) {
        numStudents = g->players[player].thD;
    } else if (discipline == STUDENT_BPS) {
        numStudents = g->players[player].bPs;
    } else if (discipline == STUDENT_BQN) {
        numStudents = g->players[player].bQn;
    } else if (discipline == STUDENT_MJ) {
        numStudents = g->players[player].mJ;
    } else if (discipline == STUDENT_MTV) {
        numStudents = g->players[player].mTv;
    } else if (discipline == STUDENT_MMONEY) {
        numStudents = g->players[player].mMoney;
    }
    
    return numStudents;
}

// return how many students of degree type tradeFrom
// the specified player would need to retrain in order to get one
// student of degree type trainTo.  This will depend
// on what retraining centers, if any, they have a campus at.
int getExchangeRate (Game g, uni player, degree tradeFrom, degree tradeTo){
    int exchangeRate = 3;
    
    int BPS1[] = {-2,  0, -2, -1, -1, -1};
    int BPS2[] = {-1, -2, -2, -1, -1, -1};
    int BQN1[] = { 2, -1,  2, -2,  3, -2};
    int BQN2[] = { 2, -1,  3, -1,  3, -2};
    int MJ1[]  = { 1, -1,  1, -2,  2, -3};
    int MJ2[]  = { 1, -2,  2, -2,  2, -3};
    int MTV1[] = {-1,  2, -1,  3,  0,  2};
    int MTV2[] = {-1,  2, -1,  3, -2,  3};
    int Mm1[]  = { 1,  1,  1,  2,  0,  2};
    int Mm2[]  = { 1,  1,  1,  2,  2,  1};
    
    int campus;
    int GO8_campus;
    
    vertex vcourse1;
    vertex vcourse2;

    // set campus to the current players campus
    if (player == UNI_A) {
        campus = CAMPUS_A;
        GO8_campus = GO8_CAMPUS_A;

    } else if (player == UNI_B) {
        campus = CAMPUS_B;
        GO8_campus = GO8_CAMPUS_B;
    } else {
        campus = CAMPUS_C;
        GO8_campus = GO8_CAMPUS_C;
    }
    
    //determines the vertex to check based on the resource 
    if (tradeTo == STUDENT_BPS) {
        vcourse1 = makeVertex (BPS1);
        vcourse2 = makeVertex (BPS2);
    } else if (tradeTo == STUDENT_BQN) {
        vcourse1 = makeVertex (BQN1);
        vcourse2 = makeVertex (BQN2);
    } else if (tradeTo == STUDENT_MJ) {
        vcourse1 = makeVertex (MJ1);
        vcourse2 = makeVertex (MJ2);
    } else if (tradeTo == STUDENT_MTV) {
        vcourse1 = makeVertex (MTV1);
        vcourse2 = makeVertex (MTV2);
    } else if (tradeTo == STUDENT_MMONEY) {
        vcourse1 = makeVertex (Mm1);
        vcourse2 = makeVertex (Mm2);
    }

    if (getVertexArrayIndex (vcourse1) != -1 && getVertexArrayIndex (vcourse2) != 0) {
        if (getCampus (g, vcourse1) == campus || getCampus (g, vcourse1) == GO8_campus
         || getCampus (g, vcourse2) == campus || getCampus (g, vcourse2) == GO8_campus) {
            
            exchangeRate = 2;
        }
    }
    
    return exchangeRate;
}

static int getHexArrayIndex (region r) {
    int result = 0;
    
    Game dummy = NULL;
    
    if (isSea (dummy, r)) {  //hex not in array
        result = -1;
    } else {  //valid hex for array
        if (r.x == -2) {
            result = r.y;
        } else if (r.x == -1) {
            result = r.y + 4;
        } else if (r.x == 0) {
            result = r.y + 9;
        } else if (r.x == 1) {
            result = r.y + 14;
        } else if (r.x == 2) {
            result = r.y + 18;
        }
    }
    
    return result;
}

static int getArcArrayIndex (arc a) {
    int result = 0;
    
    Game dummy = NULL;
    
    if (isHexAdjacent (a.region0, a.region1) && !(isSea (dummy, a.region0) && isSea (dummy, a.region1))) {  //in this case edge exists
        if (a.region0.x == a.region1.x) {  //in this case edge is horizontal
            if (a.region0.x == -2) {  //in this case edge lies in first column
                result = max (a.region0.y + 0.0, a.region1.y + 0.0);
            } else if (a.region0.x == -1) {  //in this case edge lies in second column
                result = max (a.region0.y + 0.0, a.region1.y + 0.0) + 5;
            } else if (a.region0.x == 0) {  //edge in third column
                result = max (a.region0.y + 0.0, a.region1.y + 0.0) + 11;
            } else if (a.region0.x == 1) {  //edge in fourth column
                result = max (a.region0.y + 0.0, a.region1.y + 0.0) + 17;
            } else if (a.region0.x == 2) {  //edge in last column
                result = max (a.region0.y + 0.0, a.region1.y + 0.0) + 22;
            }
        } else if (a.region0.y == a.region1.y) {  //edge is backward diagonal
            if (a.region0.y == -2) {  //in this case edge lies in lowest forward diagonal
                result = max (a.region0.x + 0.0, a.region1.x + 0.0) + 24;
            } else if (a.region0.y == -1) {  //in this case edge lies in second forward diagonal
                result = max (a.region0.x + 0.0, a.region1.x + 0.0) + 29;
            } else if (a.region0.y == 0) {  //edge in third f diagonal
                result = max (a.region0.x + 0.0, a.region1.x + 0.0) + 35;
            } else if (a.region0.y == 1) {  //edge in fourth f diag
                result = max (a.region0.x + 0.0, a.region1.x + 0.0) + 41;
            } else if (a.region0.y == 2) {  //edge in top f diag
                result = max (a.region0.x + 0.0, a.region1.x + 0.0) + 46;
            }           
        } else if (a.region0.x + a.region0.y == a.region1.x + a.region1.y) {  //edge is forward diagonal
            if (a.region0.x + a.region0.y == -2) {  //edge is in lowest backward diag
                result = max (0.0 - a.region0.x, 0.0 - a.region1.x) + 48;
            } else if (a.region0.x + a.region0.y == -1) {  //edge is in second b diag
                result = max (0.0 - a.region0.x, 0.0 - a.region1.x) + 54;
            } else if (a.region0.x + a.region0.y == 0) {  //edge is in third b diag
                result = max (0.0 - a.region0.x, 0.0 - a.region1.x) + 60;
            } else if (a.region0.x + a.region0.y == 1) {  //edge is in fourth b diag
                result = max (0.0 - a.region0.x, 0.0 - a.region1.x) + 65;
            } else if (a.region0.x + a.region0.y == 2) {  //edge is in top b diag
                result = max (0.0 - a.region0.x, 0.0 - a.region1.x) + 69;
            }
        }
    } else {  //edge does not exist!!
        result = -1;
    }
    
    return result;
}

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

static int isHexAdjacent (region r1, region r2) {
    int result = FALSE;
    
    //in this case r2 is above or below r1
    if (r1.x == r2.x && (r1.y == r2.y + 1 || r1.y == r2.y - 1)) {
        result = TRUE;
    }
    
    //in this case r2 is above and to the right or below and to the left of r1
    if (r1.y == r2.y && (r1.x == r2.x + 1 || r1.x == r2.x - 1)) {
        result = TRUE;
    }
    
    //in this case r2 is above and to the left or below and to the right of r1
    if ((r1.x == r2.x + 1 && r1.y == r2.y - 1) || (r1.x == r2.x - 1 && r1.y == r2.y + 1)) {
        result = TRUE;
    }
    
    return result;
}

static int areHexAdjacent (region r1, region r2, region r3) {
    int result = FALSE;
    
    if (isHexAdjacent (r1, r2) && isHexAdjacent (r1, r3) && isHexAdjacent (r2, r3)) {
        result = TRUE;
    }
    
    return result;
}

static void clearIntArray (int* pointer, int length) {
    int i = 0;
    
    while (i < length) {
        pointer[i] = 0;
        
        i++;
    }
}

static int getStudentMultiplier (Game g, uni player, int regionIndex) {
    int multiplier = 0;
    vertex vertA, vertB, vertC, vertD, vertE, vertF;
    region thisReg, adjA, adjB, adjC, adjD, adjE, adjF;
    
    thisReg = getHexCoords (regionIndex);
    
    
    adjA.x = thisReg.x;
    adjA.y = thisReg.y + 1;
    
    adjB.x = thisReg.x + 1;
    adjB.y = thisReg.y;
    
    adjC.x = thisReg.x + 1;
    adjC.y = thisReg.y - 1;
    
    adjD.x = thisReg.x;
    adjD.y = thisReg.y - 1;
    
    adjE.x = thisReg.x - 1;
    adjE.y = thisReg.y;
    
    adjF.x = thisReg.x - 1;
    adjF.y = thisReg.y + 1;
    
    
    vertA.region0 = thisReg;
    vertB.region0 = thisReg;
    vertC.region0 = thisReg;
    vertD.region0 = thisReg;
    vertE.region0 = thisReg;
    vertF.region0 = thisReg;
    
    vertA.region1 = adjA;
    vertB.region1 = adjB;
    vertC.region1 = adjC;
    vertD.region1 = adjD;
    vertE.region1 = adjE;
    vertF.region1 = adjF;
    
    vertA.region2 = adjB;
    vertB.region2 = adjC;
    vertC.region2 = adjD;
    vertD.region2 = adjE;
    vertE.region2 = adjF;
    vertF.region2 = adjA;
    
    
    if (g->vertices[getVertexArrayIndex (vertA)] == player + 1) {
        multiplier++;
    } else if (g->vertices[getVertexArrayIndex (vertA)] == player + 4) {
        multiplier += 2;
    }
    
    if (g->vertices[getVertexArrayIndex (vertB)] == player + 1) {
        multiplier++;
    } else if (g->vertices[getVertexArrayIndex (vertB)] == player + 4) {
        multiplier += 2;
    }
    
    if (g->vertices[getVertexArrayIndex (vertC)] == player + 1) {
        multiplier++;
    } else if (g->vertices[getVertexArrayIndex (vertC)] == player + 4) {
        multiplier += 2;
    }
    
    if (g->vertices[getVertexArrayIndex (vertD)] == player + 1) {
        multiplier++;
    } else if (g->vertices[getVertexArrayIndex (vertD)] == player + 4) {
        multiplier += 2;
    }
    
    if (g->vertices[getVertexArrayIndex (vertE)] == player + 1) {
        multiplier++;
    } else if (g->vertices[getVertexArrayIndex (vertE)] == player + 4) {
        multiplier += 2;
    }
    
    if (g->vertices[getVertexArrayIndex (vertF)] == player + 1) {
        multiplier++;
    } else if (g->vertices[getVertexArrayIndex (vertF)] == player + 4) {
        multiplier += 2;
    }
    
    
    return multiplier;
}

static region getHexCoords (int regionIndex) {
    region thisReg;
    
    if (regionIndex < 3) {
        thisReg.x = -2;
        thisReg.y = regionIndex;
    } else if (regionIndex < 7) {
        thisReg.x = -1;
        thisReg.y = regionIndex - 4;
    } else if (regionIndex < 12) {
        thisReg.x = 0;
        thisReg.y = regionIndex - 9;
    } else if (regionIndex < 16) {
        thisReg.x = 1;
        thisReg.y = regionIndex - 14;
    } else if (regionIndex < 19) {
        thisReg.x = 2;
        thisReg.y = regionIndex - 18;
    }
    
    return thisReg;
}

static vertex* getAdjacentVertices (vertex v) {
    vertex *adjVerts = malloc (3*sizeof (vertex));
    
    adjVerts[0] = v;
    adjVerts[1] = v;
    adjVerts[2] = v;
    
    if (v.region0.x < v.region1.x) {
        if (v.region0.x < v.region2.x) {  // 0 is to left of other two
            adjVerts[0].region0.x += 2;
            adjVerts[0].region0.y -= 1;
            
            if (v.region1.y < v.region2.y) {  // 2 is above 1
                adjVerts[1].region1.x -= 1;
                adjVerts[1].region1.y += 2;
                
                adjVerts[2].region2.x -= 1;
                adjVerts[2].region2.y -= 1;
            } else {  // 1 is above 2
                adjVerts[1].region1.x -= 1;
                adjVerts[1].region1.y -= 1;
                
                adjVerts[2].region2.x -= 1;
                adjVerts[2].region2.y += 2;
            }
        } else {  // 1 is to right of other two
            adjVerts[1].region1.x -= 2;
            adjVerts[1].region1.y += 1;
            
            if (v.region0.y < v.region2.y) {  // 2 is above 0
                adjVerts[0].region0.x += 1;
                adjVerts[0].region0.y += 1;
                
                adjVerts[2].region2.x += 1;
                adjVerts[2].region2.y -= 2;
            } else {  // 0 is above 2
                adjVerts[0].region0.x += 1;
                adjVerts[0].region0.y -= 2;
                
                adjVerts[2].region2.x += 1;
                adjVerts[2].region2.y += 1;
            }
        }
    } else if (v.region1.x < v.region0.x) {
        if (v.region1.x < v.region2.x) {  // 1 is left
            adjVerts[1].region1.x += 2;
            adjVerts[1].region1.y -= 1;
            
            if (v.region0.y < v.region2.y) {  // 2 is above 0
                adjVerts[0].region0.x -= 1;
                adjVerts[0].region0.y += 2;
                
                adjVerts[2].region2.x -= 1;
                adjVerts[2].region2.y -= 1;
            } else {  // 0 is above 2
                adjVerts[0].region0.x -= 1;
                adjVerts[0].region0.y -= 1;
                
                adjVerts[2].region2.x -= 1;
                adjVerts[2].region2.y += 2;
            }
        } else {  // 0 is right
            adjVerts[0].region0.x -= 2;
            adjVerts[0].region0.y += 1;
            
            if (v.region1.y < v.region2.y) {  // 2 is above 1
                adjVerts[1].region1.x += 1;
                adjVerts[1].region1.y += 1;
                
                adjVerts[2].region2.x += 1;
                adjVerts[2].region2.y -= 2;
            } else {  // 1 is above 2
                adjVerts[1].region1.x += 1;
                adjVerts[1].region1.y -= 2;
                
                adjVerts[2].region2.x += 1;
                adjVerts[2].region2.y += 1;
            }
        }
    } else {
        if (v.region2.x < v.region0.x) {  // 2 is left
            adjVerts[2].region2.x += 2;
            adjVerts[2].region2.y -= 1;
            
            if (v.region0.y < v.region1.y) {  // 1 is above 0
                adjVerts[0].region0.x -= 1;
                adjVerts[0].region0.x += 2;
                
                adjVerts[1].region1.x -= 1;
                adjVerts[1].region1.y -= 1;
            } else {  // 0 is above 1
                adjVerts[0].region0.x -= 1;
                adjVerts[0].region0.y -= 1;
                
                adjVerts[1].region1.x -= 1;
                adjVerts[1].region1.y += 2;
            }
        } else {  // 2 is right
            adjVerts[2].region2.x -= 2;
            adjVerts[2].region2.y += 1;
            
            if (v.region0.y < v.region1.y) {  // 1 is above 0
                adjVerts[0].region0.x += 1;
                adjVerts[0].region0.y += 1;
                
                adjVerts[1].region1.x += 1;
                adjVerts[1].region1.y -= 2;
            } else {  // 0 is above 1
                adjVerts[0].region0.x += 1;
                adjVerts[0].region0.y -= 2;
                
                adjVerts[1].region1.x += 1;
                adjVerts[1].region1.y += 1;
            }
        }
    }
    
    return adjVerts;
}

static arc* getAdjacentArcs (vertex v) {
    arc *adjArc = malloc (3*sizeof (arc));
    
    adjArc[2].region1 = v.region0;
    adjArc[0].region0 = v.region0;
    adjArc[0].region1 = v.region1;
    adjArc[1].region0 = v.region1;
    adjArc[1].region1 = v.region2;
    adjArc[2].region0 = v.region2;
    
    return adjArc;
}

static arc* getAdjacentArcsToArc (arc a) {
    arc *adjArcs = malloc (4*sizeof (arc));
    
    adjArcs[0] = a;
    adjArcs[1] = a;
    adjArcs[2] = a;
    adjArcs[3] = a;
    
    if (a.region0.y == a.region1.y) {  // is backward diag arc
        if (a.region0.x > a.region1.x) {  // 0 up right of 1
            adjArcs[0].region1.y++;
            adjArcs[1].region0.x--;
            adjArcs[1].region0.y++;
            adjArcs[2].region1.x++;
            adjArcs[2].region1.y--;
            adjArcs[3].region0.y--;
        } else {  // 0 down left of 1
            adjArcs[0].region0.y++;
            adjArcs[1].region1.x--;
            adjArcs[1].region1.y++;
            adjArcs[2].region0.x++;
            adjArcs[2].region0.y--;
            adjArcs[3].region1.y--;
        }
    } else if (a.region0.x == a.region1.x) {  // is horrizontal arc
        if (a.region0.y > a.region1.y) {  // 0 up of 1
            adjArcs[0].region0.x--;
            adjArcs[1].region1.x--;
            adjArcs[1].region1.y++;
            adjArcs[2].region0.x++;
            adjArcs[2].region0.y--;
            adjArcs[3].region1.x++;
        } else {  // 0 down of 1
            adjArcs[0].region1.x--;
            adjArcs[1].region0.x--;
            adjArcs[1].region0.y++;
            adjArcs[2].region1.x++;
            adjArcs[2].region1.y--;
            adjArcs[3].region0.x++;
        }
    } else {  // is foreward diag arc
        if (a.region0.x > a.region1.x) {  // 0 down right of 1
            adjArcs[0].region0.x--;
            adjArcs[1].region1.x++;
            adjArcs[2].region0.y++;
            adjArcs[3].region1.y--;
        } else {  // 0 up left of 1
            adjArcs[0].region1.x--;
            adjArcs[1].region0.x++;
            adjArcs[2].region1.y++;
            adjArcs[3].region0.y--;
        }
    }
    
    return adjArcs;
}

static vertex* getAdjacentVerticesToArc (arc a) {
    vertex *adjVerts = malloc (2*sizeof (vertex));
    
    adjVerts[0].region0 = a.region0;
    adjVerts[0].region1 = a.region1;
    adjVerts[1].region0 = a.region0;
    adjVerts[1].region1 = a.region1;
    
    if (a.region0.y == a.region1.y) {  // is backward diag arc
        if (a.region0.x > a.region1.x) {  // 0 up right of 1
            adjVerts[0].region2.x = a.region0.x;
            adjVerts[0].region2.y = a.region0.y - 1;
            adjVerts[1].region2.x = a.region0.x - 1;
            adjVerts[1].region2.y = a.region0.y + 1;
        } else {  // 0 down left of 1
            adjVerts[0].region2.x = a.region1.x;
            adjVerts[0].region2.y = a.region1.y - 1;
            adjVerts[1].region2.x = a.region1.x - 1;
            adjVerts[1].region2.y = a.region1.y + 1;
        }
    } else if (a.region0.x == a.region1.x) {  // is horrizontal arc
        if (a.region0.y > a.region1.y) {  // 0 up of 1
            adjVerts[0].region2.x = a.region0.x - 1;
            adjVerts[0].region2.y = a.region0.y;
            adjVerts[1].region2.x = a.region0.x + 1;
            adjVerts[1].region2.y = a.region0.y - 1;
        } else {  // 0 down of 1
            adjVerts[0].region2.x = a.region1.x - 1;
            adjVerts[0].region2.y = a.region1.y;
            adjVerts[1].region2.x = a.region1.x + 1;
            adjVerts[1].region2.y = a.region1.y - 1;
        }
    } else {  // is foreward diag arc
        if (a.region0.x > a.region1.x) {  // 0 down right of 1
            adjVerts[0].region2.x = a.region0.x;
            adjVerts[0].region2.y = a.region0.y + 1;
            adjVerts[1].region2.x = a.region0.x + 1;
            adjVerts[1].region2.y = a.region0.y - 1;
        } else {  // 0 up left of 1
            adjVerts[0].region2.x = a.region1.x;
            adjVerts[0].region2.y = a.region1.y + 1;
            adjVerts[1].region2.x = a.region1.x + 1;
            adjVerts[1].region2.y = a.region1.y - 1;
        }
    }
    
    return adjVerts;
}

// builds a struct type vertex with coords specified in array
static vertex makeVertex (int *coords){
    vertex v;
    
    v.region0.x = coords[0];
    v.region0.y = coords[1];
    v.region1.x = coords[2];
    v.region1.y = coords[3];
    v.region2.x = coords[4];
    v.region2.y = coords[5];
    
    return v;
}

static int getTotalGO8s (Game g) {
    int GO8s = 0;
    int i = 0;
    
    while (i < NUM_UNIS) {
        GO8s += getGO8s (g, i);
        
        i++;
    }
    
    return GO8s;
}

static double max (double a, double b) {
    double result;
    
    if (a > b) {
        result = a;
    } else {
        result = b;
    }
    
    return result;
}

#ifdef DEBUG
    void testGetHexArrayIndex (void) {
        printf ("    ***testing static get hex array index...\n");
        
        region r;
        
        r.x = -2;
        r.y = 0;
        
        //printf ("r.x: %d\n r.y: %d\n getHexArrayIndex (r): %d\n 0: %d\n", r.x, r.y, getHexArrayIndex (r), 0);
        
        printf ("        testing land regions\n");
        
        assert (getHexArrayIndex (r) == 0);
        r.x = -2;
        r.y = 1;
        assert (getHexArrayIndex (r) == 1);
        r.x = -2;
        r.y = 2;
        assert (getHexArrayIndex (r) == 2);
        r.x = -1;
        r.y = -1;
        assert (getHexArrayIndex (r) == 3);
        r.x = -1;
        r.y = 0;
        assert (getHexArrayIndex (r) == 4);
        r.x = -1;
        r.y = 1;
        assert (getHexArrayIndex (r) == 5);
        r.x = -1;
        r.y = 2;
        assert (getHexArrayIndex (r) == 6);
        r.x = 0;
        r.y = -2;
        assert (getHexArrayIndex (r) == 7);
        r.x = 0;
        r.y = -1;
        assert (getHexArrayIndex (r) == 8);
        r.x = 0;
        r.y = 0;
        assert (getHexArrayIndex (r) == 9);
        r.x = 0;
        r.y = 1;
        assert (getHexArrayIndex (r) == 10);
        r.x = 0;
        r.y = 2;
        assert (getHexArrayIndex (r) == 11);
        r.x = 1;
        r.y = -2;
        assert (getHexArrayIndex (r) == 12);
        r.x = 1;
        r.y = -1;
        assert (getHexArrayIndex (r) == 13);
        r.x = 1;
        r.y = 0;
        assert (getHexArrayIndex (r) == 14);
        r.x = 1;
        r.y = 1;
        assert (getHexArrayIndex (r) == 15);
        r.x = 2;
        r.y = -2;
        assert (getHexArrayIndex (r) == 16);
        r.x = 2;
        r.y = -1;
        assert (getHexArrayIndex (r) == 17);
        r.x = 2;
        r.y = 0;
        assert (getHexArrayIndex (r) == 18);
        
        printf ("        testing invalid cases\n");
        
        r.x = 3;
        r.y = 0;
        assert (getHexArrayIndex (r) == -1);
        r.x = 3;
        r.y = -1;
        assert (getHexArrayIndex (r) == -1);
        r.x = 3;
        r.y = -2;
        assert (getHexArrayIndex (r) == -1);
        r.x = 3;
        r.y = -3;
        assert (getHexArrayIndex (r) == -1);
        r.x = 2;
        r.y = -3;
        assert (getHexArrayIndex (r) == -1);
        r.x = 1;
        r.y = -3;
        assert (getHexArrayIndex (r) == -1);
        r.x = 0;
        r.y = -3;
        assert (getHexArrayIndex (r) == -1);
        r.x = -1;
        r.y = -2;
        assert (getHexArrayIndex (r) == -1);
        r.x = -2;
        r.y = -1;
        assert (getHexArrayIndex (r) == -1);
        r.x = -3;
        r.y = 0;
        assert (getHexArrayIndex (r) == -1);
        r.x = -3;
        r.y = 1;
        assert (getHexArrayIndex (r) == -1);
        r.x = -3;
        r.y = 2;
        assert (getHexArrayIndex (r) == -1);
        r.x = -3;
        r.y = 3;
        assert (getHexArrayIndex (r) == -1);
        r.x = -2;
        r.y = 3;
        assert (getHexArrayIndex (r) == -1);
        r.x = -1;
        r.y = 3;
        assert (getHexArrayIndex (r) == -1);
        r.x = 0;
        r.y = 3;
        assert (getHexArrayIndex (r) == -1);
        r.x = 1;
        r.y = 2;
        assert (getHexArrayIndex (r) == -1);
        r.x = 2;
        r.y = 1;
        assert (getHexArrayIndex (r) == -1);
        r.x = 3;
        r.y = 5;
        assert (getHexArrayIndex (r) == -1);
        r.x = -4;
        r.y = 2;
        assert (getHexArrayIndex (r) == -1);
        r.x = 12;
        r.y = 11;
        assert (getHexArrayIndex (r) == -1);
        r.x = -4;
        r.y = -1;
        assert (getHexArrayIndex (r) == -1);
        
        printf ("    ***passed\n");
    }

    void testIsHexAdjacent (void) {
        printf ("    ***testing static is hex adjacent...\n");
        
        printf ("        checking expected hex adjacencies\n");
        
        region r1, r2;
        
        int i = -100;
        
        while (i < 100) {
            int j = -100;
            
            while (j < 100) {
                r1.x = i;
                r1.y = j;
                
                r2.x = i;
                r2.y = j + 1;
                assert (isHexAdjacent (r1, r2));
                r2.x = i;
                r2.y = j - 1;
                assert (isHexAdjacent (r1, r2));
                r2.x = i + 1;
                r2.y = j;
                assert (isHexAdjacent (r1, r2));
                r2.x = i - 1;
                r2.y = j;
                assert (isHexAdjacent (r1, r2));
                r2.x = i - 1;
                r2.y = j + 1;
                assert (isHexAdjacent (r1, r2));
                r2.x = i + 1;
                r2.y = j - 1;
                assert (isHexAdjacent (r1, r2));
                
                //printf ("|");
                
                j++;
            }
            
            i++;
        }
        
        printf ("        testing counter examples\n");
        
        i = -20;
        
        while (i < 20) {
            int j = -20;
            
            while (j < 20) {
                int k = -20;
                
                while (k < 20) {
                    int l = -20;
                    
                    while (l < 20) {
                        r1.x = i;
                        r1.y = j;
                        r2.x = k;
                        r2.y = l;
                        
                        if (!((r1.x == r2.x && abs (r1.y - r2.y) == 1)
                         || (r1.y == r2.y && abs (r1.x - r2.x) == 1)
                         || (r1.y - r2.y == r2.x - r1.x && abs (r1.x - r2.x) == 1))) {
                            
                            assert (!(isHexAdjacent (r1, r2)));
                        }
                        
                        l++;
                    }
                    
                    k++;
                }
                
                j++;
            }
            
            i++;
        }
        
        printf ("    ***passed\n");
    }
    
    //testAreHexAdjacent ();
    
    //testGetArcArrayIndex ();
    
    //testGetVertexArrayIndex ();
    
    //testClearIntArray ();
    
    //testGetStudentMultiplier (void);
    
    //testGetHexCoords ();
    
    //testGetAdjacentVertices ();
    
    //testGetAdjacentArcs ();
    
    //testGetAdjacentArcsToArc ();
    
    //testGetAdjacentVerticesToArc ();
    
    //testMakeVertex ();
    
    //testGetTotalGO8s ();
    
    //testMax ();
#endif

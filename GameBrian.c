/* Game.c 
   This is the game.c file used 
   to intialise the game
   By We r da Best
   Get ready for a good time
*/

/*#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Game.h"

int main(int argc, char *argv[]){
}*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Game.h"

//default disciplines and dicevalues
#define DEFAULT_DISCIPLINES {2, 5, 3,\
                5, 3, 1, 4,\
                4, 1,4, 2,\
                3, 2, 0, 3,\
                5, 4, 2, 1}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

// user defined
#define NUM_DISCIPLINES  6
#define NUM_ARCS        72
#define NUM_VERTICES    54
#define TERRA_NULLIS    -1
#define EXCHANGE_RATE 3
#define RETRAIN_RATE 2
#define SEA_EXCHANGE_A1 "L,R"
#define SEA_EXCHANGE_A2 "L,R,L"
#define SEA_EXCHANGE_B1 "L,R,L,R,L,R,R,L"
#define SEA_EXCHANGE_B2 "L,R,L,R,L,R,R,L,R"
#define SEA_EXCHANGE_C1 "L,R,L,R,L,R,R,L,R,L,R,R"
#define SEA_EXCHANGE_C2 "L,R,L,R,L,R,R,L,R,L,R,R,L"
#define SEA_EXCHANGE_D1 "L,R,L,R,L,R,R,L,R,L,R,R,L,R,L,R,R,L"
#define SEA_EXCHANGE_D2 "L,R,L,R,L,R,R,L,R,L,R,R,L,R,L,R,R,L,R"
#define SEA_EXCHANGE_E1 "R"
#define SEA_EXCHANGE_E2 "R,R"
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

typedef struct _coords {
   int x;
   int y;
} coords;

typedef struct _regions {
   int a;
   int b;
   int c;
} regions;

/* students */
typedef struct _students {
   int THD;
   int BPS;
   int BQN;
   int MJ;
   int MTV;
   int MMONEY;
} students;

/* player RESOURCES DATA - Each index represents a data value for each uni */
typedef struct _player {
    students student;
    int KPI[NUM_UNIS];                          // 0 to 2 index
    int arcs[NUM_UNIS]; 
    int campuses[NUM_UNIS]; 
    int GO8[NUM_UNIS];
    int IPs[NUM_UNIS];  
    int publications[NUM_UNIS];
} player;

/* GAME DATA */

typedef struct _game {
    player player1;
    player player2;
    player player3;
    int diceValue;
    int discipline;
    int turnCount;
    int turnNumber;
    int whoseTurn;
    int mostARCs;
    int mostPubs;
    int playerPubs;
    int regions[NUM_REGIONS]; //this stores the discipline
    int regionid[NUM_REGIONS]; //this stores the dice value of the region
    //going to need 2 2d int arrays to store both the arc and campus array
    int arcarray [6][11]; //size
    int campusarray [6][11];
    regions regionarray[6][11];
} game;

void addStudent (Game g, int student, int player, int amount);
coords translatepath(path arc);

/* PATHING INFORMATION */
// pathToVertex --> Goes to the "last" vertex of the path
// pathToEdge --> Goes to the "last" edge of the path
// paths don't have to be the shortest
// paths can loop around
// length of path can't exceed PATH_LIMIT 150
// Every edge in the path must lie on the island, paths cannot include edges in the sea.

/* EDGE DATA - PATHING STRUCT 1 */
//typedef struct _edge {                  // Not sure how to represent this yet
//    int edgeID[NUM_ARCS];                             // NUM_ARCS = 72
//      int next;
//} edge;

/* VERTEX DATA - PATHING STRUCT 2 */
//typedef struct _vertex {
//    int vertexID[NUM_VERTICES];               // NUM_VERTICES = 54
//      int next;
//} vertex;

/* ACTIONS DATA 
typedef struct _action {
   int actionCode;          // see #defines in game.h
   path destination;        // if the action operates on a vertex or ARC this
                            // specifies *which* vertex or path. Unused otherwise
   int disciplineFrom;      // used for the retrain students action
   int disciplineTo;        // used for the retrain students action
} action;*/

/* DECLARE STATIC FUNCTIONS - Functions unique to this game */
static void disposeGameData (Game g) {      // EXAMPLE Free game struct data
}

static void disposePlayerData (player player) {     // EXAMPLE Free player struct data
}

static int addEdge (int fromVertex, int toVertex, int leftEdge, int rightEdge, int backEdge) {
}     

/* SETTERS - Functions which change the game */
Game newGame (int discipline[], int dice[]) {           // BRIAN
    Game g = malloc (sizeof (g))                     // Setting memory for game

    g.discipline = malloc (sizeof (int) * NUM_REGIONS); // Set memory for game board disciplines
    g.diceValue = malloc (sizeof (int) * NUM_REGIONS)); // Set memory for dice rolls

    g.currentTurn = -1;                                 // Initialise game

    int i = 0;
    while (i < NUM_REGIONS) {                           // Matching struct data with interface inputs    
        g.discipline[i] = discipline[i];
        g.diceValue[i] = dice[i];
        i++;
    }

    g->resources = malloc (sizeof (player));            // Set memory for player resources struct

    g->edgeData = malloc (sizeof (edge));               // Set memory for edge data
    g->vertexData = malloc (sizeof (vertex));           // Set memory for vertex data

    /* Insert code for starting player campuses */
    /* Insert code for starting player's surrounding discipline types??? */
  
     //initialise the game board with invalids also
    i=0;
    int z=0;
    regions r;
    r.a=INVALID;
    r.b=INVALID;
    r.c=INVALID;
    while (i<=5) { //this initialises on the y axis traverse rather then x, should be fine though
        while (z<=10){
            g->regionarray[i][z]=r;
        if ((z+i>=2) && (z+i<=13)) { //corners of the array that should be invalid add to these numbers
            g->arcarray[i][z]=VACANT_ARC;
            g->campusarray[i][z]=VACANT_VERTEX;
        } else { //doesn't catch all the invalids, rest hardcoded
            g->arcarray[i][z]=INVALID;
            g->campusarray[i][z]=INVALID;
        }
        z++;
        }
    i++;
    z=0;
    }

    //intialising hardcoded array
    r.c=0;
    g->regionarray[0][2]=r;
    g->regionarray[0][3]=r;

    r.a=0;
    r.b=1;
    r.c=INVALID;
    g->regionarray[0][4]=r;
    g->regionarray[0][5]=r;

    r.a=1;
    r.b=2;
    r.c=INVALID;
    g->regionarray[0][6]=r;
    g->regionarray[0][7]=r;

    r.a=INVALID;
    g->regionarray[0][8]=r;

    r.b=3;
    g->regionarray[1][1]=r;

    r.a=0;
    g->regionarray[1][2]=r;

    r.c=4;
    g->regionarray[1][3]=r;

    r.b=1;
    g->regionarray[1][4]=r;

    r.a=5;
    g->regionarray[1][5]=r;

   r.c=2;
   g->regionarray[1][6]=r;

   r.b=6;
   g->regionarray[1][7]=r;

   r.a=INVALID;
   g->regionarray[1][8]=r;

   r.c=INVALID;
   g->regionarray[1][9]=r;

   r.a=INVALID;
   r.b=INVALID;
   r.c=7;
   g->regionarray[2][0]=r;

   r.a=3;
   g->regionarray[2][1]=r;

   r.b=8;
   g->regionarray[2][2]=r;

   r.c=4;
   g->regionarray[2][3]=r;

   r.a=9;
   g->regionarray[2][4]=r;

   r.b=5;
   g->regionarray[2][5]=r;

   r.c=10;
   g->regionarray[2][6]=r;

   r.a=6;
   g->regionarray[2][7]=r;

   r.b=11;
   g->regionarray[2][8]=r;

   r.c=INVALID;
   g->regionarray[2][9]=r;

   r.a=INVALID;
   g->regionarray[2][10]=r;

   r.b=7;
   g->regionarray[3][0]=r;

   r.c=12;
   g->regionarray[3][1]=r;

   r.a=8;
   g->regionarray[3][2]=r;

   r.b=13;
   g->regionarray[3][3]=r;

   r.c=9;
   g->regionarray[3][4]=r;

   r.a=14;
   g->regionarray[3][5]=r;

   r.b=10;
   g->regionarray[3][6]=r;

   r.c=15;
   g->regionarray[3][7]=r;

   r.a=11;
   g->regionarray[3][8]=r;

   r.b=INVALID;
   g->regionarray[3][9]=r;

   r.c=INVALID;
   g->regionarray[3][10]=r;

   r.a=12;
   g->regionarray[4][1]=r;

   r.b=16;
   g->regionarray[4][2]=r;

   r.c=13;
   g->regionarray[4][3]=r;

   r.a=17;
   g->regionarray[4][4]=r;

   r.b=14;
   g->regionarray[4][5]=r;

   r.c=18;
   g->regionarray[4][6]=r;

   r.a=15;
   g->regionarray[4][7]=r;

   r.b=INVALID;
   g->regionarray[4][8]=r;

   r.c=INVALID;
   g->regionarray[4][9]=r;

   r.a=16;
   g->regionarray[5][2]=r;
   g->regionarray[5][3]=r;

   r.b=17;
   g->regionarray[5][4]=r;

    r.a=INVALID;
    g->regionarray[5][5]=r;

    r.a=18;
    g->regionarray[5][6]=r;

    r.b=INVALID;
    g->regionarray[5][7]=r;
    g->regionarray[5][8]=r;

    //specify missed invalids
    g->arcarray[4][0]=INVALID;
    g->arcarray[5][0]=INVALID;
    g->arcarray[5][1]=INVALID;
    g->arcarray[0][9]=INVALID;
    g->arcarray[0][10]=INVALID;
    g->arcarray[1][10]=INVALID;

    g->campusarray[4][0]=INVALID;
    g->campusarray[5][0]=INVALID;
    g->campusarray[5][1]=INVALID;
    g->campusarray[0][9]=INVALID;
    g->campusarray[0][10]=INVALID;
    g->campusarray[1][10]=INVALID;

    //player one
    g->player1.KPI=20;
    g->player1.arcs=0;
    g->player1.GO8s=0;
    g->player1.Campuses=2;
    g->player1.IPs=0;
    g->player1.Pubs=0;
    g->player1.students.THD=0;
    g->player1.students.BPS=3;
    g->player1.students.BQN=3;
    g->player1.students.MJ=0;
    g->player1.students.MTV=0;
    g->player1.students.MMONEY=0;

    //player two
    g->player2.KPI=20;
    g->player2.arcs=0;
    g->player2.GO8s=0;
    g->player2.Campuses=2;
    g->player2.IPs=0;
    g->player2.Pubs=0;
    g->player2.students.THD=0;
    g->player2.students.BPS=3;
    g->player2.students.BQN=3;
    g->player2.students.MJ=0;
    g->player2.students.MTV=0;
    g->player2.students.MMONEY=0;

    //player three
    g->player3.KPI=20;
    g->player3.arcs=0;
    g->player3.GO8s=0;
    g->player3.Campuses=2;
    g->player3.IPs=0;
    g->player3.Pubs=0;
    g->player3.students.THD=0;
    g->player3.students.BPS=3;
    g->player3.students.BQN=3;
    g->player3.students.MJ=0;
    g->player3.students.MTV=0; 
    g->player3.students.MMONEY=0;
 
    //assign exisintg points, arcs do not exist in these locs but arcs can be built from them, therefore they must be stated as if they have arcs
    g->arcarray[2][0]=UNI_A;
    g->arcarray[3][10]=UNI_A;
    g->arcarray[0][3]=UNI_B;
    g->arcarray[5][7]=UNI_B;
    g->arcarray[0][8]=UNI_C;
    g->arcarray[5][2]=UNI_C;

    g->campusarray[2][0]=UNI_A;
    g->campusarray[3][10]=UNI_A;
    g->campusarray[0][3]=UNI_B;
    g->campusarray[5][7]=UNI_B;
    g->campusarray[0][8]=UNI_C;
    g->campusarray[5][2]=UNI_C;

    return g;
}

void disposeGame (Game g) {     // BRIAN
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

coords translatepath(path arc){
    //needs a response for if the path is empty
    int prevycoords=0;
    coords coord;
    int prevxcoords=2;
    int xcoords=2;
    int ycoords=0;
    int leftx=0;
    int lefty=0;
    int rightx=0;
    int righty=0;
    int tempx=0;
    int tempy=0;
    int approach=DOWN;
    int index=0;
    while(arc[index]!=0){
        //determine approach
        //There is never a possibility of changing both x and y, therefore it isn't accounted for (yeah it should error trap but its our own function)
        if (prevycoords<ycoords||((ycoords==0)&&(index==0))){
            approach=DOWN;
        } else if (prevycoords>ycoords){
            approach=UP;
        } else if (prevxcoords<xcoords){
            approach=RIGHT;
        } else if (prevxcoords>xcoords){
            approach=LEFT;
        }
      //Compressed code, uncompressed found in other file
        if (((approach == DOWN) && ((xcoords == 0) || (xcoords%2==0)) && (ycoords%2 == 0))
            || ((approach == DOWN) && (xcoords%2 == 1) && (ycoords%2 != 0))) { //EVENS EVENS and ODDS ODDS
            leftx=xcoords+1;
            lefty=ycoords;
            rightx=xcoords;
            righty=ycoords+1;
        } else if (((approach == UP) && ((xcoords == 0) || (xcoords%2 == 0)) && (ycoords%2 == 0))
                   || ((approach == UP) && (xcoords%2 == 1) && (ycoords%2 != 0))) {
            leftx=xcoords;
            lefty=ycoords-1;
            rightx=xcoords+1;
            righty=ycoords;
        } else if (((approach == RIGHT) && ((xcoords == 0) || (xcoords%2 == 0)) && (ycoords%2 == 0))
                   || ((approach == RIGHT) && (xcoords%2 == 1) && (ycoords%2 != 0))) {
            leftx=xcoords;
            lefty=ycoords-1;
            rightx=xcoords;
            righty=ycoords+1;
        } else if ((approach == RIGHT) && (xcoords%2 == 1) && (ycoords%2 != 0)) {
            //avoiding combining the invalid statements as they are so damn long
            leftx=xcoords; //if this happens it should be picked up by the islegalfunction
            lefty=ycoords-1;
            rightx=xcoords;
            righty=ycoords+1;
        } else if (((approach == DOWN) && ((xcoords == 0) || (xcoords%2 == 0)) && (ycoords%2 != 0)) || ((approach == DOWN) && (xcoords%2 == 1) && (ycoords%2 == 0))) { //EVENS ODDS
            leftx=xcoords;
            lefty=ycoords+1;
            rightx=xcoords-1;
            righty=ycoords;
        } else if (((approach == UP) && ((xcoords == 0) || (xcoords%2 == 0)) && (ycoords%2 != 0)) || ((approach == UP) && (xcoords%2 == 1) && (ycoords%2 == 0))) {
            eftx=xcoords-1;
            lefty=ycoords;
            rightx=xcoords;
            righty=ycoords-1;
        } else if (((approach == RIGHT) && ((xcoords == 0) || (xcoords%2 == 0)) && (ycoords%2 != 0)) || ((approach == RIGHT) && (xcoords%2 == 1) && (ycoords%2 == 0))) {
         //not possible DOUBLE CHECK
            leftx=xcoords;
            lefty=ycoords-1;
            rightx=xcoords;
            righty=ycoords+1;
        } else if (((approach == LEFT) && ((xcoords == 0) || (xcoords%2 == 0)) && (ycoords%2 != 0)) || ((approach == LEFT) && (xcoords%2 == 1) && (ycoords%2 == 0))) {
            leftx=xcoords;
            lefty=ycoords-1;
            rightx=xcoords;
            righty=ycoords+1;
        } else if (((approach == LEFT) && ((xcoords == 0) || (xcoords%2 == 0)) && (ycoords%2 == 0)) || ((approach == LEFT) && (xcoords%2 == 1) && (ycoords%2 != 0))) {
            leftx=xcoords;
            lefty=ycoords+1;
            rightx=xcoords;
            righty=ycoords-1;
        }

      //assuming new coords have been obtained
      if (arc[index]=='L') {
         prevxcoords=xcoords;
         prevycoords=ycoords;
         xcoords=leftx;
         ycoords=lefty;
      } else if (arc[index]=='R') {
         prevxcoords=xcoords;
         prevycoords=ycoords;
         xcoords=rightx;
         ycoords=righty;
      } else if (arc[index]=='B') {
         tempx=xcoords;
         tempy=ycoords;
         xcoords=prevxcoords;
         ycoords=prevycoords;
         prevxcoords=tempx;
         prevycoords=tempy;
      }
      index++;
   }

   coord.x=xcoords;
   coord.y=ycoords;

   return coord;
} 
          
void makeAction (Game g, action a);                                 // MEHRI

void throwDice (Game g, int diceScore);                             // MEHRI

/* GAME BOARD GETTERS - Functions which get game board data */
int getDiscipline (Game g, int regionID) {                          // DAVID
    return g->discipline[region ID];
}

int diceValue (Game g, int regionID) {                // SHARON
    int diceValue[19] = DEFAULT_DICE;
    return g->diceValue;
}

int getMostARCs (Game g) {  // VEN
    int P1A = g->player1.arcs;
    int P2A = g->player2.arcs;
    int P3A = g->player3.arcs;
    int curArcs = g->mostARCS;
    int playmostarc = NO_ONE;
     
    if ((P1A == 0) && (P2A == 0) && (P3A == 0)){
        playmostarc = NO_ONE;
    }
    if (P1A > P2A){
        if(P2A > P3A){
            playmostarc = UNI_A;
        } else if (P1A == P3A) {
            playmostarc = curArcs;
        } else {
            plamostarc = UNI_C;
    } else if (P1A == P2A) {
        playmostarc = curArcs;
    } else if (P2A > P3A){
        playmostarc = UNI_B;
    } else if ( P2A == P3A) {
        playmostarc = curArcs;
    } else {
        playmostarc = UNI_C;
    }
    return playmostarc;  
}

int getPublications (Game g, int player) {               //SHARON
    int playerPubs = 0;
    if (player == UNI_A) {
        playerPubs = g->player1.Pubs;
    } else if (player == UNI_B) {
        playerPubs = g->player2.Pubs;
    } else if (player == UNI_C) {
        playerPubs = g->player3.Pubs;
    }
    return playerPubs;
}


int getMostPublications(Game g) {                        //SHARON
    int pub1 = g->player1.Pubs;
    int pub2 = g->player2.Pubs;
    int pub3 = g->player3.Pubs;

    int currentMostPubs = g->mostPubs;
    int mostPubs = NO_ONE;

    if ((pub1 == 0)&&(pub2 == 0)&&(pub3 == 0)) {
        mostPubs = NO_ONE;
    }

    if ((pub1) > (pub2)) {
    //if player1Pubs > player2Pubs
        if ((pub1) > (pub3)) {     //and player1Pubs > player3Pubs as well
            mostPubs = UNI_A;
        } else if ((pub1) == (pub3)) {
            mostPubs = currentMostPubs;
        } else {
        mostPubs = UNI_C;
    } else if (pub1 == pub2) {          //or if player2Pubs >= player1Pubs
        mostPubs = currentMostPubs;
    } else if ((pub2) > (pub3)) {
        mostPubs = UNI_B;
    } else if ((pub2) == (pub3)) {
        mostPubs = currentMostPubs;
    } else {
        mostPubs = UNI_C;
    }
    return mostPubs;
}

int getTurnNumber (Game g) {
    int currentTurn = TERRA_NULLIS; //at the start of the game
    currentTurn++;
    return currentTurn; //g->currentTurn;
}

int getWhoseTurn (Game g) {                                          // DONE (SHARON)// at the start of the game
   return g.whoseTurn;
}

int getCampus(Game g, path pathToVertex) {                           // DONE (BRIAN)
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

int getARC(Game g, path pathToEdge) {
    int playerARC = 0;
    if (player == UNI_A) {
        playerARC = g->player1.arcs;
    } else if {player == UNI_B) {
        playerARC = g->player2.arcs;
    } else {player == UNI_C) {
        playerARC = g->player3.arcs;
    }
    return playerARC;
}                             

int isLegalAction (Game g, action a){
   int legal=FALSE;
   int x=0; //NEED TO CONSIDER HOW TO ACTUALLY BUILD AN ARC
   int y=0;
   int w=0;
   int player = getWhoseTurn(g);
   coords coord;
   if (a.actionCode==OBTAIN_ARC){ //currently this assumes arcs are like vertex's and their points ARCS REPED BY THE VERTEXS THEY CONNECT
      if ((getStudents(g,player,STUDENT_BPS)>=1)&&(getStudents(g,player,STUDENT_BQN)>=1)&&(a.destination[0]!='B') && sizeof(a.destination)<=PATH_LIMIT){ //gate to ensure sufficient students & valid path
         coord=translatepath(a.destination); //translate action a and return coords in terms of x and y
         x=coord.x;
         y=coord.y;
         if (g->arcarray[x][y]==VACANT_VERTEX){ //SCANS SURROUNDINGS FOR OTHER MATCHING ARCS RETURNS TRUE IF ONE IS FOUND
            if (y!=0){
               w=y-1;
               if (g->arcarray[x][w]==getWhoseTurn(g)){ //REMOVE NEED FOR VALID POINT FUNCTION BY INITIALISING ARRAY TO HAVE AN IMPOSSIBLE VALUE (10) IN THE INVALID POINTS
                  legal=TRUE;
               }
            }
            if (y!=10){
               w=y+1;
               if (g->arcarray[x][w]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            }
            if (((x==3)||(x==1)||(x==5))&&(y%2==0)){ //checks for odd column, even row do some logic testing on these
               w=x-1;
               if (g->arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            } else if (((x==3)||(x==1)||(x==5))&&(y%2!=0)) {
               w=x+1;
               if (g->arcarray[w][y]==getWhoseTurn(g)){
                  legal=TRUE;
               }
            } else if (((x==0)||(x==2)||(x==4))&&(y%2==0)) {
               w=x+1;
               if (g->arcarray[w][y]==getWhoseTurn(g)) {
                  legal=TRUE;
               }
            } else if (((x==0)||(x==2)||(x==4))&&(y%2!=0)) {
               w=x-1;
               if (g->arcarray[w][y]==getWhoseTurn(g)) {
                  legal=TRUE;
               }
            }
         }
         //also needs to check if a vacant arc first
      }
    } else if (a.actionCode == RETRAIN_STUDENTS) {
        if ((a.disciplineFrom >= getExchangeRate(g,player,a.disciplineFrom,a.disciplineTo)) && (a.disciplineFrom!=STUDENT_THD)) { //checks not THD and above rate
            legal=TRUE;
    }
    } else if (a.actionCode==PASS){
      legal=TRUE;
   } else if (a.actionCode==START_SPINOFF){
      if ((getStudents (g,player,STUDENT_MJ) >= 1) && (getStudents (g,player,STUDENT_MTV) >= 1) && (getStudents (g,player,STUDENT_MMONEY) >= 1)) {
         legal=TRUE;
      }
   } else if (a.actionCode==BUILD_CAMPUS){
      if ((getStudents(g,player,STUDENT_BPS)>=1)&&(getStudents(g,player,STUDENT_BQN)>=1)&&(getStudents(g,player,STUDENT_MJ)>=1)&&(getStudents(g,player,STUDENT_MTV)>=1)&& (getARC(g,a.destination)==player)){ //gate, also uses getARC
         // need to also check no campuses within surounding area using similar scanning technique to arcs
         coord=translatepath(a.destination); //translate given path into 2d array point
         x=coord.x;
         y=coord.y;
         legal=TRUE; //sets to true for proving wrong
         if (y!=0){ //Scans for nearby campus's
            w=y-1;
            if (g->campusarray[x][w]==getWhoseTurn(g)){ //CAN PROBS COMPILE THIS INTO ITS OWN FUNCTION CALLED SCAN WHICH TAKES location, type to scan for and returns true if one is found, false if none.
               legal=FALSE;
            }
         }
         if (y!=10){
            w=y+1;
            if (g->campusarray[x][w]==getWhoseTurn(g)){
               legal=FALSE;
            }
         }
         if (((x==3)||(x==1)||(x==5))&&(y%2==0)){
            w=x-1;
            if (g->campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if (((x==3)||(x==1)||(x==5))&&(y%2!=0)) {
            w=x+1;
            if (g->campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if ((x%2==0)&&(y%2==0)){
            w=x+1;
            if (g->campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         } else if ((x%2==0)&&(y%2!=0)){
            w=x-1;
            if (g->campusarray[w][y]==getWhoseTurn(g)){
               legal=FALSE;
            }
         }
      }
   } else if (a.actionCode==BUILD_GO8){
      if ((getStudents(g,player,STUDENT_MJ)>=2)&&(getStudents(g,player,STUDENT_MMONEY)>=3)&&(player==getCampus(g,a.destination))){
         legal=TRUE;
      } //uses getcampus function
   }
   return legal;
}

/* PLAYER INFO GETTERS - Functions which get specific player data */

int getKPIpoints (Game g, int player){
    int Kpipts = 0;
    Kpipts = Kpipits + 10*getCampuses(g, player);
    Kpipits = Kpipts + 20*getGO8s(g, player);
    Kpipts = Kpipts + 2*getARCs;
    if (getMostPublications(g) == player) {
        Kpipts = Kpipts + 10;
    }
    if (getMostArcs(g) == player){
        Kpipts = Kpipts + 10;
    }

    int assignedplayer = getWhoseTurn(g);
    if (assignedplayer == UNI_A){
        *g->player1.KPI = Kpipts;
    } else if(assignedplayer == UNI_B){
        *g->player2.KPI = Kpipts;
    } else (assignedplayer == UNI_C){
        *g->player3.KPI = Kpipts;
    }
    return Kpipts;
}

int getGO8s (Game g, int player) {                                      // BRIAN
    int numGO8 = 0;
    int i = 0;
        
    while (i < NUM_VERTICES) {
        g->player.GO8 = numGO8;
    }
    i++;
    return numGO8;
}


int getCampuses (Game g, int player);                                   // BRIAN
    int i = 0;
    int numCampus = 0;

    while (i < NUM_VERTICES) {
        ;
    }
    counter++;
    return returnValue;
}

int getIPs (Game g, int player) {                                       // DONE
    return *g->player.IPs;
}


int getStudents (Game g, int player, int discipline){   // function which returns the amount of students in a discipline for a player DAVID
  int students=0; 
  if (player==UNI_A){
      if (discipline==STUDENT_THD){
        g->player1.student.THD=students;
      } if (discipline==STUDENT_BPS){
         students=player1.student.BPS;
      } if (discipline==STUDENT_BQN){
         students=player1.student.BQN;
      } if (discipline==STUDENT_MJ){
         students=player1.student.MJ;
      } if (discipline==STUDENT_MTV){
         students=player1.student.MTV;
      } if (discipline==STUDENT_MMONEY){
         students=player1.student.MMONEY;
      }
   } else if (player==UNI_B){
      if (discipline==STUDENT_THD){
         students = player2.student.THD;
      } if (discipline==STUDENT_BPS){
         students = player2.student.BPS;
      } if (discipline==STUDENT_BQN){
         students = player2.student.BQN;
      } if (discipline==STUDENT_MJ){
         students = player2.student.MJ;
      } if (discipline==STUDENT_MTV){
         students = player2.student.MTV;
      } if (discipline==STUDENT_MMONEY){
         students = player2.student.MMONEY;
      }
   } else if (player==UNI_C){
      if (discipline==STUDENT_THD){
         students = player3.student.THD;
      } if (discipline==STUDENT_BPS){
         students = player3.student.BPS;
      } if (discipline==STUDENT_BQN){
         students = player3.student.BQN;
      } if (discipline==STUDENT_MJ){
         students = player3.student.MJ;
      } if (discipline==STUDENT_MTV){
         students = player3.student.MTV;
      } if (discipline==STUDENT_MMONEY){
         students = player3.student.MMONEY;
      }
   }

   return students;
}
  
int getExchangeRate (Game g, int player,int disciplineFrom, int disciplineTo){
    int exchangeRate=EXCHANGE_RATE;
  
    if (getCampus(g,SEA_EXCHANGE_A1) == player) {
        exchangeRate=RETRAIN_RATE;
    }
    if (getCampus(g,SEA_EXCHANGE_A2) == player) {
        exchangeRate=RETRAIN_RATE;
    }   
    if (getCampus(g,SEA_EXCHANGE_B1) == player) {
        exchangeRate=RETRAIN_RATE;
    }
    if (getCampus(g,SEA_EXCHANGE_B2) == player) {
        exchangeRate=RETRAIN_RATE;
    }
    if (getCampus(g,SEA_EXCHANGE_C1)==player) {
        exchangeRate=RETRAIN_RATE;
    } 
    if (getCampus(g,SEA_EXCHANGE_C2)==player){
        exchangeRate=RETRAIN_RATE;
    }
    if (getCampus(g,SEA_EXCHANGE_D1)==player){
    exchangeRate=RETRAIN_RATE;
    }
    if (getCampus(g,SEA_EXCHANGE_D2)==player){
    exchangeRate=RETRAIN_RATE;
    }
    if (getCampus(g,SEA_EXCHANGE_E1)==player){
    exchangeRate=RETRAIN_RATE;
    }
  if(getCampus(g,SEA_EXCHANGE_E2)==player){
     exchangeRate=RETRAIN_RATE;
  }
 
    return exchangeRate ;
}



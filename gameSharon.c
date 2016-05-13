typedef struct game {
   
   int diceValue;
   int discipline;
   int turnNumber;
   int whoseTurn;
   int mostARCs;
   int mostPubs;
   
} game;
 
int diceValue (Game g, int regionID) {
	return g-> diceValue[regionID];
}

int discipline (Game g, int region ID) {
	return g-> discipline[region ID];
}

int getTurnNumber(Game g) {
   return g->currentTurn;
}
 
int getWhoseTurn (Game g)
   return g->whoseTurn;

int getMostARCs(Game g) {
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
 
 
int getMostPublications(Game g) {
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
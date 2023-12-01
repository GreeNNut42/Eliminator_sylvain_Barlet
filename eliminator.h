#ifndef ELIMINATOR_H
#define ELIMINATOR_H
#include <string>

typedef char grille[10][10];


void creationGrille(grille &grilleCrea, int &nbTours, int* nbBoulesV, int* nbBoulesR, int* nbBoulesB, int* nbBoulesJ, int* nbBoulesN);
void afficherGrille(grille grilleAffiche);
bool testdirection(grille grilleJeu, int i, int j, char chxDirection);
void deplacement (grille grilleJeu, grille grilleBase, int* nbTours, int nbToursTot, int* nbBoulesV, int* nbBoulesR, int* nbBoulesB, int* nbBoulesJ, int* nbBoulesN);
void verif_elimination(grille grilleJeu, int* nbBoulesV, int* nbBoulesR, int* nbBoulesB, int* nbBoulesJ, int* nbBoulesN);
void elimination(grille grilleJeu);
int victoire (grille grilleJeu);
int jouer();
void sauvegarde(grille grilleJeu, std::string nomGrille, int nbTours);
void chargementfichier(grille grilleJeu, int &nbTours, int* position);
int jouerCharge();
int jouerChargeclssmnt();
void chargementfichierclssmnt(grille grilleJeu, int &nbTours, int* position);
void setscore(double tempsTotal, int nbGrilles);
void afficherscores();
#endif

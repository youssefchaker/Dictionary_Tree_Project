#ifndef DEF_DICO
#define DEF_DICO
#include "arbre.h"

int piocherMot(char *motPioche);
int nombreAleatoire(int nombreMax);

void dicoAfficher(TArbre a);
int dicoNbMotsDifferents(TArbre a);
int dicoNbMotsTotal(TArbre a);
void dicoInsererMot(char mot[], TArbre *a);
int dicoNbOcc(char mot[], TArbre a); 
int est_dans_dico(char *mot, Tarbre dico);
#endif
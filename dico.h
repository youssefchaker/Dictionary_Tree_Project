#ifndef DEF_DICO
#define DEF_DICO
#include "arbre.h"

int piocherMot(char *motPioche);
int nombreAleatoire(int nombreMax);
void dicoAfficher(TArbre* a,char buffer[], int *cur);
int dicoNbMotsDifferents(TArbre* a);
int dicoNbMotsTotal(TArbre* a);
void dicoInsererMot(char mot[], TArbre** a);
int dicoNbOcc(char mot[], TArbre* a); 
TArbre* dicoInsererNouvMot(char mot[], TArbre* a);
TArbre* dicoBranche(char *mot);
void dicoNbOccAdd(char *mot, TArbre** a);
void aff(TArbre* a);
#endif
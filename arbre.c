#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "arbre.h"

//create empty tree
TArbre* arbreConsVide(){
    TArbre* empty;
    empty = (TArbre*) malloc(sizeof(TArbre));
    return empty;
}
//test if the tree is empty or not
int arbreEstVide(TArbre* a){
    if(a == arbreConsVide())
        return 1;
    return 0;
}
//create a tree 
TArbre* arbreCons(char c, int n, TArbre* fg, TArbre* fd){
    TArbre* arbre;
    arbre = (TArbre*)malloc(sizeof(TArbre));
    arbre->data=c;
    arbre->nbOcc=n;
    arbre->droite=fg;
    arbre->gauche=fd;
    return arbre;
}

//retrun node data
char arbreRacineLettre(TArbre* a){
    return a->data;
}

//return nb occ
int arbreRacineNbOcc(TArbre* a){
    return a->nbOcc;
}

//return left tree node
TArbre* arbreFilsGauche(TArbre* a){
    return a->gauche;
}

//return right tree node
TArbre* arbreFilsDroit(TArbre* a){
    return a->droite;
}

//delete tree
void arbreSuppr(TArbre* a){
    if(!arbreEstVide(a)){
        arbreSuppr(a->gauche);
        arbreSuppr(a->droite);
        free(a);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "arbre.h"

//create empty tree
TArbre arbreConsVide(){
    TArbre empty;
    empty=malloc(sizeof(TArbre));
    return empty;
}
//test if the tree is empty or not
int arbreEstVide(TArbre a){
    if(a==arbreConsVide())
        return 1;
    return 0;
}
//create a tree 
TArbre arbreCons(char c, int n, TArbre* fg, TArbre* fd){
    TArbre arbre;
    arbre=malloc(sizeof(TArbre));
    arbre.data=c;
    arbre.nbOcc=n;
    arbre.right=fg;
    arbre.left=fd;
    return arbre;
}

//retrun node data
char arbreRacineLettre(TArbre a){
    return a.data;
}

//return nb occ
int arbreRacineNbOcc(TArbre a){
    return a.nbOcc;
}

//return left tree node
TArbre* arbreFilsGauche(TArbre* a){
    return a->left;
}

//return right tree node
TArbre* arbreFilsDroit(TArbre* a){
    return a->right;
}

//delete tree
void arbreSuppr(TArbre* a){
    if(!arbreEstVide(a)){
        arbreSuppr(a->left);
        arbreSuppr(a->right);
        free(a);
    }
}

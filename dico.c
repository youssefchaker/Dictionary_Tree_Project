#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dico.h"
#include "arbre.h"

//print the entire dictionary
void dicoAfficher(TArbre* a){
    dicoAfficher(a->left);
    printf("%s ", a->data);
    dicoAfficher(a->right);
}
//get the number of different words 
int dicoNbMotsDifferents(TArbre a){}

//get the total number of words
int dicoNbMotsTotal(TArbre a){}

//insert a word in the dictionary
/*void dicoInsererMot(char mot[], TArbre *dico){
    if(dico == NULL) return arbreConsVide();
  if(mot[0] == '\0') return (dico->data == '\0')?dico:arbreCons('\0',1,NULL,dico);
  if(mot[0] < dico->data) return arbreCons(mot[0]0,, new_dico(mot+1), dico);
  if(mot[0] == dico->data){
    dico->gauche = ajoute_dans_dico(mot+1, dico->gauche);
    return dico;
  }
  dico->droite = ajoute_dans_dico(mot, dico->droite);
  return dico;
}*/

//get the number of occurences in the dictionary
int dicoNbOcc(char mot[], TArbre dico){
    if(!est_dans_dico(mot,dico))
        printf("the word is not in the dictionary");
    
}

//check if the word is in the dictionary
int est_dans_dico(char *mot, Tarbre dico){
  if((dico == NULL)||(dico->data > mot[0])) return 0;
  if(mot[0] == dico->data){
    if(mot[0] == '\0') return 1;
    return est_dans_dico(mot+1, dico->gauche);
  }
  return est_dans_dico(mot, dico->droite);
}

/*Tarbre new_dico(char *mot){
  if(mot[0] == '\0') return noeud('\0',NULL,NULL);
  return noeud(mot[0],new_dico(mot+1),NULL);
}*/





 
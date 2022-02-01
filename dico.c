#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dico.h"
#include "arbre.h"

/* *************************************************** Insertion *************************************************** */

//get a random number
int nombreAleatoire(int nombreMax)
{
  srand(time(NULL));
  return (rand() % nombreMax);
}

//get a random word from the dictionary 
int piocherMot(char *motPioche)
{
  FILE* dico = NULL; 
  int nombreMots = 0; //nombre de mots dans le fichier
  int numMotChoisi = 0, // mot piocher au hasard
  int i = 0; //compteur
  int caractereLu = 0;

  dico = fopen("dico.txt", "r"); // On ouvre le dictionnaire en lecture seule

  // On vérifie si on a réussi à ouvrir le dictionnaire
  if (dico == NULL) 
  {
      // Si on n'a PAS réussi à ouvrir le fichier
      printf("\n Impossible de charger le dictionnaire de mots");
      return 0; 
  }

  // On compte le nombre de mots dans le fichier
  do
  {
      caractereLu = fgetc(dico);
      if (caractereLu == '\n')
          nombreMots++; 
  } while(caractereLu != EOF);
  // On pioche un mot au hasard
  numMotChoisi = nombreAleatoire(nombreMots);

  // On recommence à lire le fichier depuis le début
  rewind(dico);
  while (numMotChoisi > 0)
  {
      caractereLu = fgetc(dico);
      if (caractereLu == '\n')
          numMotChoisi--;
  }
  // Arrivé au bon mot
  fgets(motPioche, 100, dico);

  // On vire le \n à la fin
  motPioche[strlen(motPioche) - 1] = '\0';
  fclose(dico);

  // Tout s'est bien passé 
  return 1; 
}


//YOUSSEF

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
/*Tarbre new_dico(char *mot){
  if(mot[0] == '\0') return noeud('\0',NULL,NULL);
  return noeud(mot[0],new_dico(mot+1),NULL);
}*/

/* ***************************************************************************************************************** */


/* *************************************************** Affichage *************************************************** */

//print the entire dictionary
void dicoAfficher(TArbre* a){
    static char buffer[TAILLE_MAX_MOT]; // Buffer servant à stocker les mots à écrire
    static int cur = 0; // Case courante à remplir
    if (a != NULL){
        buffer[cur++]=a->data;
        if (a->data == '\0'){
            printf("%s ", buffer);
            printf("nb d'occ: %d \n", a->nbOcc);
        }
        else 
            dicoAfficher(a->gauche);
        cur--;
        if (a->droite != NULL)
            dicoAfficher(a->droite);
    }
    else 
        printf("Dictionnaire est vide \n");
}
/* ***************************************************************************************************************** */



/* *************************************************** Statistiques *************************************************** */
//get the number of different words 
int dicoNbMotsDifferents(TArbre a){
  static int NbMotsDifferents=0;
  if (a != NULL){
        if (a->data == '\0'){
            NbMotsDifferents++;
        }
        else 
            dicoNbMotsDifferents(a->gauche);
        if (a->droite != NULL)
            dicoNbMotsDifferents(a->droite);
    }
    return count;
}

//get the total number of words
int dicoNbMotsTotal(TArbre a){
  static int NbMotsTotal=0;
  if (a != NULL){
        if (a->data == '\0'){
            NbMotsTotal+=a->nbOcc;
        }
        else 
            dicoNbMotsTotal(a->gauche);
        if (a->droite != NULL)
            dicoNbMotsTotal(a->droite);
    }
    return NbMotsTotal;
}
/* ***************************************************************************************************************** */


/* *************************************************** Exist + Occ *************************************************** */

//get the number of occurences in the dictionary
int dicoNbOcc(char *mot, Tarbre a){
  if((a == NULL)||(*mot < a->data)) return 0;
  if(*mot == a->data){
    if(*mot == '\0') return a->nbOcc;
    return dicoNbOcc(mot+1, a->gauche);
  }
  return dicoNbOcc(mot, a->droite);
}

//Increment the number of occurences in the dictionary
void dicoNbOccAdd(char *mot, Tarbre a){
  if(*mot == a->data){
    if(*mot == '\0') return a->nbOcc+=1;
    return dicoNbOcc(mot+1, a->gauche);
  }
  return dicoNbOcc(mot, a->droite);
}
/* ***************************************************************************************************************** */





 
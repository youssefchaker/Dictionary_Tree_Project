#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dico.h"
#include "arbre.h"

/* *************************************************** Insertion *************************************************** */

//choisir un nimbre aleatoire depuis le dictionnaire
int nombreAleatoire(int nombreMax)
{
  srand(time(NULL));
  return (rand() % nombreMax);
}

//choisir un mot aleatoire depuis le dictionnaire
int piocherMot(char *motPioche)
{
  FILE* dico = NULL; 
  int nombreMots = 0; //nombre de mots dans le fichier
  int numMotChoisi = 0; // mot piocher au hasard
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


void aff(TArbre* a){
  if (a != NULL){
    printf("%c aaaaaaaaa %d \n ",a->data, a->nbOcc);
    aff(a->gauche);
    aff(a->droite);
  }
}
TArbre* dicoBranche(char *mot){
  if(mot[0] == '\0') return arbreCons('~',1,NULL,NULL);
  return arbreCons(mot[0],0,dicoBranche(mot+1),NULL);
}

// Insertion dans le dictionnaire
TArbre* dicoInsererNouvMot(char mot[], TArbre* a){
    // verifier si l'arbre est nulle

    if(a== NULL){
        return dicoBranche(mot);
    } 
    /* verifier si le caractere est un caractere de fin de chaine
     si c'est le cas verifier le mot dans la racine*/
    if(mot[0] == '\0') return (a->data == '\0')?a:arbreCons('\0',1,NULL,a);

    /* si c'est un nouveau mot construire un nouveau 
      sous arbre contenant le nouveau mot et l'affecter
      au fg*/
    if(mot[0] < a->data) return arbreCons(mot[0],0, dicoBranche(mot+1), a);
    /* si le mot commence avec la même lettre */
    if(mot[0] == a->data){
      /* l'inserer dans le sous arbre gauche*/
      a->gauche = dicoInsererNouvMot(mot+1, a->gauche);
      return a;
    }
    a->droite = dicoInsererNouvMot(mot, a->droite);
    return a;
}
//  Incrementer le nombre d'occurences dans dictionnaire
void dicoNbOccAdd(char *mot, TArbre* a){
  // verifier si le mot se trouve à la racine
  if(*mot == a->data){
    if(*mot == '\0') a->nbOcc+=1;
    // incrimenter son occurance
    return dicoNbOccAdd(mot+1, a->gauche);
  }
  // verifier le sous arbre droite
  return dicoNbOccAdd(mot, a->droite);
}


//insert a word in the dictionary
void dicoInsererMot(char mot[], TArbre* a){
  if(dicoNbOcc(mot, a) == 0){
    // Nouveau mot
    a = dicoInsererNouvMot(mot,a);
    aff(a);

  }else
    // mot exisistant alors incrimenter on occurence
    dicoNbOccAdd(mot,a);

}

/* ***************************************************************************************************************** */


/* *************************************************** Affichage *************************************************** */
 
//Afficher tout le dictionnaire
void dicoAfficher(TArbre* a,char *buffer, int *cur){
    printf("cur %d \n",*cur);
    printf("Buffer init %s \n",buffer);
    if (a != NULL){
        buffer[*cur] = a->data;
        *cur+=1;
        printf("Buffer: %s \n",buffer);
    
        if (a->data == '~'){
            // afficher le mot et son occurence
            printf("\t %s -> [ %d ]\n",buffer,a->nbOcc);
        }
        else {

            dicoAfficher(a->gauche,buffer,cur);
        }
        
        if (a->droite != NULL){
            //*cur--;
            dicoAfficher(a->droite,buffer,cur);
        }
    }
    /*else 
        printf("Dictionnaire est vide \n");*/
}
/* ***************************************************************************************************************** */



/* *************************************************** Statistiques *************************************************** */
// Trouver le nombre de mots differents 
int dicoNbMotsDifferents(TArbre* a){
  static int NbMotsDifferents=0;
  if (a != NULL){
        /* incrimenter à chaque fois qu'on
          atteint la fin de chaine */
        if (a->data == '\0'){
            NbMotsDifferents++;
        }
        else 
            // verifier le sous arbre gauche
            dicoNbMotsDifferents(a->gauche);
        if (a->droite != NULL)
            // verifier le sous arbre droite
            dicoNbMotsDifferents(a->droite);
    }
    return NbMotsDifferents;
}

// Trouver le nombre total de mots
int dicoNbMotsTotal(TArbre* a){
  static int NbMotsTotal=0;
  if (a != NULL){
        if (a->data == '\0'){
            /* incrimenter le compteur à chaque fois
             qu'on atteint la fin de chaine */
            NbMotsTotal+=a->nbOcc;
        }
        else 
            // verifier le sous arbre gauche
            dicoNbMotsTotal(a->gauche);
        if (a->droite != NULL)
            // verifier le sous arbre droite
            dicoNbMotsTotal(a->droite);
    }
    return NbMotsTotal;
}
/* ***************************************************************************************************************** */


/* *************************************************** Exist + Occ *************************************************** */

//Trouver le nombre d'occurences dans le dictionnaire
int dicoNbOcc(char *mot, TArbre* a){
  /* verifier si l'arbre est vide ou le mot < à la racine
    càd qu'il est nouveau puisque l'insertion est dans 
    l'ordre alphabetique */
  if((a == NULL)||(*mot < a->data)) return 0;
  /* le mot se trouve dans la racine*/
  if(*mot == a->data){
    if(*mot == '\0') return a->nbOcc;
    return dicoNbOcc(mot+1, a->gauche);
  }
  // verifier le sous arbre droite
  return dicoNbOcc(mot, a->droite);
}


/* ***************************************************************************************************************** */





 
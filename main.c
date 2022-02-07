#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dico.h"
#include "arbre.h"

int main(int argc, char* argv[]){
    char motPioche[100] = {0};
    int coupsRestants;
    long tailleMot = 0;
    char *buffer = NULL;
    TArbre* dico=NULL;
    TArbre* dicoCopy=NULL;
    printf("Bienvenue dans Notre Dictionnaire !\n\n");
    printf("Combien de mot à piocher ? !\n\n");
    scanf("%d",&coupsRestants);

    // Construire un dictionnaire vide
    dico = arbreConsVide();
    /* On continue à jouer tant qu'il reste au moins un coup à jouer */
    while (coupsRestants > 0){
        char motPioche[100] = {0};
        long tailleMot = 0;
        char *buffer = NULL;
        // Piocher un mot
        if (!piocherMot(motPioche))
            exit(0);

        tailleMot = strlen(motPioche);
        buffer = malloc((tailleMot+1) * sizeof(char));
        strcpy(buffer, motPioche);
        printf("motPioche est %s \n",motPioche);
        dicoInsererMot(buffer, &dico);
       /* printf("aaaaaaaaaa \n" );
        aff2(dico);
        printf("aaaaaaaaaa \n" );*/
    
        char bufferAff[100]={0}; // Buffer servant à stocker les mots à écrire
        int cur = 0; // Case courante à remplir
        dicoAfficher(dico,bufferAff,&cur);
        printf("Le nbr d'occ du mot %s est %d \n",buffer,dicoNbOcc(buffer,dico));
        
        printf("\n");
        coupsRestants--;
       // printf("Nb coups restants = %d \n",coupsRestants);
    }
   // printf("FIINNN \n");
}

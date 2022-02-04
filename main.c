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

    printf("Bienvenue dans Notre Dictionnaire !\n\n");
    printf("Combien de mot à piocher ? !\n\n");
    scanf("%d",&coupsRestants);

    // Construire un dictionnaire vide
    dico = arbreConsVide();
           
    /* On continue à jouer tant qu'il reste au moins un coup à jouer */
    while (coupsRestants > 0){
        // Piocher un mot
        if (!piocherMot(motPioche))
            exit(0);
        
        tailleMot = strlen(motPioche);
        buffer = malloc((tailleMot+1) * sizeof(char));
        strcpy(buffer, motPioche);
        dicoInsererMot(buffer, dico);
        printf("aaaaaaaaaa \n" );
         aff(dico);
        printf("aaaaaaaaaa \n" );
        char bufferAff[100]={0}; // Buffer servant à stocker les mots à écrire
        int cur = 0; // Case courante à remplir
        dicoAfficher(dico,bufferAff,&cur);
        dicoNbOcc(motPioche,dico);
        printf("\n");
        coupsRestants--;
    }
}

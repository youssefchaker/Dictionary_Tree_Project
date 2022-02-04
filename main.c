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
    TArbre* dico;

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
        buffer = malloc(tailleMot * sizeof(char));
        strcpy(buffer, motPioche);
        dicoInsererMot(buffer, dico);
        dicoAfficher(dico);
        dicoNbOcc(motPioche,dico);
        printf("\n");
    }
}

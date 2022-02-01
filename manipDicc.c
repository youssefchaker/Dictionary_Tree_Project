//get a random number(max:nombre max)
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
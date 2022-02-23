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
    //srand(time(NULL));
    return (rand() % nombreMax);
}

//choisir un mot aleatoire depuis le dictionnaire
int piocherMot(char *motPioche)
{
    FILE *dico = NULL;
    int nombreMots = 0;   //nombre de mots dans le fichier
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
    } while (caractereLu != EOF);
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
void aff2(TArbre *a)
{
    if (a != NULL)
    {
        printf("%c \n ", a->data);
        printf("/ \n");
        aff2(a->gauche);
        printf("   '\' \n");
        aff2(a->droite);
    }
}
void aff2(TArbre* a){
  if (a != NULL){
    printf("%c aaaaaaaaa %d \n ",a->data, a->nbOcc);
    
    //aff2(a->gauche);
    //printf("Mche Droite \n");
    aff2(a->droite);
  }
}

void aff(TArbre *a)
{
    if (a != NULL)
    {
        printf("%c aaaaaaaaa %d \n ", a->data, a->nbOcc);
        aff(a->gauche);
        aff(a->droite);
    }
}
TArbre *dicoBranche(char mot[])
{
    if (mot[0] == '\0')
        return arbreCons('~', 1, NULL, NULL);
    return arbreCons(mot[0], 0, dicoBranche(mot + 1), NULL);
}

// Insertion dans le dictionnaire
TArbre *dicoInsererNouvMot(char mot[], TArbre *a)
{
    // verifier si l'arbre est nulle
    if (a->data == '\0')
    {
        return dicoBranche(mot);
    }
    /* verifier si le caractere est un caractere de fin de chaine
     si c'est le cas verifier le mot dans la racine*/
    if (mot[0] == '\0')
        return (a->data == '~') ? a : arbreCons('~', 1, NULL, a);

    /* si c'est un nouveau mot construire un nouveau 
      sous arbre contenant le nouveau mot et l'affecter
      au fg*/
    if ((a->data != '\0') && (mot[0] < a->data))
    {
        return arbreCons(mot[0], 0, dicoBranche(mot + 1), a);
    }
    /* si le mot commence avec la même lettre */
    if (mot[0] == a->data)
    {
        /* l'inserer dans le sous arbre gauche*/
        a->gauche = dicoInsererNouvMot(mot + 1, a->gauche);
        return a;
    }
    a->droite = dicoInsererNouvMot(mot, a->droite);
    return a;
}
//  Incrementer le nombre d'occurences dans dictionnaire
void dicoNbOccAdd(char *mot, TArbre **a)
{
    if ((*a)->data == '~')
    {
        (*a)->data = '\0';
    }
    // verifier si le mot se trouve à la racine
    if (*mot == (*a)->data)
    {
        if (*mot == '\0')
        {
            (*a)->data = '~';
            (*a)->nbOcc += 1;
            return;
        }
        // incrimenter son occurance
        return dicoNbOccAdd(mot + 1, &((*a)->gauche));
    }
    // verifier le sous arbre droite
    return dicoNbOccAdd(mot, &((*a)->droite));
}

//insert a word in the dictionary
void dicoInsererMot(char mot[], TArbre **a)
{
    if (dicoNbOcc(mot, *a) == 0)
    {
        // Nouveau mot
        (*a) = dicoInsererNouvMot(mot, *a);
    }
    else
        // mot exisistant alors incrimenter on occurence

        dicoNbOccAdd(mot, a);
}

/* ***************************************************************************************************************** */

/* *************************************************** Affichage *************************************************** */
//Afficher tout le dictionnaire
void dicoAfficherProp(TArbre *a, char *buffer, int *cur)
{

    if ((a->data != '\0'))
    {
        buffer[*cur] = a->data;
        *cur += 1;
        if (a->data == '~')
        {
            buffer[*cur - 1] = '\0';
            // afficher le mot et son occurence
            int motSize = strlen(buffer);
            printf("\t |  %s", buffer);
            for (int i = 0; i < 17 - motSize; i++)
            {
                printf(" ");
            }
            printf("|         %d           |\n", a->nbOcc);
        }
        else
        {

            dicoAfficherProp(a->gauche, buffer, cur);
        }
        buffer[*cur] = '\0';
        *cur -= 1;
        if ((a->droite != NULL))
        {
            dicoAfficherProp(a->droite, buffer, cur);
        }
    }
    else
        printf("Dictionnaire est vide \n");
}
//Afficher tout le dictionnaire
void dicoAfficher(TArbre *a, char *buffer, int *cur)
{

    if ((a->data != '\0'))
    {
        buffer[*cur] = a->data;
        *cur += 1;
        if (a->data == '~')
        {
            buffer[*cur - 1] = '\0';
            // afficher le mot et son occurence
            printf("\t %s -> [ %d ]\n", buffer, a->nbOcc);
        }
        else
        {

            dicoAfficher(a->gauche, buffer, cur);
        }
        buffer[*cur] = '\0';
        *cur -= 1;
        if ((a->droite != NULL))
        {
            dicoAfficher(a->droite, buffer, cur);
        }
    }
    else
        printf("Dictionnaire est vide \n");
}
/* ***************************************************************************************************************** */

/* *************************************************** Statistiques *************************************************** */
// Trouver le nombre de mots differents
int dicoNbMotsDifferents(TArbre *a)
{
    static int NbMotsDifferents = 0;
    if (a != NULL)
    {
        /* incrimenter à chaque fois qu'on
          atteint la fin de chaine */
        if (a->data == '~')
        {
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
int dicoNbMotsTotal(TArbre *a)
{
    static int NbMotsTotal = 0;
    if (a != NULL)
    {
        if (a->data == '~')
        {
            /* incrimenter le compteur à chaque fois
             qu'on atteint la fin de chaine */
            NbMotsTotal += a->nbOcc;
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
int dicoNbOcc(char mot[], TArbre *a)
{
    /* le mot se trouve dans la racine*/
    if (a->data == '~')
    {
        a->data = '\0';
    }
    if ((*mot == a->data))
    {
        if (*mot == '\0')
        {
            a->data = '~';
            return a->nbOcc;
        }
        return dicoNbOcc(mot + 1, a->gauche);
    }

    /* verifier si l'arbre est vide ou le mot < à la racine
  càd qu'il est nouveau puisque l'insertion est dans 
  l'ordre alphabetique */
    if ((a->data == '\0') || (mot[0] < a->data))
    {
        return 0;
    }

    // verifier le sous arbre droite
    return dicoNbOcc(mot, a->droite);
}

/* ******************************************** Mgaaa7ef ******************************************************** */
#define COUNT 10
#define MAX_HEIGHT 1000

int print_next = 0;
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
int gap = 3;

typedef struct asciinode asciinode;
struct asciinode
{
    asciinode *gauche, *droite;

    //length of the edge from this node to its children
    int edge_length;

    int height;

    int lablen;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;
    int nbOcc;
    //max supported unit32 in dec, 10 digits max
    char label[11];
};

void print_level(asciinode *node, int x, int level)
{
    int i, isleft;
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    if (level == 0)
    {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++)
        {
            printf(" ");
        }
        print_next += i;
        printf("\033[107m");
        system("setterm -bold on");
        printf("\033[1;31m");
        printf("%s", node->label);
        printf("\033[0;37m");
        system("setterm -bold off");
        printf("\033[0m");
        print_next += node->lablen;
    }
    else if (node->edge_length >= level)
    {
        if (node->gauche != NULL)
        {
            for (i = 0; i < (x - print_next - (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->droite != NULL)
        {
            for (i = 0; i < (x - print_next + (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else
    {
        print_level(node->gauche,
                    x - node->edge_length - 1,
                    level - node->edge_length - 1);
        print_level(node->droite,
                    x + node->edge_length + 1,
                    level - node->edge_length - 1);
    }
}

//This function fills in the edge_length and
//height fields of the specified tree
int MAX(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
int MIN(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

void compute_lprofile(asciinode *node, int x, int y)
{
    int i, isleft;
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->gauche != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < 100; i++)
        {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->gauche, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->droite, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(asciinode *node, int x, int y)
{
    int i, notleft;
    if (node == NULL)
        return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->droite != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < 100; i++)
        {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->gauche, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->droite, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_edge_lengths(asciinode *node)
{
    int h, hmin, i, delta;
    if (node == NULL)
        return;
    compute_edge_lengths(node->gauche);
    compute_edge_lengths(node->droite);

    /* first fill in the edge_length of node */
    if (node->droite == NULL && node->gauche == NULL)
    {
        node->edge_length = 0;
    }
    else
    {
        if (node->gauche != NULL)
        {
            for (i = 0; i < node->gauche->height && i < 100; i++)
            {
                rprofile[i] = -10000;
            }
            compute_rprofile(node->gauche, 0, 0);
            hmin = node->gauche->height;
        }
        else
        {
            hmin = 0;
        }
        if (node->droite != NULL)
        {
            for (i = 0; i < node->droite->height && i < 100; i++)
            {
                lprofile[i] = 10000;
            }
            compute_lprofile(node->droite, 0, 0);
            hmin = MIN(node->droite->height, hmin);
        }
        else
        {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++)
        {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((node->gauche != NULL && node->gauche->height == 1) ||
             (node->droite != NULL && node->droite->height == 1)) &&
            delta > 4)
        {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->gauche != NULL)
    {
        h = MAX(node->gauche->height + node->edge_length + 1, h);
    }
    if (node->droite != NULL)
    {
        h = MAX(node->droite->height + node->edge_length + 1, h);
    }
    node->height = h;
}

struct asciinode *build_ascii_tree_recursive(TArbre *t)
{
    struct asciinode *node;

    if (t == NULL)
        return NULL;

    node = malloc(sizeof(asciinode));
    node->gauche = build_ascii_tree_recursive(t->gauche);
    node->droite = build_ascii_tree_recursive(t->droite);

    if (node->gauche != NULL)
    {
        node->gauche->parent_dir = -1;
    }

    if (node->droite != NULL)
    {
        node->droite->parent_dir = 1;
    }
    if (t->data != '~')
        sprintf(node->label, " %c ", t->data);
    else
        sprintf(node->label, " %d ", t->nbOcc);
    node->lablen = strlen(node->label);

    return node;
}

//Copy the tree into the ascii node structre
struct asciinode *build_ascii_tree(TArbre *t)
{
    struct asciinode *node;
    if (t == NULL)
        return NULL;
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node)
{
    if (node == NULL)
        return;
    free_ascii_tree(node->gauche);
    free_ascii_tree(node->droite);
    free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.

//prints ascii tree for given Tree structure
void print_ascii_tree(TArbre *t)
{
    asciinode *proot;
    int xmin, i;
    if (t == NULL)
        return;
    proot = build_ascii_tree(t);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < 100; i++)
    {
        lprofile[i] = 10000;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < 100; i++)
    {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++)
    {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= 100)
    {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n",
               100);
    }
    free_ascii_tree(proot);
}

/* ******************************************** Mgaaa7ef Insert******************************************************** */

void dicoNbOccSim(char *mot, TArbre **a)
{
    if ((*a)->data == '~')
    {
        (*a)->data = '\0';
    }
    // verifier si le mot se trouve à la racine
    if (*mot == (*a)->data)
    {
        (*a)->nbOcc=1;
        if (*mot == '\0')
        {
            (*a)->data = '~';
            return;
        }
        // incrimenter son occurance
        return dicoNbOccSim(mot + 1, &((*a)->gauche));
    }
    // verifier le sous arbre droite
    return dicoNbOccSim(mot, &((*a)->droite));
}

void dicoNbOccSimInit(char *mot, TArbre **a)
{
    if ((*a)->data == '~')
    {
        (*a)->data = '\0';
    }
    // verifier si le mot se trouve à la racine
    if (*mot == (*a)->data)
    {
       
        if (*mot == '\0')
        {
            (*a)->data = '~';
            return;
        }else{
            
            (*a)->nbOcc=0;
        
        }
        // incrimenter son occurance
        return dicoNbOccSimInit(mot + 1, &((*a)->gauche));
    }
    // verifier le sous arbre droite
    return dicoNbOccSimInit(mot, &((*a)->droite));
}

void print_levelInsert(asciinode *node, int x, int level, char *mot)
{
    int i, isleft;
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    if (level == 0)
    {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++)
        {
            printf(" ");
        }
        print_next += i;
        char copyMot[11];
        copyMot[0] = mot[0];
       // printf("!!!! nbOcc Node= %d \n",node->nbOcc);
        printf("\033[107m");
        system("setterm -bold on");
        if ((node->nbOcc != 0) && (node->label != "~"))
        {
            printf("\033[1;31m"); //red
            
        }
        else
        {
            printf("\033[30m"); //Black

            mot = mot + 1;
        }
        printf("%s", node->label);
        printf("\033[0;37m");
        system("setterm -bold off");
        printf("\033[0m");
        print_next += node->lablen;
    }
    else if (node->edge_length >= level)
    {
        if (node->gauche != NULL)
        {
            for (i = 0; i < (x - print_next - (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->droite != NULL)
        {
            for (i = 0; i < (x - print_next + (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else
    {
        print_levelInsert(node->gauche,
                          x - node->edge_length - 1,
                          level - node->edge_length - 1, mot);
        print_levelInsert(node->droite,
                          x + node->edge_length + 1,
                          level - node->edge_length - 1, mot);
    }
}

struct asciinode *build_ascii_tree_recursiveInsert(TArbre *t, char *mot)
{
    struct asciinode *node;

    if (t == NULL)
        return NULL;

    node = malloc(sizeof(asciinode));
    node->gauche = build_ascii_tree_recursiveInsert(t->gauche, mot);
    node->droite = build_ascii_tree_recursiveInsert(t->droite, mot);

    if (node->gauche != NULL)
    {
        node->gauche->parent_dir = -1;
    }

    if (node->droite != NULL)
    {
        node->droite->parent_dir = 1;
    }
   
        sprintf(node->label, " %c ", t->data);
        node->nbOcc= t->nbOcc;
        
    
    node->lablen = strlen(node->label);

    return node;
}

//Copy the tree into the ascii node structre
struct asciinode *build_ascii_treeInsert(TArbre *t, char *mot)
{
    struct asciinode *node;
    if (t == NULL)
        return NULL;
    node = build_ascii_tree_recursiveInsert(t, mot);
    node->parent_dir = 0;
    return node;
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.

//prints ascii tree for given Tree structure
void print_ascii_treeInsert(TArbre *t, char *mot)
{
    dicoNbOccSim(mot, &t);
   // aff(t);
    asciinode *proot;
    int xmin, i;
    if (t == NULL)
        return;
    proot = build_ascii_treeInsert(t, mot);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < 100; i++)
    {
        lprofile[i] = 10000;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < 100; i++)
    {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++)
    {
        print_next = 0;
        print_levelInsert(proot, -xmin, i, mot);
        printf("\n");
        
    }
    //printf("aaaa data=%c",(*t)->label);
    dicoNbOccSimInit(mot, &t);
    if (proot->height >= 100)
    {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n",
               100);
    }
    free_ascii_tree(proot);
}

#ifndef DEF_ARBRE
#define DEF_ARBRE
typedef struct TArbre {
    int data;
    int nbOcc;
    struct TArbre* left;
    struct TArbre* right;
}TArbre;

TArbre arbreConsVide(void);
int arbreEstVide(TArbre a);
TArbre arbreCons(char c, int n, TArbre* fg, TArbre* fd);
char arbreRacineLettre(TArbre a);
int arbreRacineNbOcc(TArbre a);
TArbre* arbreFilsGauche(TArbre* a);
TArbre* arbreFilsDroit(TArbre* a);
void arbreSuppr(TArbre* a);
#endif
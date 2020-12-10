/* Header gestion admin prototypes et structures */

typedef struct{
    char mail[100];
    char signe[50];
    char decan[100];
    char abonnement[20];
}CLIENT;

void listing_client(FILE *rep);
void saisir_nouveau_client(FILE *rep);
int rechercher_client (FILE *rep, char *nomrech);
void saisie_mot_cle(FILE *fic, REPONSE *p);
void afficher_mot_cle(FILE *fic);
//void rechercher_theme_signe(FILE *fic, char *recsigne, char *rectheme);
void effacer_client (FILE *rep, char *nomrech);
void saisir_nouveau_mot(FILE *mot);
void effacer_mot_theme(FILE *mot);
void listing_mot_cle(FILE *mot);

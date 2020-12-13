/* Header gestion admin prototypes et structures */

typedef struct{
    char mail[100];
    char signe[50];
    char decan[100];
    char abonnement[20];
}CLIENT;

void listing_client();
void saisir_nouveau_client();
int rechercher_client (char *nomrech);
void saisie_reponse_theme(REPONSE *p);
void afficher_reponse_theme();
void supprimer_reponse_theme(char *recsigne, char *rectheme);
//void rechercher_theme_signe(FILE *fic, char *recsigne, char *rectheme);
void effacer_client (char *nomrech);
void saisir_nouveau_motcle_theme();
void effacer_motcle_theme();
void listing_motcle_theme();

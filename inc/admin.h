/* Header gestion admin prototypes et structures */

typedef struct
{
    	char mail[100];
    	char signe[50];
	char decan[100];
    	char abonnement[20];
}CLIENT;

void listing_client(FILE *rep);
void saisir_nouveau_client(FILE *rep);
int rechercher_client (FILE *rep, char *nomrech);
void modifier_client(FILE *rep, char *nomrech);
void saisie_mot_cle(FILE *fic, REPONSE *p);
void afficher_mot_cle(FILE *fic);
void viderBuffer(void);
int lire(char *chaine, int longueur);


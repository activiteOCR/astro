/* Header gestion admin prototypes et structures */

void listing_client(FILE *rep);
void saisir_nouveau_client(FILE *rep);
int rechercher_client (FILE *rep, char *nomrech);
void modifier_client(FILE *rep, char *nomrech);

typedef struct
{
    char mail[100];
    char signe[50];
	char decan[100];
    char abonnement[20];
}CLIENT;
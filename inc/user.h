/* Header gestion admin prototypes et structures */


void saisie_email(EMAIL *);
void viderBuffer(void);
int lire(char *chaine, int);
int rec_cle_amour(EMAIL *);
int rec_cle_travail(EMAIL *);
int rec_cle_sante(EMAIL *);
int rec_mois(EMAIL *);
int rec_decan(EMAIL *);
int rec_jour(EMAIL *);
void rec_signe(char *,size_t,EMAIL *);
int calc_signe(int,int,char *,size_t);
void ecriture_email(EMAIL *,char *);
void rechercher_theme_signe(char *answer,char *recsigne,char *rectheme);

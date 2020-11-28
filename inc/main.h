/*Fichier main.h ==> prototypes et structures */

typedef struct{
    char adress_EM[50];
	char adress_DEST[50];
    char OBJ[100];
	char CORPS[1500];
}EMAIL;

typedef struct
{
    char signe[20];
    char theme[20];
    char reponseTheme[1500];
    char decan[20];
    char reponseDecan[1500];
}REPONSE;

void print_help(char * prgName);
void print_error(char * prgName, const char * errStr);
void menu_utilisateur(void);
void menu_admin(FILE *rep, FILE *fic, REPONSE *p);


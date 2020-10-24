/*Fichier main.h ==> prototypes et structures */

void print_help(char * prgName);
void print_error(char * prgName, char * errStr);
void menu_utilisateur();
void menu_admin(FILE *rep);

typedef struct{
    char adress_EM[50];
	char adress_DEST[50];
    char OBJ[100];
	char CORPS[1500];
}EMAIL;

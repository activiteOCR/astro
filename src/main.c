#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/main.h"
#include "../inc/admin.h"


int main(int argc, char *argv[])
{
	/* 0 => users ; 1 => admin */
	int mode = 0;
	FILE *rep = NULL;
	FILE *fic = NULL;

    REPONSE p;

	// parsing des arguments
	if(argc > 3)
	{
		print_error( argv[0], " nombre d'arguments invalide" );
		return EXIT_FAILURE;
	}
	// parsing des arguments
	else if(argc < 2)
	{
		mode = 0;
	}
	// parsing des arguments
	else if (argc == 2)
	{
		if( strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0)
		{
			// affichage aide
			print_help(argv[0]);

			// MACRO stdlib gestion exit
			return EXIT_SUCCESS;
		}

		else if( strcmp(argv[1], "-admin") == 0)
		{
			printf(" le password admin est manquant dans le second champs\n");
			exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
		}
		else
		{
			print_error( argv[0], " -h or -help for help menu or none if mode users is required" );
			exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
		}
	}
	else
	{
		if( strcmp(argv[1], "-admin") == 0)
		{
			if( strcmp(argv[2], "P18M") == 0)
			{
				mode = 1;
			}
			else
			{
				print_error( argv[0], " -h or -help for help menu or none if mode users is required" );
				exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
			}
		}
		else
		{
			print_error( argv[0], " -h or -help for help menu or none if mode users is required" );
			exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
		}
	}

	switch(mode)
	{
		case 0:
			menu_utilisateur();
			//printf(" ici appel du menu mode users\n");
		break;
		case 1:
			menu_admin(rep, fic, &p);
			//printf(" ici appel du menu mode admin\n");
		break;
		default:
            exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
        break;
	}


	return EXIT_SUCCESS;
}

// Affiche l'aide du programme
void print_help(char *prgName)
{
	printf("\n Show program help \n\n");
	printf(" %s <opt> <password> \n\n", prgName);
	printf(" <opt> is either '-h' or '-help' or '-admin'.\n\n");
	printf(" <password> is the password of the admin.\n\n");
}

// Affiche l'erreur errStr, puis l'aide du programme
void print_error(char *prgName, const char *errStr)
{
	printf(" Error : '%s'\n", errStr);
	print_help(prgName);
}

void menu_utilisateur()
{
	int choix = 0;

	//rep=fopen("bdd_client.txt","a+");

	do
	{
		do
		{
			printf("\nMenu utilisateur:\n");
			printf("1-Envoyer votre mail a Madame Soleil\n");
			printf("2-les promotions du jour celeste\n");
			printf("3-quitter l'astre solaire\n");
			printf("Votre choix : ");
			scanf("%d", &choix);
		}while (choix < 1 || choix > 3);

		switch (choix)
		{
			case 1 : printf(" ici appel de la fonction saisie mail\n");//saisie_mail(fichier);
				 break;
			case 2 : printf(" Aujourd'hui super promo pour deux themes Astral achete un theme astral offert\n");
				 break;

			default : break;
		}
	}while (choix != 3);
}

void menu_admin(FILE *rep, FILE *fic, REPONSE *p)
{
	int choix = 0;
	int recherche = 0;
	char nomrech[100];

	do
	{
		do
		{
			printf("\nMenu Admin:\n");
			printf("1-Ajouter un client dans la bdd\n");
			printf("2-Afficher la bdd client\n");
			printf("3-Rechercher un client dans la bdd\n");
			printf("4-Modifier l'abonnement d'un client dans la bdd\n");
			printf("5-Ajouter un mot cle et sa reponse dans la bdd mot cle\n");
			printf("6-Afficher les mots cles et leurs reponses\n");
			printf("7-Rechercher un mot cle et sa reponse\n");
			printf("8-Supprimer un mot cle et sa reponse\n");
			printf("9-quitter le programme\n");
			printf("Votre choix : ");
			scanf("%d", &choix);
		}while (choix < 1 || choix > 9);

		switch (choix)
		{
			case 1 : 	saisir_nouveau_client(rep);
				 break;

			case 2 : 	listing_client(rep);
				 break;

			case 3 :	printf("Saisissez un nom a rechercher\n");
						scanf("%s",nomrech);
						recherche=rechercher_client (rep, nomrech);
						//memset effacer le nom saisie?
				 break;

			case 4 : 	printf("Saisissez un nom sur laquelle vous voulez changer l'abonnement\n");
						scanf("%s",nomrech);
						modifier_client(rep, nomrech);
						//memset effacer le nom saisie?
				 break;

			case 5 :    printf("Ajouter un mot cle et sa reponse dans la bdd mot cle\n");
                       		    saisie_mot_cle(fic, p);
				 break;
			case 6 :    printf("Afficher les mots cles et leurs reponses\n");
                       		    afficher_mot_cle(fic);
				 break;
			case 7 : printf(" ici appel de la fonction Rechercher un mot cle et sa reponse\n");
				 break;
			case 8 : printf(" ici appel de la fonction Supprimer un mot cle et sa reponse\n");
				 break;

			default : break;
		}
	}while (choix != 9);
}

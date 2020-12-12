#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/main.h"
#include "../inc/admin.h"
#include "../inc/user.h"

# define ANS 3500

int main(int argc, char *argv[])
{
	/* 0 => users ; 1 => admin */
	int mode = 0;
	FILE *rep = NULL;
	FILE *fic = NULL;
	FILE *mot = NULL;

    REPONSE p;
    EMAIL q;

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
			print_error( argv[0], " -h or -help pour le menu aide ou pas d'option si mode utilisateur" );
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
				print_error( argv[0], " -h or -help pour le menu aide ou pas d'option pour le mode utilisateur" );
				exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
			}
		}
		else
		{
			print_error( argv[0], " -h or -help le menu aide ou pas d'option pour le mode utilisateur" );
			exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
		}
	}

	switch(mode)
	{
		case 0:
			menu_utilisateur(rep, &q);
			//printf(" ici appel du menu mode users\n");
		break;
		case 1:
			menu_admin(rep, fic, mot, &p);
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
	printf("\n Aide \n\n");
	printf(" %s <opt> <password> \n\n", prgName);
	printf(" <opt> possible '-h' ou '-help' ou '-admin'.\n\n");
	printf(" <password> is the password of the admin.\n\n");
}

// Affiche l'erreur errStr, puis l'aide du programme
void print_error(char *prgName, const char *errStr)
{
	printf(" Error : '%s'\n", errStr);
	print_help(prgName);
}

void menu_utilisateur(FILE *rep, EMAIL *q)
{
	int choix = 0;
	int EM=-1;
    char proposition[]="\nPour un theme astral personalise, nous vous conseillons notre abonnement MERCURE a 49 euros par jour\n";
	char perso[]="\nMerci pour votre email.\nGrace à votre abonnement MERCURE Madame SOLEIL prendra contact par telephone avec vous pour un theme astral personnalise\nA tres bientot....";
	char erreur[]="\nVotre date de naissance est manquante ou incomplete\nNous ne sommes pas en mesure de vos donner votre theme astral.\nVeuillez preciser votre demande merci.\nMadame SOLEIL.";
	char zodiaque[11]="";
    int mois=0, jour=0;
	int atheme=0,stheme=0,ttheme=0;
    char ztheme[8]="";
	char fullname[ANS]="";
	char answer[ANS]="";

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
			case 1 :    saisie_email(q);
                        EM=rechercher_client (rep, q->adress_EM);
                        // réponse type en fct
                        if (EM==1) // abo OK réponse personnalisé
                        {
                            ecriture_email(q,perso,zodiaque);
                            goto fin;
                            //choix = 3;
                        }
                        else if (EM==2) // deja dans la base client mais non abonné Proposition abonnement
                        {
                            ecriture_email(q,proposition,zodiaque);
                            goto fin;
                            //choix = 3;
                        }
                        else
                        {
                            rec_signe(zodiaque,sizeof(zodiaque),q); // recherche si son signe est indiqué
                           
                           //printf("\nsigne trouve = %s",zodiaque); // Pour test DEBUG
                           //printf("\nlongueur signe = %d\n",strlen(zodiaque)); // Pour test DEBUG
                        }

                        // Si pas de signe donné recherche date et sinon envoi mail erreur predefini
                        if (strlen(zodiaque)==0)
                        {
                            mois=rec_mois(q); // recherche du mois de la date de naissance indiqué dans le mail
                            jour=rec_jour(q); // recherche du jour de la date de naissance indiqué dans le mail
                            
                            printf("\nMOIS trouve = %d",mois); // Pour test DEBUG
                            printf("\nJOUR trouve = %d",jour); // Pour test DEBUG


                            if (mois==0 || jour==0)
                            {
                                ecriture_email(q,erreur,zodiaque);
                                goto fin;
                                //choix = 3;
                            }
                            else
                            {
                                //fct de recherche de signe en fct date trouvee
                                calc_signe(mois,jour,zodiaque,sizeof(zodiaque));
                            }
                        }
                        // Recherche des mots clés dans les fichers
                        atheme=rec_cle_amour(q);
                        stheme=rec_cle_sante(q);
                        ttheme=rec_cle_travail(q);

                        if (atheme==1) //affichage du thème Amour
                        {
                            strcat(fullname,"\nTheme Amour:\n");
                            strncpy(ztheme, "amour", 8);
                            rechercher_theme_signe(answer,zodiaque,ztheme);
                            strcat(fullname,answer);
                            strcat(fullname,"\n");
                        }
                        else if (stheme==1) //affichage du thème Sante
                        {
                            strcat(fullname,"\nTheme Sante:\n");
                            strncpy(ztheme, "sante", 8);
                            rechercher_theme_signe(answer,zodiaque,ztheme);
                            strcat(fullname, answer);
                            strcat(fullname,"\n");
                        }
                        else if (ttheme==1) //affichage du thème Travail
                        {
                            strcat(fullname,"\nTheme Travail:\n");
                            strncpy(ztheme, "travail", 8);
                            rechercher_theme_signe(answer,zodiaque,ztheme);
                            strcat(fullname, answer);
                            strcat(fullname,"\n");
                        }
                        else
                        {
                            strcat(fullname,"\nAmour:\n");
                            strncpy(ztheme, "amour", 8);
                            rechercher_theme_signe(answer,zodiaque,ztheme);
                            strcat(fullname,answer);
                            strcat(fullname,"\nSante:\n");
                            strncpy(ztheme, "sante", 8);
                            rechercher_theme_signe(answer,zodiaque,ztheme);
                            strcat(fullname, answer);
                            strcat(fullname,"\nTravail:\n");
                            strncpy(ztheme, "travail", 8);
                            rechercher_theme_signe(answer,zodiaque,ztheme);
                            strcat(fullname, answer);
                            strcat(fullname,"\n");
                        }
                        ecriture_email(q,fullname,zodiaque);
                        memset(zodiaque,'0',11);
				 break;
			case 2 :    printf(" Aujourd'hui c'est votre jour de chance avec le code promo ILFAITSOLEIL404 vous obtiendrez une reduction 0.49 centimes d'euros sur votre abonnement\n");
				 break;

			default : break;
		}
     goto fin;
	}while (choix != 3);
    fin:
    printf("\nSortie menu utilisateur:\n");
}

void menu_admin(FILE *rep, FILE *fic, FILE *mot, REPONSE *p)
{
	int choix = 0;
	char nomrech[100];
	char recsigne[100];
	char rectheme[100];
	char answer[ANS]="";

	do
	{
		do
		{
			printf("\nMenu Admin:\n");
			printf("1-Ajouter un client dans la bdd\n");
			printf("2-Afficher la bdd client\n");
			printf("3-Rechercher un client dans la bdd\n");
			printf("4-Supprimer un client de la bdd\n");
			printf("5-Ajouter une reponse dans la bdd par signe et theme\n");
			printf("6-Afficher les reponses par signes et par themes\n");
			printf("7-Afficher la reponse par un signe et un theme choisi\n");
			printf("8-Supprimer un mot cle et sa reponse\n");
			printf("9-Ajouter un mot cle dans un theme\n");
			printf("10-Supprimer un mot cle dans un theme\n");
			printf("11-Afficher les mots cle pour un theme\n");
			printf("12-quitter le programme\n");
			printf("Votre choix : ");
			scanf("%d", &choix);
			getchar();
		}while (choix < 1 || choix > 12);

		switch (choix)
		{
			case 1 : 	saisir_nouveau_client(rep);
				 break;

			case 2 : 	listing_client(rep);
				 break;

			case 3 :	printf("Saisissez le mail du client a rechercher\n");
                        scanf("%s",nomrech);
                        rechercher_client (rep, nomrech);
				 break;

			case 4 : 	printf("Saisissez le mail du client a supprimer\n");
                        scanf("%s",nomrech);
                        effacer_client(rep,nomrech);
				 break;

			case 5 :    printf("Ajouter une reponse dans la bdd par signe et theme\n");
                        saisie_mot_cle(fic, p);
				 break;
			case 6 :    printf("Afficher toutes les reponses\n");
                        afficher_mot_cle(fic);
				 break;
			case 7 : 	printf("Afficher la reponse pour un signe et un theme choisi\n");
                        printf("\nSaisissez un signe du zodiaque \n(belier / taureau / gemeaux \ncancer / lion  / vierge \nbalance / scorpion / sagittaire \ncapricorne / verseau / poissons )\n");
                        scanf("%s",recsigne);
                        printf("\nSaisissez un theme\n(amour / sante / travail)\n");
                        scanf("%s",rectheme);
                        rechercher_theme_signe(answer, recsigne, rectheme);
                        //rechercher_theme_signe (fic, recsigne, rectheme);
				 break;
			case 8 : 	printf(" ici appel de la fonction supprimer un mot cle et sa reponse\n");
				 break;
			case 9 : 	saisir_nouveau_mot(mot);
				 break;
			case 10 : 	effacer_mot_theme(mot);
				 break;
			case 11 : 	listing_mot_cle(mot);
				 break;

			default : break;
		}
	}while (choix != 12);
}

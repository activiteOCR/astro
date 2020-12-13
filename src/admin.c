/* Fichier source gestion admin */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/main.h"
#include "../inc/admin.h"
#include "../inc/user.h"

void listing_client()
{
	FILE *rep=NULL;
	CLIENT p;

	rep=fopen("bdd_client.txt","r");

	if(rep != NULL)
    {
		fseek(rep, 0, SEEK_SET);
		while (fscanf(rep,"%s %s %s %s", p.mail, p.signe, p.decan, p.abonnement) !=EOF)
		{
			printf("\nAffichage de la base de donnée client: mail=%s, signe_zodiaque=%s, decan=%s, abonnement=%s", p.mail, p.signe, p.decan, p.abonnement);
		}
	}
	fclose(rep);
	printf("\n");
}

void saisir_nouveau_client()
{
    FILE *rep=NULL;
    CLIENT p;
    rep=fopen("bdd_client.txt","a+");
    fseek(rep, 0, SEEK_END);
	int fin=0;
    int testsig=0;
	int testdecan=0;
	int testab=0;

    if(rep != NULL)
    {
		do
		{
        	printf("Saisissez un mail (tapez: fin pour arreter) \n");
			scanf("%s",p.mail);
            if (strcmp(p.mail,"fin")==0)
                fin=1;
            else
            {
                do
                {
                    printf("\nSaisissez un signe du zodiaque \n(belier / taureau / gemeaux \ncancer / lion  / vierge \nbalance / scorpion / sagittaire \ncapricorne / verseau / poissons )\n\n");
                    scanf("%s",p.signe);
                    testsig=(strcmp(p.signe,"belier")*strcmp(p.signe,"taureau")*strcmp(p.signe,"gemeaux")*strcmp(p.signe,"cancer")*strcmp(p.signe,"lion")*strcmp(p.signe,"vierge")*strcmp(p.signe,"balance")*strcmp(p.signe,"scorpion")*strcmp(p.signe,"sagittaire")*strcmp(p.signe,"capricorne")*strcmp(p.signe,"verseau")*strcmp(p.signe,"poissons"));
                }while(testsig!=0);

                do
                {
                    printf("\nSaisissez un decan (1er, 2ieme, 3ieme)\n");
                    scanf("%s",p.decan);
                    testdecan=(strcmp(p.decan,"1er")*strcmp(p.decan,"2ieme")*strcmp(p.decan,"3ieme"));
                }while(testdecan!=0);

                do
                {
                    printf("\nSaisissez s'il y a un abonnement (oui/non)\n");
                    scanf("%s", p.abonnement);
                    testab=(strcmp(p.abonnement,"oui")*strcmp(p.abonnement,"non"));
                }while(testab!=0);

				fprintf(rep,"\n%s %s %s %s", p.mail, p.signe, p.decan, p.abonnement);
            }
		}while(fin!=1);
        printf("\n");
	}
    else
	{
		printf("\nl ouverture du fichier c'est mal passe!");
	}
	fclose(rep);
}

int rechercher_client ( char *nomrech)
{
	FILE *rep=NULL;
	int trouve=0;
	CLIENT p;

	rep=fopen("bdd_client.txt","r");

	fseek(rep, 0, SEEK_SET);
	while (fscanf(rep,"%s %s %s %s", p.mail, p.signe, p.decan, p.abonnement) !=EOF)
    	{
        if (strcmp(p.mail,nomrech)==0)
        {
            printf("\nAffichage des infos du client recherche: Mail=%s, Signe=%s, Decan=%s, Abonnement=%s\n", p.mail, p.signe, p.decan, p.abonnement);
            trouve=strlen(p.abonnement);
            if (strcmp(p.abonnement,"oui")==0) trouve=1; // pour exploitation par fct fred
            else trouve=2;// pour exploitation par fct fred
            return trouve;
        }
    	}
	if(trouve==0)
    {
        printf("\nLa personne n'est pas dans la base de donnees\n");
    }
	return trouve;
	fclose(rep);
}


void effacer_client (char *nomrech)
{
	FILE *rep=NULL;
	CLIENT p;
	rep=fopen("bdd_client.txt","r");
	fseek(rep, 0, SEEK_SET);
	FILE *temp=NULL;
	temp=fopen("bdd_client_tmp.txt","w+");
	int trouve=0;
	trouve=rechercher_client(nomrech);
	while (fscanf(rep,"%s %s %s %s", p.mail, p.signe, p.decan, p.abonnement) !=EOF)
	{
        if (strcmp(p.mail,nomrech)!=0)
        {
            fprintf(temp,"\n%s %s %s %s", p.mail, p.signe, p.decan, p.abonnement);
        }
	}
	if (trouve!=0)
	{
		printf("\neffacement confirme\n");
	}

	fclose(rep);
    fclose(temp);
	remove("bdd_client.txt");
	rename("bdd_client_tmp.txt", "bdd_client.txt");
	remove("bdd_client_tmp.txt");
}

void saisie_reponse_theme(REPONSE *p)
{
	FILE *fic=NULL;
	int testsig=0;
	int testtheme=0;
	int testdecan=0;
    	fic=fopen("reponse.dat","ab");

    	if (fic==NULL)
	{
		printf("impossible d'ouvrir le fichier en lecture\n");
		exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
	}
    	if(fic != NULL)
    	{
		do
		{
		printf("\nSaisissez un signe du zodiaque \n(belier / taureau / gemeaux \ncancer / lion  / vierge \nbalance / scorpion / sagittaire \ncapricorne / verseau / poissons )\n\n");
		scanf("%s",p->signe);
		testsig=(strcmp(p->signe,"belier")*strcmp(p->signe,"taureau")*strcmp(p->signe,"gemeaux")*strcmp(p->signe,"cancer")*strcmp(p->signe,"lion")*strcmp(p->signe,"vierge")*strcmp(p->signe,"balance")*strcmp(p->signe,"scorpion")*strcmp(p->signe,"sagittaire")*strcmp(p->signe,"capricorne")*strcmp(p->signe,"verseau")*strcmp(p->signe,"poissons"));
		}while(testsig!=0);
		fflush(stdin);

        if ((strlen(p->signe) > 0) && (p->signe[strlen (p->signe) - 1] == '\n'))
            p->signe[strlen (p->signe) - 1] = '\0';
		do
		{
		printf("Saisissez un theme (amour / sante / travail\n");
		scanf("%s",p->theme);
		testtheme=(strcmp(p->theme,"amour")*strcmp(p->theme,"sante")*strcmp(p->theme,"travail"));
		}while(testtheme!=0);

		if ((strlen(p->theme) > 0) && (p->theme[strlen (p->theme) - 1] == '\n'))
                p->theme[strlen (p->theme) - 1] = '\0';

		printf("Saisissez la reponse theme\n");
		fgetc(stdin);
		fgets(p->reponseTheme, sizeof(p->reponseTheme), stdin);
           	if ((strlen(p->reponseTheme) > 0) && (p->reponseTheme[strlen (p->reponseTheme) - 1] == '\n'))
                p->reponseTheme[strlen (p->reponseTheme) - 1] = '\0';
		do
		{
			printf("\nSaisissez un decan (1er, 2ieme, 3ieme)\n");
			scanf("%s",p->decan);
			testdecan=(strcmp(p->decan,"1er")*strcmp(p->decan,"2ieme")*strcmp(p->decan,"3ieme"));
		}while(testdecan!=0);

		if ((strlen(p->decan) > 0) && (p->decan[strlen (p->decan) - 1] == '\n'))
                p->decan[strlen (p->decan) - 1] = '\0';

		printf("Saisissez une reponse decan\n");
		fgetc(stdin);
		fgets(p->reponseDecan, sizeof(p->reponseDecan), stdin);
            /* Remove trailing newline, if there. */

		fwrite(p, 1 , sizeof(REPONSE) , fic );

    }
    else
	{
		printf("\nl ouverture du fichier c'est mal passe!");
	}
	fclose(fic);
}

void afficher_reponse_theme()
{
	REPONSE p;
	FILE *fic=NULL;
     	fic=fopen("reponse.dat","rb");


    if (fic==NULL)
	{
		printf("impossible d'ouvrir le fichier en lecture\n");
		exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
	}

	/* Seek to the beginning of the file */
	fseek(fic, 0, SEEK_SET);

    if(fic != NULL)
    {
        while (fread(&p, sizeof(REPONSE), 1, fic))
        printf("\nPour le signe=%s et le theme=%s, la reponse associe est:\n%s\n", p.signe, p.theme, p.reponseTheme);
    }
    else
	{
		printf("\nl ouverture du fichier c'est mal passe!");
	}
    fclose(fic);
}

void supprimer_reponse_theme(char *recsigne, char *rectheme)
{
	FILE *fic=NULL;
	REPONSE p;
	fic=fopen("reponse.dat","rb");
	fseek(fic, 0, SEEK_SET);
	FILE *temp=NULL;
	temp=fopen("reponse_tmp.dat","wb+");
	
        while (fread(&p, sizeof(REPONSE), 1, fic))
        if ((strcmp(p.signe,recsigne)==0)&&(strcmp(p.theme,rectheme)==0))
	{
                printf("\neffacement confirme\n");
	}
        else
        {
                fwrite(&p, 1 , sizeof(REPONSE) , temp);
                
         }

    	fclose(fic);
    	fclose(temp);
	remove("reponse.dat");
	rename("reponse_tmp.dat", "reponse.dat");
}

void saisir_nouveau_motcle_theme()
{
	FILE *mot=NULL;
	int choix = 0;
	char nouveau[100];
	int fin=0;
	do
	{
		printf("\nMenu choix du theme:\n");
		printf("1-Sante\n");
		printf("2-Amour\n");
		printf("3-Travail\n");
		printf("Votre choix : ");
		scanf("%d", &choix);
		getchar();
	}
	while (choix < 1 || choix > 3);

	switch (choix)
		{
			case 1 :    	mot=fopen("sante.txt","a+");
    					fseek(mot, 0, SEEK_END);
    					if(mot != NULL)
                        {
							do
							{
                                printf("Mot à ajouter au theme choisi (tapez: fin pour arreter) \n");
								scanf("%s",nouveau);
								if (strcmp(nouveau,"fin")==0)
									fin=1;
								else
								{
                                    fprintf(mot,"\n%s", nouveau);
								}
							}while(fin!=1);
						}
    					else
                        {
                            printf("\nl ouverture du fichier c'est mal passe!");
                        }
                        fclose(mot);
				 	break;

			case 2 :    mot=fopen("amour.txt","a+");
    					fseek(mot, 0, SEEK_END);
    					if(mot != NULL)
                        {
							do
							{
                                printf("Mot à ajouter au theme choisi (tapez: fin pour arreter) \n");
								scanf("%s",nouveau);
								if (strcmp(nouveau,"fin")==0)
									fin=1;
								else
								{
                                    fprintf(mot,"\n%s", nouveau);
								}
							}while(fin!=1);
						}
    					else
                        {
                            printf("\nl ouverture du fichier c'est mal passe!");
                        }
                        fclose(mot);
				 	break;
			case 3 :    mot=fopen("travail.txt","a+");
    					fseek(mot, 0, SEEK_END);
                        int fin=0;
    					if(mot != NULL)
                        {
							do
							{
                                printf("Mot à ajouter au theme choisi (tapez: fin pour arreter) \n");
								scanf("%s",nouveau);
								if (strcmp(nouveau,"fin")==0)
									fin=1;
								else
								{
                                    fprintf(mot,"\n%s", nouveau);
								}
							}while(fin!=1);
						}
    					else
                        {
                            printf("\nl ouverture du fichier c'est mal passe!");
                        }
                        fclose(mot);
                    break;

			default : break;
		}
}

void effacer_motcle_theme()
{
	FILE *mot=NULL;
	int choix = 0;
	char asupprimer[100];
	char fichier[100];
	FILE *temp=NULL;

	do
	{
		printf("\nMenu choix du theme:\n");
		printf("1-Sante\n");
		printf("2-Amour\n");
		printf("3-Travail\n");
		printf("Votre choix : ");
		scanf("%d", &choix);
		getchar();
	}
	while (choix < 1 || choix > 3);

	switch (choix)
		{
			case 1 :    mot=fopen("sante.txt","r");
                        fseek(mot, 0, SEEK_SET);
                        temp=fopen("sante_tmp.txt","w+");
                        printf("Mot a supprimer du theme choisi \n");
                        scanf("%s",asupprimer);

                        while (fscanf(mot,"%s",fichier) !=EOF)
                        {
                            if (strcmp(fichier,asupprimer)!=0)
                            {
                                fprintf(temp,"\n%s", fichier);
                            }
                            else
                            {
                                printf("\neffacement confirme\n");
                            }
                        }
                        fclose(mot);
    					fclose(temp);
                        remove("sante.txt");
                        rename("sante_tmp.txt", "sante.txt");
                        remove("sante_tmp.txt.txt");
					break;

			case 2 :    mot=fopen("amour.txt","r");
                        fseek(mot, 0, SEEK_SET);
                        temp=fopen("amour_tmp.txt","w+");
                        printf("Mot a supprimer du theme choisi \n");
                        scanf("%s",asupprimer);

                        while (fscanf(mot,"%s",fichier) !=EOF)
                        {
                            if (strcmp(fichier,asupprimer)!=0)
                            {
                            fprintf(temp,"\n%s", fichier);
                            }
                            else
                            {
                                printf("\neffacement confirme\n");
                            }
                        }
                        fclose(mot);
    					fclose(temp);
                        remove("amour.txt");
                        rename("amour_tmp.txt", "amour.txt");
                        remove("amour_tmp.txt.txt");
					break;

			case 3 :    mot=fopen("travail.txt","r");
                        fseek(mot, 0, SEEK_SET);
                        temp=fopen("travail_tmp.txt","w+");
                        printf("Mot a supprimer du theme choisi \n");
                        scanf("%s",asupprimer);

                        while (fscanf(mot,"%s",fichier) !=EOF)
                        {
                            if (strcmp(fichier,asupprimer)!=0)
                            {
                            fprintf(temp,"\n%s", fichier);
                            }
                            else
                            {
                            printf("\neffacement confirme\n");
                            }
                        }
                        	fclose(mot);
    				fclose(temp);
                        	remove("travail.txt");
                        	rename("travail_tmp.txt", "travail.txt");
                        	remove("travail_tmp.txt.txt");
				break;
			default : break;
		}
}

void listing_motcle_theme()
{
	FILE *mot=NULL;
	int choix = 0;
	char fichier[100];

	do
	{
		printf("\nMenu choix du theme:\n");
		printf("1-Sante\n");
		printf("2-Amour\n");
		printf("3-Travail\n");
		printf("Votre choix : ");
		scanf("%d", &choix);
		getchar();
	}
	while (choix < 1 || choix > 3);

	switch (choix)
		{
			case 1 :    mot=fopen("sante.txt","r");
                        if(mot != NULL)
                        {
                            fseek(mot, 0, SEEK_SET);
                            while (fscanf(mot,"%s", fichier) !=EOF)
                            {
                                printf("\nMots cle du theme sante: %s", fichier);
                            }
                        }
                        fclose(mot);
                        printf("\n");
					break;

			case 2 :    mot=fopen("amour.txt","r");
                        if(mot != NULL)
    					{
                            fseek(mot, 0, SEEK_SET);
                            while (fscanf(mot,"%s", fichier) !=EOF)
                            {
                            printf("\nMots cle du theme amour: %s", fichier);
                            }
                        }
                        fclose(mot);
                        printf("\n");
					break;

			case 3 :    mot=fopen("travail.txt","r");
                        if(mot != NULL)
    					{
                            fseek(mot, 0, SEEK_SET);
                            while (fscanf(mot,"%s", fichier) !=EOF)
                            {
                                printf("\nMots cle du theme travail: %s", fichier);
                            }
                        }
                        fclose(mot);
                        printf("\n");
					break;
			default : break;
		}
}


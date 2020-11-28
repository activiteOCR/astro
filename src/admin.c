/* Fichier source gestion admin */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/main.h"
#include "../inc/admin.h"

void listing_client(FILE *rep)
{
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
}

void saisir_nouveau_client(FILE *rep)
{
    CLIENT p;

	rep=fopen("bdd_client.txt","a+");

    if(rep != NULL)
    {
        printf("Saisissez un mail \n");
        scanf("%s",p.mail);
        printf("Saisissez un signe du zodiaque \n");
        scanf("%s",p.signe);
        printf("Saisissez un decan (1er, 2ieme, 3ieme)\n");
        scanf("%s",p.decan);
	    printf("Saisissez s'il y a un abonnement (Oui/Non)\n");
        scanf("%s",p.abonnement);
        fprintf(rep,"\n%s %s %s %s", p.mail, p.signe, p.decan, p.abonnement);
    }
    else
	{
		printf("\nl ouverture du fichier c'est mal passe!");
	}
	fclose(rep);
}

int rechercher_client (FILE *rep, char *nomrech)
{
	int trouve=0;
	CLIENT p;

	rep=fopen("bdd_client.txt","r");

	fseek(rep, 0, SEEK_SET);
	while (fscanf(rep,"%s %s %s %s", p.mail, p.signe, p.decan, p.abonnement) !=EOF)
		{
            if (strcmp(p.mail,nomrech)==0)
			{
				printf("\nAffichage de la structure: Mail=%s, Signe=%s, Decan=%s, Abonnement=%s", p.mail, p.signe, p.decan, p.abonnement);
				trouve=strlen(p.abonnement); //determine la taille de la chaine de caractere num_temp pour la retourner et connaitre le nombre d'octect pour se deplacer
				return trouve;
			}
			else
			{
				printf("\nLa personne n existe pas");
			}
		}
		fclose(rep);
		return trouve;
}

void modifier_client(FILE *rep, char *nomrech)
{
	int trouve=0;
    CLIENT p;

	trouve=rechercher_client(rep,nomrech);
	rep=fopen("bdd_client.txt","r+");
	if (trouve!=0)
	{
        fseek(rep, -1*trouve, SEEK_CUR);
		printf("\nSaisir le nouvel abonnement (Oui/Non)\n");
		scanf("%s", p.abonnement);
        fprintf(rep,"%s",p.abonnement);

        listing_client(rep);
	}
	else
	{
		printf("\nLa personne n existe pas");
	}
	fclose(rep);
}

void saisie_mot_cle(FILE *fic, REPONSE *p)
{

    fic=fopen("reponse.dat","ab");

    if (fic==NULL)
	{
		printf("impossible d'ouvrir le fichier en lecture\n");
		exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
        /*fic=fopen("reponse.dat","w+b");
		if (fic==NULL)
		{
			printf("impossible d'ouvrir le fichier en ecriture\n");
			exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
		}*/
	}

    if(fic != NULL)
    {
			printf("Saisissez un signe\n");
			scanf("%s",p->signe);
            fflush(stdin);
            /* Remove trailing newline, if there. */
            if ((strlen(p->signe) > 0) && (p->signe[strlen (p->signe) - 1] == '\n'))
                p->signe[strlen (p->signe) - 1] = '\0';

			printf("Saisissez un theme\n");
			scanf("%s",p->theme);
			if ((strlen(p->theme) > 0) && (p->theme[strlen (p->theme) - 1] == '\n'))
                p->theme[strlen (p->theme) - 1] = '\0';

			printf("Saisissez la reponse theme\n");
			fgetc(stdin);
			fgets(p->reponseTheme, sizeof(p->reponseTheme), stdin);
            if ((strlen(p->reponseTheme) > 0) && (p->reponseTheme[strlen (p->reponseTheme) - 1] == '\n'))
                p->reponseTheme[strlen (p->reponseTheme) - 1] = '\0';

			printf("Saisissez un decan\n");
			scanf("%s",p->decan);
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

void afficher_mot_cle(FILE *fic)
{
	REPONSE p;

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
            printf("\nAffichage de la structure: signe=%s, theme=%s, reponse theme=%s, decan=%s,reponse decan=%s", p.signe, p.theme, p.reponseTheme, p.decan, p.reponseDecan);
    }
    else
	{
		printf("\nl ouverture du fichier c'est mal passe!");
	}
    fclose(fic);
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/*
    Exemple:
    char nom[10];
    printf("Quel est votre nom ? ");
    lire(nom, 10);
    printf("Ah ! Vous vous appelez donc %s !\n\n", nom);
*/

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

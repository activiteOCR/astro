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
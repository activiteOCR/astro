/* Fichier source gestion user */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/main.h"
#include "../inc/admin.h"
#include "../inc/user.h"

# define TMAX 1500

void rechercher_theme_signe(char *answer,char *recsigne,char *rectheme) // modifie pour fonction retour reponse
{
	FILE *fic=NULL;
	REPONSE r;
	fic=fopen("reponse.dat","rb");
	int verif=0;
    if (fic==NULL)
	{
		printf("impossible d'ouvrir le fichier en lecture\n");
		exit(EXIT_FAILURE); // equivalent a return EXIT_FAILURE;
	}


	fseek(fic, 0, SEEK_SET);

    	if(fic != NULL)
    	{
        	while (fread(&r, sizeof(REPONSE), 1, fic))
        	if ((strcmp(r.signe,recsigne)==0)&&(strcmp(r.theme,rectheme)==0))
			{
				printf("\nAffichage de la structure: signe=%s, theme=%s, \nreponse theme=%s, \ndecan=%s,\nreponse decan=%s", r.signe, r.theme, r.reponseTheme, r.decan, r.reponseDecan);
				verif=strlen(r.signe);
				strncpy(answer,r.reponseTheme,3000);
			}
		if (verif==0)
			{
				printf("\nla recherche n a pas aboutie!\n");
    		}
    	}
    	else
	{
		printf("\nl ouverture du fichier c'est mal passe!");
	}
    	fclose(fic);
}

void ecriture_email(EMAIL *q,char *reponse) // Fonction d'envoi d'email et enregistrement log
{

	// fonction de réponse et sotckage dans le Log.txt des emails envoyés
	time_t now; //pour enregistrement de la date de reception de l'email dans le log
	time(&now);
	FILE *log=NULL;

	log=fopen("log.txt","a+");

	// system("cls"); // Pour terminal windows
	// system("clear"); pour terminal systeme linux

	printf("\n-----------------------------------------------");
	printf("\nFrom : madame.soleil@horoscope.fr");
	printf("\nto : %s",q->adress_EM);
	printf("\nSujet : Re : %s",q->OBJ);
	printf("\n%s",reponse);
	if (log !=NULL)
	{
		fprintf(log,"\n Date d envoi : %s|Destinataire: %s\n|Objet: Re: %s\n|Contenu: %s\n",ctime(&now),q->adress_DEST,q->OBJ,reponse);
		// sans Email emetteur car on n'en a pas besoin ;)
	}
	fclose(log);
}


int calc_signe(int m, int j,char *zodiaque,size_t longzod) // Fonction de recherche de signa astrologique et de decan fct date
{
	int decan=0;

	if ((m==1 && j<21) || (m==12 && j>20))
		strncpy(zodiaque, "capricorne", longzod);
	if ((m==2 && j<20) || (m==1 && j>=20))
		strncpy(zodiaque, "verseau", longzod);
	if ((m==3 && j<21) || (m==2 && j>=19))
		strncpy(zodiaque, "poisson", longzod);
	if ((m==4 && j<21) || (m==3 && j>=20))
		strncpy(zodiaque, "belier", longzod);
	if ((m==5 && j<21) || (m==4 && j>=20))
		strncpy(zodiaque, "taureau", longzod);
	if ((m==6 && j<22) || (m==5 && j>=20))
		strncpy(zodiaque, "gemaux", longzod);
	if ((m==7 && j<24) || (m==6 && j>=21))
		strncpy(zodiaque, "cancer", longzod);
	if ((m==8 && j<24) || (m==7 && j>=23))
		strncpy(zodiaque, "lion", longzod);
	if ((m==9 && j<24) || (m==8 && j>=23))
		strncpy(zodiaque, "vierge", longzod);
	if ((m==10 && j<24) || (m==9 && j>=23))
		strncpy(zodiaque, "balance", longzod);
	if ((m==11 && j<23) || (m==10 && j>=23))
		strncpy(zodiaque, "scorpion", longzod);
	if ((m==12 && j<21) || (m==11 && j>=22))
		strncpy(zodiaque, "sagittaire", longzod);

	// calcul du decan (simplifié)

	if (j>=21) decan=1;
		else if (j>=11) decan=3;
			else decan=2;

	return decan;

}


void saisie_email(EMAIL *q) // Fonction de saisie de l'email et enregistrement Log
{
	// Saisie de l'email et stockage dans le Log.txt les emails recus
	time_t now; //pour enregistrement de la date de reception de l'email dans le log
	time(&now);
	FILE *log=NULL;

	log=fopen ("log.txt","a+");
	fflush(stdin);
	viderBuffer();
	printf("Saisissez l'email de l'EMetteur \n");
	lire(q->adress_EM,sizeof(q->adress_EM));
	printf("Saisissez l'email du DEstinataire \n");;
	lire(q->adress_DEST,sizeof(q->adress_DEST));
	printf("Saisissez l'OBJet de l'email\n");
	lire(q->OBJ,sizeof(q->OBJ));
	printf("Saisissez le CORPS de l'email\n");
	lire(q->CORPS,sizeof(q->CORPS));

	if (log !=NULL)
	{
		fprintf(log,"\n Date de reception : %s|Emetteur: %s\n|Objet: %s\n|Contenu: %s\n",ctime(&now),q->adress_EM,q->OBJ,q->CORPS);
		// sans Email destinataire car on n'en a pas besoin ;)
	}
	fclose(log);
}


int rec_cle_amour(EMAIL *q) // Fonction de recherche de mots cle pour trouver le thème amour
{
	FILE *cle=NULL;
	int theme=0;
	char temp[TMAX]; // chaine temporaire pour stocker les mots cles
	char *retour;
	// ouverture du fichier de mots cles amour

	cle=fopen("amour.txt","r");
    if (cle==NULL)
		{
        printf("\nPb d'ouverture du fichier amour.txt");
		}

	while (fscanf(cle,"%s", temp) !=EOF) //lit chaque mot du fichier de cle et le stock dans temp
		{
			// utilisation de strstr vs strcmp pour rechercher dans la totalité du texte de la structure
			retour = strstr(q->OBJ,temp);
			if (retour==NULL)
				retour=strstr(q->CORPS,temp); // Si pas de theme trouve dans OBJ on cheche dans CORPS
			if (retour!= NULL) //recherche dans objet du MAIL et compare a chaque temp du fichier mot cle
			{
				theme=1;
				printf("\ntheme trouve : amour");
				printf("\nmot cle : = %s", temp);
				return theme;
			}
		}
	fclose(cle);
	return theme;
}

int rec_cle_sante(EMAIL *q) // Fonction de recherche de mots cle pour trouver le thème sante
{
	FILE *cle=NULL;
	int theme=0;
	char temp[TMAX]; // chaine temporaire pour stocker les mots cles
	char *retour;
	// ouverture du fichier de mots cles sante
	cle=fopen("sante.txt","r");
    if (cle==NULL)
		{
        printf("\nPb d'ouverture du fichier sante.txt");
		}

	while (fscanf(cle,"%s", temp) !=EOF) //lit chaque mot du fichier de cle et le stock dans temp
		{
			// utilisation de strstr vs strcmp pour rechercher dans la totalité du texte de la structure
			retour = strstr(q->OBJ,temp);
			if (retour==NULL)
				retour=strstr(q->CORPS,temp); // Si pas de theme trouve dans OBJ on cheche dans CORPS
			if (retour!= NULL) //recherche dans objet du MAIL et compare a chaque temp du fichier mot cle
			{
				theme=1;
				printf("\ntheme trouve : sante");
				printf("\nmot cle : =%s", temp);
				return theme;
			}
		}
	fclose(cle);
	return theme;
}

int rec_cle_travail(EMAIL *q) // Fonction de recherche de mots cle pour trouver le thème travail
{
	FILE *cle=NULL;
	int theme=0;
	char temp[TMAX]; // chaine temporaire pour stocker les mots cles
	char *retour;
	// ouverture du fichier de mots cles travail
	cle=fopen("travail.txt","r");
    if (cle==NULL)
		{
        printf("\nPb d'ouverture du fichier travail.txt");
		}

	while (fscanf(cle,"%s", temp) !=EOF) //lit chaque mot du fichier de cle et le stock dans temp
		{
			// utilisation de strstr vs strcmp pour rechercher dans la totalité du texte de la structure
			retour = strstr(q->OBJ,temp);
			if (retour==NULL)
				retour=strstr(q->CORPS,temp); // Si pas de theme trouve dans OBJ on cheche dans CORPS
			if (retour!= NULL) //recherche dans objet du MAIL et compare a chaque temp du fichier mot cle
			{
				theme=1;
				printf("\ntheme trouve : travail");
				printf("\nmot cle : =%s", temp);
				return theme;
			}
		}
	fclose(cle);
	return theme;
}

int rec_mois(EMAIL *q) // OK mais Pb si mise de l'année il y a risque de confusion
{
	int mois=0;

    if (strstr(q->OBJ,"janvier")!=NULL || strstr(q->CORPS,"janvier")!=NULL || strstr(q->OBJ,"/01")!=NULL || strstr(q->CORPS,"/01")!=NULL)
		mois=1;
    if (strstr(q->OBJ,"fevrier")!=NULL || strstr(q->CORPS,"fevrier")!=NULL || strstr(q->OBJ,"/02")!=NULL || strstr(q->CORPS,"/02")!=NULL)
		mois=2;
    if (strstr(q->OBJ,"mars")!=NULL || strstr(q->CORPS,"mars")!=NULL || strstr(q->OBJ,"/03")!=NULL || strstr(q->CORPS,"/03")!=NULL)
		mois=3;
    if (strstr(q->OBJ,"avril")!=NULL || strstr(q->CORPS,"avril")!=NULL || strstr(q->OBJ,"/04")!=NULL || strstr(q->CORPS,"/04")!=NULL)
		mois=4;
    if (strstr(q->OBJ,"mai")!=NULL  || strstr(q->CORPS,"mai")!=NULL || strstr(q->OBJ,"/05")!=NULL || strstr(q->CORPS,"/05")!=NULL)
		mois=5;
    if (strstr(q->OBJ,"juin")!=NULL  || strstr(q->CORPS,"juin")!=NULL || strstr(q->OBJ,"/06")!=NULL || strstr(q->CORPS,"/06")!=NULL)
		mois=6;
    if (strstr(q->OBJ,"juillet")!=NULL  || strstr(q->CORPS,"juillet")!=NULL || strstr(q->OBJ,"/07")!=NULL || strstr(q->CORPS,"/07")!=NULL)
		mois=7;
    if (strstr(q->OBJ,"aout")!=NULL || strstr(q->CORPS,"aout")!=NULL || strstr(q->OBJ,"/08")!=NULL || strstr(q->CORPS,"/08")!=NULL)
		mois=8;
    if (strstr(q->OBJ,"septembre")!=NULL  || strstr(q->CORPS,"septembre")!=NULL || strstr(q->OBJ,"/09")!=NULL || strstr(q->CORPS,"/09")!=NULL)
		mois=9;
    if (strstr(q->OBJ,"octobre")!=NULL  || strstr(q->CORPS,"octobre")!=NULL || strstr(q->OBJ,"/10")!=NULL || strstr(q->CORPS,"/10")!=NULL)
		mois=10;
    if (strstr(q->OBJ,"novembre")!=NULL  || strstr(q->CORPS,"novembre")!=NULL || strstr(q->OBJ,"/11")!=NULL || strstr(q->CORPS,"/11")!=NULL)
		mois=11;
    if (strstr(q->OBJ,"decembre")!=NULL  || strstr(q->CORPS,"decembre")!=NULL || strstr(q->OBJ,"/12")!=NULL || strstr(q->CORPS,"/12")!=NULL)
		mois=12;

	return mois;
}

int rec_jour(EMAIL *q) // OK mais Pb si mise de l'année il y a risque de confusion
{
	int jour=0;

    if (strstr(q->OBJ,"01 ")!=NULL || strstr(q->CORPS,"1 ")!=NULL || strstr(q->OBJ,"01/")!=NULL || strstr(q->CORPS,"01/")!=NULL)
		jour=1;
    if (strstr(q->OBJ,"02 ")!=NULL || strstr(q->CORPS,"2 ")!=NULL || strstr(q->OBJ,"02/")!=NULL || strstr(q->CORPS,"02/")!=NULL)
		jour=2;
    if (strstr(q->OBJ,"03 ")!=NULL || strstr(q->CORPS,"3 ")!=NULL || strstr(q->OBJ,"03/")!=NULL || strstr(q->CORPS,"03/")!=NULL)
		jour=3;
    if (strstr(q->OBJ,"04 ")!=NULL || strstr(q->CORPS,"4 ")!=NULL || strstr(q->OBJ,"04/")!=NULL || strstr(q->CORPS,"04/")!=NULL)
		jour=4;
    if (strstr(q->OBJ,"05 ")!=NULL || strstr(q->CORPS,"5 ")!=NULL || strstr(q->OBJ,"05/")!=NULL || strstr(q->CORPS,"05/")!=NULL)
		jour=5;
    if (strstr(q->OBJ,"06 ")!=NULL || strstr(q->CORPS,"6 ")!=NULL || strstr(q->OBJ,"06/")!=NULL || strstr(q->CORPS,"06/")!=NULL)
		jour=6;
    if (strstr(q->OBJ,"07 ")!=NULL || strstr(q->CORPS,"7 ")!=NULL || strstr(q->OBJ,"07/")!=NULL || strstr(q->CORPS,"07/")!=NULL)
		jour=7;
    if (strstr(q->OBJ,"08 ")!=NULL || strstr(q->CORPS,"8 ")!=NULL || strstr(q->OBJ,"08/")!=NULL || strstr(q->CORPS,"08/")!=NULL)
		jour=8;
    if (strstr(q->OBJ,"09 ")!=NULL || strstr(q->CORPS,"9 ")!=NULL || strstr(q->OBJ,"09/")!=NULL || strstr(q->CORPS,"09/")!=NULL)
		jour=9;
    if (strstr(q->OBJ,"10 ")!=NULL || strstr(q->CORPS,"10 ")!=NULL || strstr(q->OBJ,"10/")!=NULL || strstr(q->CORPS,"10/")!=NULL)
		jour=10;
    if (strstr(q->OBJ,"11 ")!=NULL || strstr(q->CORPS,"11 ")!=NULL || strstr(q->OBJ,"11/")!=NULL || strstr(q->CORPS,"11/")!=NULL)
		jour=11;
    if (strstr(q->OBJ,"12 ")!=NULL || strstr(q->CORPS,"12 ")!=NULL || strstr(q->OBJ,"12/")!=NULL || strstr(q->CORPS,"12/")!=NULL)
		jour=12;
    if (strstr(q->OBJ,"13 ")!=NULL || strstr(q->CORPS,"13 ")!=NULL || strstr(q->OBJ,"13/")!=NULL || strstr(q->CORPS,"13/")!=NULL)
		jour=13;
    if (strstr(q->OBJ,"14 ")!=NULL || strstr(q->CORPS,"14 ")!=NULL || strstr(q->OBJ,"14/")!=NULL || strstr(q->CORPS,"14/")!=NULL)
		jour=14;
    if (strstr(q->OBJ,"15 ")!=NULL || strstr(q->CORPS,"15 ")!=NULL || strstr(q->OBJ,"15/")!=NULL || strstr(q->CORPS,"15/")!=NULL)
		jour=15;
    if (strstr(q->OBJ,"16 ")!=NULL || strstr(q->CORPS,"16 ")!=NULL || strstr(q->OBJ,"16/")!=NULL || strstr(q->CORPS,"16/")!=NULL)
		jour=16;
    if (strstr(q->OBJ,"17 ")!=NULL || strstr(q->CORPS,"17 ")!=NULL || strstr(q->OBJ,"17/")!=NULL || strstr(q->CORPS,"17/")!=NULL)
		jour=17;
    if (strstr(q->OBJ,"18 ")!=NULL || strstr(q->CORPS,"18 ")!=NULL || strstr(q->OBJ,"18/")!=NULL || strstr(q->CORPS,"18/")!=NULL)
		jour=18;
    if (strstr(q->OBJ,"19 ")!=NULL || strstr(q->CORPS,"19 ")!=NULL || strstr(q->OBJ,"19/")!=NULL || strstr(q->CORPS,"19/")!=NULL)
		jour=19;
    if (strstr(q->OBJ,"20 ")!=NULL || strstr(q->CORPS,"20 ")!=NULL || strstr(q->OBJ,"20/")!=NULL || strstr(q->CORPS,"20/")!=NULL)
		jour=20;
    if (strstr(q->OBJ,"21 ")!=NULL || strstr(q->CORPS,"21 ")!=NULL || strstr(q->OBJ,"21/")!=NULL || strstr(q->CORPS,"21/")!=NULL)
		jour=21;
    if (strstr(q->OBJ,"22 ")!=NULL || strstr(q->CORPS,"22 ")!=NULL || strstr(q->OBJ,"22/")!=NULL || strstr(q->CORPS,"22/")!=NULL)
		jour=22;
    if (strstr(q->OBJ,"23 ")!=NULL || strstr(q->CORPS,"23 ")!=NULL || strstr(q->OBJ,"23/")!=NULL || strstr(q->CORPS,"23/")!=NULL)
		jour=23;
    if (strstr(q->OBJ,"24 ")!=NULL || strstr(q->CORPS,"24 ")!=NULL || strstr(q->OBJ,"24/")!=NULL || strstr(q->CORPS,"24/")!=NULL)
		jour=24;
    if (strstr(q->OBJ,"25 ")!=NULL || strstr(q->CORPS,"25 ")!=NULL || strstr(q->OBJ,"25/")!=NULL || strstr(q->CORPS,"25/")!=NULL)
		jour=25;
    if (strstr(q->OBJ,"26 ")!=NULL || strstr(q->CORPS,"26 ")!=NULL || strstr(q->OBJ,"26/")!=NULL || strstr(q->CORPS,"26/")!=NULL)
		jour=26;
    if (strstr(q->OBJ,"27 ")!=NULL || strstr(q->CORPS,"27 ")!=NULL || strstr(q->OBJ,"27/")!=NULL || strstr(q->CORPS,"27/")!=NULL)
		jour=27;
    if (strstr(q->OBJ,"28 ")!=NULL || strstr(q->CORPS,"28 ")!=NULL || strstr(q->OBJ,"28/")!=NULL || strstr(q->CORPS,"28/")!=NULL)
		jour=28;
    if (strstr(q->OBJ,"29 ")!=NULL || strstr(q->CORPS,"29 ")!=NULL || strstr(q->OBJ,"29/")!=NULL || strstr(q->CORPS,"29/")!=NULL)
		jour=29;
    if (strstr(q->OBJ,"30 ")!=NULL || strstr(q->CORPS,"30 ")!=NULL || strstr(q->OBJ,"30/")!=NULL || strstr(q->CORPS,"30/")!=NULL)
		jour=30;
    if (strstr(q->OBJ,"31 ")!=NULL || strstr(q->CORPS,"31 ")!=NULL || strstr(q->OBJ,"31/")!=NULL || strstr(q->CORPS,"31/")!=NULL)
		jour=31;

	return jour;
}

void rec_signe(char *zodiaque,size_t longzod,EMAIL *q) // Fonction de recherche du signe du zodiaque
{

    if (strstr(q->OBJ,"belier")!=NULL || strstr(q->CORPS,"belier")!=NULL)
		strncpy(zodiaque, "belier", longzod);
    if (strstr(q->OBJ,"taureau")!=NULL || strstr(q->CORPS,"taureau")!=NULL)
		strncpy(zodiaque, "taureau", longzod);
    if (strstr(q->OBJ,"gemeaux")!=NULL || strstr(q->CORPS,"gemeaux")!=NULL)
		strncpy(zodiaque, "gemeaux", longzod);
    if (strstr(q->OBJ,"cancer")!=NULL || strstr(q->CORPS,"cancer")!=NULL)
		strncpy(zodiaque, "cancer", longzod);
    if (strstr(q->OBJ,"lion")!=NULL  || strstr(q->CORPS,"lion")!=NULL)
		strncpy(zodiaque, "lion", longzod);
    if (strstr(q->OBJ,"vierge")!=NULL  || strstr(q->CORPS,"vierge")!=NULL)
		strncpy(zodiaque, "vierge", longzod);
    if (strstr(q->OBJ,"balance")!=NULL  || strstr(q->CORPS,"balance")!=NULL)
		strncpy(zodiaque, "balance", longzod);
    if (strstr(q->OBJ,"scorpion")!=NULL || strstr(q->CORPS,"scorpion")!=NULL)
		strncpy(zodiaque, "scorpion", longzod);
    if (strstr(q->OBJ,"sagittaire")!=NULL  || strstr(q->CORPS,"sagittaire")!=NULL)
		strncpy(zodiaque, "sagittaire", longzod);
    if (strstr(q->OBJ,"capricorne")!=NULL  || strstr(q->CORPS,"capricorne")!=NULL)
		strncpy(zodiaque, "capricorne", longzod);
    if (strstr(q->OBJ,"verseau")!=NULL  || strstr(q->CORPS,"verseau")!=NULL)
		strncpy(zodiaque, "verseau", longzod);
    if (strstr(q->OBJ,"poisson")!=NULL  || strstr(q->CORPS,"poisson")!=NULL)
		strncpy(zodiaque, "poisson", longzod);
}

void viderBuffer() // Pour sécurisation fgets de la fonction lire si saisie trop longue ou si Pb de saisie
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur) // Fonction pour palier au Pb de Retour Chariot de fgets et pour que la recherche de mot cle fonctionne
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

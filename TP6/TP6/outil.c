#include <stdio.h>   /* pour les entr�es-sorties */
#include <string.h>  /* pour les manipulations de cha�nes de caract�res */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compl�ter votre nom ici                                                */
/*   Nom : BERGERAULT                    Pr�nom : FOUCAULD                          */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le r�pertoire stock� en m�moire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compl�ter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		*(rep->tab + rep->nb_elts) = enr;
		rep->nb_elts += 1;
		rep->est_trie = false;

	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
			//
			// compl�ter code ici pour Liste
			//
			//
			//

	}


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du r�pertoire l'enregistrement dont l'indice est donn� en */
  /*   param�tre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compl�ter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{	
		if (indice > -1 && indice < rep->nb_elts) {    /* et que l'indice pointe a l'interieur */
			for (int i = indice; i < rep->nb_elts - 1;i++) {
				*(rep->tab + i) = *(rep->tab + i + 1); 
			}
			rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
			modif = true;
			return;
		}
	}
	modif = false;

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du r�pertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif � vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne � l'�cran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	

	printf("%s  %s  %s", enr.nom, enr.prenom, enr.tel);

	// code � compl�ter ici


} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code � compl�ter ici
	// comme fonction affichage_enreg, mais avec pr�sentation align�es des infos
	/*printf("| %c", enr.nom);
	printf("                                           | %c |", enr.tel);
	printf("_____________________________________________________________________________________________");*/

	
	int nbespace = 0;
	printf("| %s", enr.nom);
	nbespace = MAX_NOM - strlen(enr.nom);
	for (int j = 0; j < nbespace; j++) {
		printf(" ");
	}
	printf("| %s", enr.prenom);
	nbespace = MAX_NOM - strlen(enr.prenom);
	for (int j = 0; j < nbespace; j++) {
		printf(" ");
	}
	printf("| %s", enr.tel);
	printf("\n");

	

} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	if (strcmp(enr1.nom, enr2.nom) == 0) {// cas ou les nom sont identiques
		if (strcmp(enr1.prenom, enr2.prenom) == 0) { // cas ou les prenoms sont �galement identique
			return(true);// vrai car deux prenom identique sont dans l'ordre alphab�tique
		}
		else if (strcmp(enr1.prenom, enr2.prenom) < 0) {// Cas ou le prenom 1 et Avant le prenom 2 dans l'ordre alp
			return(true);
		}
		else { // cas ou le prenon 1 est apres le prenom 2 dans l'ordre Alpha
			return(false);
		}
	}
	else if (strcmp(enr1.nom, enr2.nom) < 0) {// cas ou le nom 1 est avant le nom 2 dans l'ordre Alphab
		return(true);
	}
	else {// Cas ou le nom1 est apr�s le Nom 2 dans l'ordre Alphab
		return(false);
	}
		

	// code � compl�ter ici
	//strcmpi() regarder cette fonctio

}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	for (int i = 0; i < rep->nb_elts-1; i++) {
		if (est_sup(*(rep->tab + i), *(rep->tab + i + 1)) == false) {// si tab [i]est apres tab[i+1] dans l'ordre alpha
			Enregistrement transit;
			int j = i,stop=0;
			do {
				transit = *(rep->tab + j);
				*(rep->tab + j) = *(rep->tab + j + 1);
				*(rep->tab + j + 1)= transit;  // on inverse les valeur de tab [i]est apres tab[i+1]
				j--;
				
			} while (est_sup(*(rep->tab + j), *(rep->tab + j + 1)) == false && j<0);//On verifie mnt si tab i-1 et avant tab i+1 dans l'ordre aphap
		}																	// SINON on recomence la boucle pour redecaler i+1 de 1 cran vers la gauche
		//else la boucle continue son chemin
	}


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien � faire !
	// la liste est toujours tri�e
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le r�pertoire d'un enregistrement correspondant au  */
  /*   nom � partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au crit�re ou*/
  /*   un entier n�gatif si la recherche est n�gative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de d�but de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


#ifdef IMPL_TAB
							// ajouter code ici pour tableau
	
#else
#ifdef IMPL_LIST
							// ajouter code ici pour Liste
	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non num�riques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	// compl�ter code ici

	return;
}

/**********************************************************************/
/* sauvegarde le r�pertoire dans le fichier dont le nom est pass� en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionn� ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le r�pertoire le contenu du fichier dont le nom est  */
  /*   pass� en argument                                                */
  /*   retourne OK si le chargement a fonctionn� et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element � priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */
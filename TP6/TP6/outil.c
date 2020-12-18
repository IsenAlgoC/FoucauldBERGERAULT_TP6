#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : BERGERAULT                    Prénom : FOUCAULD                          */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire* rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		*(rep->tab + rep->nb_elts) = enr;
		rep->nb_elts += 1;
		rep->est_trie = false;
		modif = true;

	}
	else {
		return(ERROR);
	}


#else
#ifdef IMPL_LIST

	int i = 0;
	bool inserted = false;
	if (rep->nb_elts == 0) {//Si la liste est vide on creer le premier maillon
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			rep->est_trie = true;
			inserted = true;
}

	}
	else {
		if (rep->nb_elts < MAX_ENREG) {
			SingleLinkedListElem* elem = NULL;
			elem = rep->liste->head;
			while (!inserted && i <= rep->liste->size)
			{
				if (elem == NULL) {
					if (InsertElementAt(rep->liste, i, enr) != 0) {
						rep->nb_elts += 1;
						rep->est_trie = true;
						inserted = true;
					}
				}
				else {
					if (est_sup(enr, elem->pers)) {
						if (InsertElementAt(rep->liste, i, enr) != 0) {
							rep->nb_elts += 1;
							rep->est_trie = true;
							inserted = true;
						}
					}
					elem = elem->next;
				}

				i++;
			}

		}

	}


#endif

#endif


	modif = true;
	if (inserted)  return OK;
	else return ERROR;

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire* rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{
		if (indice > -1 && indice < rep->nb_elts) {    /* et que l'indice pointe a l'interieur */
			for (int i = indice; i < rep->nb_elts - 1; i++) {
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
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

int supprimer_un_contact_dans_rep_liste(Repertoire* rep, SingleLinkedListElem* elem) {

	int ret = DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0);
}
#endif
#endif


/**********************************************************************/
/*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
/* ex Dupont, Jean                 0320304050                         */
/**********************************************************************/
void affichage_enreg(Enregistrement enr)
{


	printf("%s  %s  %s", enr.nom, enr.prenom, enr.tel);

	// code à compléter ici


} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos
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
	if (_strcmpi(enr1.nom, enr2.nom) == 0) {// cas ou les nom sont identiques

		if (_strcmpi(enr1.prenom, enr2.prenom) <= 0) {// Cas ou le prenom 1 et Avant le prenom 2 dans l'ordre alp
			return(true);
		}

	}
	else if (_strcmpi(enr1.nom, enr2.nom) < 0) {// cas ou le nom 1 est avant le nom 2 dans l'ordre Alphab
		return(true);
	}

	return(false);



	// code à compléter ici
	//strcmpi() regarder cette fonctio

}

/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire* rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	for (int i = 0; i < rep->nb_elts - 1; i++) {
		if (est_sup(*(rep->tab + i), *(rep->tab + i + 1)) == false) {// si tab [i]est apres tab[i+1] dans l'ordre alpha
			Enregistrement transit;
			int j = i, stop = 0;
			do {
				transit = *(rep->tab + j);
				*(rep->tab + j) = *(rep->tab + j + 1);
				*(rep->tab + j + 1) = transit;  // on inverse les valeur de tab [i]est apres tab[i+1]

				j--;


			} while (est_sup(*(rep->tab + j), *(rep->tab + j + 1)) == false && j > -1);//On verifie mnt si tab i-1 et avant tab i+1 dans l'ordre aphap
		}																	// SINON on recomence la boucle pour redecaler i+1 de 1 cran vers la gauche
		//else la boucle continue son chemin

	}




#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire* rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin = rep->nb_elts;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;


#ifdef IMPL_TAB
	strcpy_s(tmp_nom, _countof(tmp_nom), nom);//Copie la chaine nom dans tmp_nom
	for (int j = 0; j < rep->nb_elts; j++) {
		strcpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[j].nom);//Copie le nom à la position j du repertoire dans tmp Nom
		if (_strcmpi(tmp_nom, tmp_nom2) == 0) {// Compare le nom dans le rep avec le nom recherche
			trouve = true;
			break;
		}
	}



#else
#ifdef IMPL_LIST
	strcpy_s(tmp_nom, MAX_NOM, nom);//Meme chose qu'avec TABL mais avec une liste
	_strupr_s(tmp_nom, MAX_NOM);
	while (!trouve && i < ind_fin) {
		strcpy_s(tmp_nom2, MAX_NOM, GetElementAt(rep->liste, i)->pers.nom);
		_strupr_s(tmp_nom2, MAX_NOM);
		if (_strcmpi(tmp_nom, tmp_nom2) == 0) trouve = true;
		i++;
	}

#endif
#endif

	return((trouve) ? i : -1); //si trouve = vrai return i sinon -1
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char* s)
{
	int i = 0;
	do {
		if (isdigit(s[i]) < 1) {// test si le caractere est un num , un espace ou un tiret
			int j = i; // Si NON on le supprimer en décalant tous les caracteres qui suivents de un cran vers la gauche
			do {
				s[j] = s[j + 1];
				j++;
			} while (s[j] != '\0');// On décalle jusqu'a rencontrer la fin de la liste

		}
		else {
			i++;// Si le caracter est un num on on continue le parcours de la liste
		}

	} while (s[i] != '\0');


	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;			//le fichier
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w");
	if (fic_rep == NULL|| err!=0) {
		return (ERROR);
	}
	char buffer[sizeof(Enregistrement) + 3];

#ifdef IMPL_TAB



	for (int i = 0; i < rep->nb_elts; i++) {
		sprintf_s(buffer, sizeof(Enregistrement) + 3, "%s%c%s%c%s%s", rep->tab[i].nom, SEPARATEUR, rep->tab[i].prenom, SEPARATEUR, rep->tab[i].tel,"\n");
		fputs(buffer, fic_rep);
	}
	if (feof(fic_rep)) {
		fclose(fic_rep);
	}

#else
#ifdef IMPL_LIST
	if (fopen_s(&fic_rep, nom_fichier, "w+") != 0 || fic_rep == NULL)//Meme chose mais en LISTE
		return ERROR;
	else {
		int i = 0;
		while (i < rep->nb_elts) {
			fprintf(fic_rep, "%s;", GetElementAt(rep->liste, i)->pers.nom);
			fprintf(fic_rep, "%s;", GetElementAt(rep->liste, i)->pers.prenom);
			fprintf(fic_rep, "%s\n", GetElementAt(rep->liste, i)->pers.tel);
			i++;
}


	}
	fclose(fic_rep);
	return 0;
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char* char_nw_line;

	_set_errno(0);
	if (((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL))
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
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
				Enregistrement pers = { {'A'},{'A'},{'0'} };//creation d'un element qui sera rempli par ce qui est dans le fichier texte(ligne par ligne)
				SingleLinkedListElem* elem = NULL;
				InsertElementAt(rep->liste, num_rec, pers);
				elem = GetElementAt(rep->liste, (num_rec));
				if (lire_champ_suivant(buffer, &idx, elem->pers.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, elem->pers.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, elem->pers.tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */
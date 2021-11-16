/// \file liste.c
/// \brief liste statique de priorité (triée à la demande)
/// \author Vincent Dugat
/// \date august 2018
/// \note la liste est circulaire

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "global.h"
#include "elementliste.h"
#include "liste.h"

void createList(liste *p){
/// \brief Création d'une liste
    p->Tete= 0; /// \var < premier élément de la liste
    p->nbElt = 0; /// \var < nombre d'éléments de la liste
}

int nbEltList(liste lst){
  /// \return : le nombre d'éléments de la liste (int)
    return lst.nbElt;
}

void addFrontList(liste *p, Elementliste e){
/// \brief ajoute e en début de liste
  if (fullList(*p)) {
      fprintf(stderr,"addFront : liste pleine !\n");
      exit(1);
  }
  p->Tete = (p->Tete-1) %DIMMAX;
  if (p->Tete<0)
      p->Tete = DIMMAX+p->Tete ;
  copie_element(&(p->Tabliste[p->Tete]),e);
  p->nbElt++;
}

void addTailList(liste *p, Elementliste e){
/// \brief ajoute e en fin de liste
  if (fullList(*p)) {
      fprintf(stderr,"addTailList : liste pleine !\n");
      exit(1);
  }
  copie_element(&(p->Tabliste[(p->Tete+p->nbElt)%DIMMAX]),e);
  p->nbElt++;
}

/* Delister */
void delTailList(liste *p){
    if (emptyList(*p)) {
        /* la liste est vide : erreur */
        fprintf(stderr,"delTail : liste vide !\n");
        exit(1);
    } else {
        /* la liste n'est pas vide */
	p->Tete=p->Tete+1 % DIMMAX; // modulo pour circulaire
  p->nbElt--;
   }
}

void delFrontList(liste *p){
    if (emptyList(*p)) {
        /* la liste est vide : erreur */
        fprintf(stderr,"depiler : liste vide !\n");
        exit(1);
    } else {
        /* la liste n'est pas vide */
  p->nbElt--;
   }
}

void headList(liste p, Elementliste *e){
  /// \brief Récupère le premer élément sans le supprimer (permet de tester)
    if (!emptyList(p))
        *e= p.Tabliste[p.Tete];
    else {
        /* la liste est vide : erreur */
        fprintf(stderr,"sommet : liste vide !\n");
        exit(1);
    }
}

void tailList(liste p, Elementliste *e){
  /// \brief Récupère le premer élément sans le supprimer (permet de tester)
    if (!emptyList(p))
        *e= p.Tabliste[p.Tete+p.nbElt%DIMMAX];
    else {
        /* la liste est vide : erreur */
        fprintf(stderr,"sommet : liste vide !\n");
        exit(1);
    }
}

bool emptyList(liste p) {
/// \brief La liste est-elle vide ?
/// \return true (si vide), false (sinon)
  return (p.nbElt==0);
 }

bool fullList(liste p) {
  /// \brief La liste est-elle pleine ?
  /// \return true (si pleine), false (sinon)
	return (p.nbElt==DIMMAX);
}


/* Affichage de la liste */
void dumpList(liste p,FILE *fp){
  fprintf(fp,"\n(orig, dest, pds)\n");
	for(int ind=p.Tete;ind<p.Tete+p.nbElt%DIMMAX;ind++){
    fprintf(fp,"elt %d=",ind%DIMMAX);
    afficher_element(p.Tabliste[ind%DIMMAX],fp);
    }
}

void swapEltList(Elementliste *a,Elementliste *b)
/// \brief swap
{
    Elementliste aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void bubbleSortList(liste *p){
/// \brief tri à bulle par ordre décroissant d'une liste
/// \param[in] une liste.
/// \param[out] la même liste triée
	int i,j;
	for (i=p->Tete;i<p->Tete+p->nbElt%DIMMAX;i++)
		for(j=i+1;j<p->Tete+p->nbElt%DIMMAX;j++)
			if ((p->Tabliste[i]).poids<(p->Tabliste[j]).poids)
			swapEltList(&(p->Tabliste[i]),&(p->Tabliste[j]));
}

void pickEltList(liste l,Elementliste *e,int index){
  /// \brief renvoie l'élément numéro index
  /// \return : l'élément numéro index
    int nbElt = l.nbElt;
    int indice = l.Tete+index%DIMMAX;
    if (index<0 || index >nbElt){
        printf("erreur d'indice dans la liste\n");
        return;
    }
    *e = l.Tabliste[indice];
}

bool belongEltList(liste p,Elementliste e){
  /// \brief appartenance l'un elt à une liste.
  /// \return : true si e appartient à la liste, false sinon
    for(int ind=p.Tete;ind<p.Tete+p.nbElt%DIMMAX;ind++){
        if (cmp_elements(p.Tabliste[ind],e))
            return true;
    }
    return false;
}

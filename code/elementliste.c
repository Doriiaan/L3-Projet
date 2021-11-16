/// \file elementliste.c
/// \brief liste statique : module de définition des éléments de la liste
/// \author Vincent Dugat

#include <stdio.h>
#include <stdbool.h>
#include "global.h"
#include "elementliste.h"

void afficher_element(Elementliste e,FILE *fp){
  fprintf(fp,"(%d, %d, %d)\n", e.orig,e.dest,e.poids);
}

void saisie_element(Elementliste *e){
    printf("Arc ? (trois entiers séparés par des espaces)");
    scanf("%d", &(e->orig));
    scanf("%d", &(e->dest));
    scanf("%d", &(e->poids));
}

void copie_element(Elementliste *cible, Elementliste source){
/// \param[out] *cible (référence) reçoit l"élémént
/// \param[in] source élément à copier
    cible->orig=source.orig;
    cible->dest=source.dest;
    cible->poids=source.poids;
}

bool cmp_elements(Elementliste e1,Elementliste e2){
/// \param[in] e1 et e2
/// \return true si e1 ==e2, false sinon
    return (e1.orig==e2.orig)&&(e1.dest==e2.dest)&&(e1.poids==e2.poids);
}

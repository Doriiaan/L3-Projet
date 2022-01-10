/**
* @file condorcet_minimax.c
* @brief Fichier contenant les fonctions d'election par methode condorcet minimax \n
* @author ALARY Dorian
* @date Janvier 2022
*/


#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"
#include "fichiers_h/utils_scrutins.h"

/**
* @fn int minimax(t_mat_int_dyn duels_mat, liste larcs, int nbSommets,FILE *outfp)
* @brief renvoie l'indice du vainqueur et affiche les calculs intermediaire dans fichier log si besoin
* @param[out] int indice_vainqueur
*/
int minimax(t_mat_int_dyn duels_mat, liste larcs, int nbSommets,FILE *outfp){

  fprintf(outfp, "\n\n-------------------------------------\n");
  fprintf(outfp, "----------CONDORCET MINIMAX----------\n");
  fprintf(outfp, "-------------------------------------\n");
  int vainqueur_condorcet = vainqueurCondorcet(larcs, nbSommets);

  //si il y a un vainqueur de condorcet sinon on fait la methode minimax
  if(vainqueur_condorcet != -1){
    return vainqueur_condorcet;
  }
  else{

    liste liste_arc_moins_bon;
    createList(&liste_arc_moins_bon);
    Elementliste arc_moins_bon;
    Elementliste arc;
    Elementliste minimax_elem;

    //on ajoute les arcs les moins bon pour chaque sommet dans la liste
    for (int x = 0; x < nbSommets; x++) {
      arc_moins_bon.orig = x;
      arc_moins_bon.dest = 0;
      if(x == 0)
        arc_moins_bon.dest = 1;
      arc_moins_bon.poids = duels_mat.tab[x][arc_moins_bon.dest];
      for (int y = 1; y < nbSommets; y++) {
        if(x != y){
          arc.orig = x;
          arc.dest = y;
          arc.poids = duels_mat.tab[x][y];
          if (arc.poids < arc_moins_bon.poids)
            copie_element(&arc_moins_bon, arc);
        }
      }
      addTailList(&liste_arc_moins_bon, arc_moins_bon);
    }
    // on trie la liste puis on prend l'origine du plus fort
    bubbleSortList(&liste_arc_moins_bon);
    if(outfp != stdout){
      fprintf(outfp, "\n-----GRAPHE DES DUELS MINIMUMS-----\n\n");
      dumpList(liste_arc_moins_bon, outfp);
      fprintf(outfp, "\n");
    }
    headList(liste_arc_moins_bon, &minimax_elem);
    return minimax_elem.orig;
  }
}

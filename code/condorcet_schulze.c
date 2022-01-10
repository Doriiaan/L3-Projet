/**
* @file condorcet_schulze.c
* @brief Fichier contenant les fonctions d'election par methode condorcet schulze \n
* @author ALARY Dorian
* @date Janvier 2022
*/

#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"
#include "fichiers_h/utils_scrutins.h"

/**
* @fn t_tab_int_dyn schulze(t_mat_int_dyn duels_mat, liste larcs, int nbSommets, FILE *outfp)
* @brief renvoie l'ensemble des gagnants potentiels et affiche les calculs intermediaire dans fichier log si besoin
* @param[out] t_tab_int_dyn ensemble_gagnants_potentiels
*/
t_tab_int_dyn schulze(t_mat_int_dyn duels_mat, liste larcs, int nbSommets, FILE *outfp){

  fprintf(outfp, "\n\n-------------------------------------\n");
  fprintf(outfp, "----------CONDORCET SCHULZE----------\n");
  fprintf(outfp, "-------------------------------------\n");
  int vainqueur_condorcet = vainqueurCondorcet(larcs, nbSommets);

  t_tab_int_dyn ensemble_gagnants_potentiels;
  creer_t_tab_int_dyn(&ensemble_gagnants_potentiels, nbSommets);
  init_tab_int(ensemble_gagnants_potentiels.tab, nbSommets, 0);

  if(vainqueur_condorcet != -1){
    ensemble_gagnants_potentiels.tab[vainqueur_condorcet] = 1;
    return ensemble_gagnants_potentiels;
  }
  else{
    t_mat_int_dyn p;
    creer_t_mat_int_dyn(&p, nbSommets, nbSommets);
    creer_mat_force_du_plus_fort_chemin(&p, duels_mat);
    creer_ensemble_gagnants_potentiels(&ensemble_gagnants_potentiels, p);

    if(outfp != stdout){
      fprintf(outfp, "\n----MATRICE DES PLUS FORT CHEMINS-----\n\n");
      affiche_t_mat_int_dyn(p, outfp);
      fprintf(outfp, "\n\n----LISTE GAGANTS POTENTIELS-----\n\n");
      affiche_t_tab_int_dyn(ensemble_gagnants_potentiels, outfp);
      fprintf(outfp, "\n");
    }
    return ensemble_gagnants_potentiels;
  }

}

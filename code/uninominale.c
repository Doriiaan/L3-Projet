#include "fichiers_h/global.h"
#include "fichiers_h/utils_scrutins.h"
#include "fichiers_h/utils.h"

void uninominal_un_tour(t_mat_char_star_dyn tabmots,FILE *outfp){

  int nombreVotant = tabmots.nbRows-1;
  int nombreCandidat = tabmots.nbCol-tabmots.offset;

  // construire le tableau des votes par candidats
  t_tab_int_dyn vote_par_candidat_candidat = creer_vote_par_candidat_candidat(tabmots, nombreCandidat);

  // chercher le nom du vainqueur
  int indice_vainqueur = max_tab_indice(vote_par_candidat_candidat.tab, vote_par_candidat_candidat.dim);
  char nom_vainqueur[LONGMOTS];
  copier_chaine_char(tabmots.tab[0][indice_vainqueur+tabmots.offset], nom_vainqueur);
  printf("%s\n", nom_vainqueur);




}


void uninominal_deux_tours(t_tab_int_dyn first_array,t_mat_int_dyn duels_mat,t_mat_char_star_dyn tabmots,FILE *outfp){

}

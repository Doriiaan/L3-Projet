#include "fichiers_h/global.h"


t_tab_int_dyn creer_vote_par_candidat_candidat(t_mat_char_star_dyn tabmots, int nombreCandidat){

  t_tab_int_dyn candidats_classement;
  creer_t_tab_int_dyn(&candidats_classement, nombreCandidat);
  init_tab_int(candidats_classement.tab, nombreCandidat, 0);

  int minimum_ligne = tabmots.offset;

  for (int i_votant = 1; i_votant < tabmots.nbRows-1; i_votant++) { //1 a la fin (lignes)
    for (int i_candidat = tabmots.offset; i_candidat < tabmots.nbCol; i_candidat++) { //debut des votes jusqua la fin (colonnes)
      if(atoi(tabmots.tab[i_votant][i_candidat]) < atoi(tabmots.tab[i_votant][minimum_ligne]))
        minimum_ligne = i_candidat;
    }
    candidats_classement.tab[minimum_ligne-tabmots.offset]++;
    minimum_ligne = tabmots.offset;
  }
  return candidats_classement;
}


void affiche_resultat(FILE *outfp, char * scrutin, int nbCandidats, int nbVotants , float score, char * vainqueur){

}

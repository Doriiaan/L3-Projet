#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"


/*
struct liste {
    Elementliste Tabliste[DIMMAX];
    int Tete;
    int nbElt;
};

typedef struct s_arc_p{ /// arc pondéré = arc de préférence
  int orig;
  int dest;
  int poids;
} t_arc_p;


*/
int vainqueurCondorcet(liste larcs, int nbSommets){

  int vainqueur = -1;

  int x = larcs.Tabliste[0].orig; //sommet actuel
  int nombre_victoire = 1;

  int i_arc = 1;
  while (i_arc < nbEltList(larcs) && nombre_victoire != nbSommets-1) {
    if(larcs.Tabliste[i_arc].orig == x){
      nombre_victoire++;
    }
    else{
      x = larcs.Tabliste[i_arc].orig;
      nombre_victoire = 1;
    }
    i_arc++;
  }
  if(nombre_victoire == nbSommets-1){
    vainqueur = x;
    return vainqueur;
  }
  return vainqueur;
}


int creer_liste_arc(liste *liste_arc, t_mat_int_dyn duels_mat){

  Elementliste arc;
  Elementliste arc_inverse;
  // x -> y
  for (int x = 0; x < duels_mat.nbRows; x++) {
    for (int y = 0; y < duels_mat.nbCol; y++) {
      if(x != y){
        arc.orig = x;
        arc.dest = y;
        arc.poids = duels_mat.tab[x][y];
        arc_inverse.orig = y;
        arc_inverse.dest = x;
        arc_inverse.poids = duels_mat.tab[y][x];
        if(duels_mat.tab[x][y] >= duels_mat.tab[y][x] && !belongEltList(*liste_arc, arc_inverse)){
          addTailList(liste_arc, arc);
        }
      }
    }
  }
}

void construct_mat_duels_d(t_mat_char_star_dyn tabmots,t_mat_int_dyn *duels_mat,int nbCandidats,FILE *outfp){

  creer_t_mat_int_dyn(duels_mat, nbCandidats, nbCandidats);
  int nombreVotant = tabmots.nbRows-1;
  int somme_vote_x_superieur_y = 0;

  for (size_t x = 0; x < nbCandidats; x++) {
    for (size_t y = 0; y < nbCandidats; y++) {
      if(x != y){
        for (size_t i_ligne = 1; i_ligne < nombreVotant; i_ligne++) {
          if(atoi(tabmots.tab[i_ligne][x + tabmots.offset]) > atoi(tabmots.tab[i_ligne][y + tabmots.offset]))
            somme_vote_x_superieur_y++;
        }
        duels_mat->tab[x][y] = somme_vote_x_superieur_y;
        somme_vote_x_superieur_y = 0;
      }
      else{
        duels_mat->tab[x][y] = 0;
      }
    }
  }
}


t_tab_int_dyn creer_vote_par_candidat(t_mat_char_star_dyn tabmots, int nombreCandidat){

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

  if(comparer_chaine_char(scrutin, "uni1")){
    fprintf(outfp, "Mode de scrutin : uninominale à un tour, %d candidats, %d votants, vainqueur = %s, score = %f%\n", nbCandidats, nbVotants, vainqueur, score);
  }
  if(comparer_chaine_char(scrutin, "uni2 tour1")){
    fprintf(outfp, "Mode de scrutin : uninominale à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %f%\n", nbCandidats, nbVotants, vainqueur, score);
  }
  if(comparer_chaine_char(scrutin, "uni2 tour2")){
    fprintf(outfp, "Mode de scrutin : uninominale à deux tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %f%\n", nbCandidats, nbVotants, vainqueur, score);
  }
}

#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"
#include "fichiers_h/utils_scrutins.h"


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


int creer_liste_arc_etiquette(liste *liste_arc, t_mat_int_dyn duels_mat){

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
        if(duels_mat.tab[x][y] > duels_mat.tab[y][x] && !belongEltList(*liste_arc, arc_inverse)){
          addTailList(liste_arc, arc);
        }
      }
    }
  }
}

int creer_liste_arc_pondere(liste *liste_arc, t_mat_int_dyn duels_mat){
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
        if(duels_mat.tab[x][y] > duels_mat.tab[y][x] && !belongEltList(*liste_arc, arc_inverse)){
          arc.poids = duels_mat.tab[x][y] - duels_mat.tab[y][x];
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

void copie_tabmots_duels_mat(t_mat_char_star_dyn tabmots, t_mat_int_dyn *duels_mat, int nbCandidats){

  creer_t_mat_int_dyn(duels_mat, nbCandidats, nbCandidats);

  for (size_t x = 1; x < nbCandidats+1; x++) {
    for (size_t y = 0; y < nbCandidats; y++) {
      duels_mat->tab[x-1][y] = atoi(tabmots.tab[x][y]);
    }
  }
}


t_tab_int_dyn creer_vote_par_candidat(t_mat_char_star_dyn tabmots, int nombreCandidat){

  t_tab_int_dyn candidats_classement;
  creer_t_tab_int_dyn(&candidats_classement, nombreCandidat);
  init_tab_int(candidats_classement.tab, nombreCandidat, 0);

  for (int i_ligne = 1; i_ligne < tabmots.nbRows-1; i_ligne++) { //on parcourt les lignes
    for (int i_colonne = tabmots.offset; i_colonne < tabmots.nbCol; i_colonne++) { //on parcourt les colonnes pour chercher le min

      // les votes sont compris entre 1 et 10 sinon c'est considéré comme vote nul
      // on cherche tous les minimum de la ligne parce qu'il peut y avoir des ex equo
      if (atoi(tabmots.tab[i_ligne][i_colonne]) == minimum_ligne(tabmots, nombreCandidat, i_ligne) && atoi(tabmots.tab[i_ligne][i_colonne]) >=1 && atoi(tabmots.tab[i_ligne][i_colonne]) <= 10){
        candidats_classement.tab[i_colonne-tabmots.offset]++;
      }
    }
  }
  return candidats_classement;
}


void affiche_resultat(FILE *outfp, char * scrutin, int nbCandidats, int nbVotants , float score, char * vainqueur){

  if(comparer_chaine_char(scrutin, "uni1")){
    fprintf(outfp, "Mode de scrutin : uninominale à un tour, %d candidats, %d votants, vainqueur = %s, score = %f%\n\n", nbCandidats, nbVotants, vainqueur, score);
  }
  if(comparer_chaine_char(scrutin, "uni2 tour1")){
    fprintf(outfp, "Mode de scrutin : uninominale à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %f%\n", nbCandidats, nbVotants, vainqueur, score);
  }
  if(comparer_chaine_char(scrutin, "uni2 tour2")){
    fprintf(outfp, "Mode de scrutin : uninominale à deux tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %f%\n\n", nbCandidats, nbVotants, vainqueur, score);
  }
}

int minimum_ligne(t_mat_char_star_dyn tabmots, int nombreCandidat, int i_ligne){

  int minimum = atoi(tabmots.tab[i_ligne][tabmots.offset]);
  for (int i = tabmots.offset; i < nombreCandidat+tabmots.offset; i++) {
    if(atoi(tabmots.tab[i_ligne][i]) < minimum)
      minimum = atoi(tabmots.tab[i_ligne][i]);
  }
  return minimum;
}

void creer_mat_force_du_plus_fort_chemin(t_mat_int_dyn *p, t_mat_int_dyn duels_mat){

  int nbSommets = p->nbRows;
  for (int i = 0; i < nbSommets; i++) {
    for (int j = 0; j < nbSommets; j++) {
      if (i != j){
        if (duels_mat.tab[i][j] > duels_mat.tab[j][i])
            p->tab[i][j] = duels_mat.tab[i][j];
        else
            p->tab[i][j] = 0;
      }
      else
        p->tab[i][j] = 0;
    }
  }

  for (int i = 0; i < nbSommets; i++) {
    for (int j = 0; j < nbSommets; j++) {
      if (i != j) {
        for (int k = 0; k < nbSommets; k++) {
          if (i != k && j != k) {
            p->tab[j][k] = max(p->tab[j][k], min(p->tab[j][i], p->tab[i][k]));
          }
        }
      }
    }
  }
}

void creer_ensemble_gagnants_potentiels(t_tab_int_dyn *ensemble_gagnants_potentiels, t_mat_int_dyn p){

  int nbSommets = p.nbRows;
  init_tab_int(ensemble_gagnants_potentiels->tab, nbSommets, 0);

  for (int x = 0; x < nbSommets; x++) {
    int gagnant_potentiel = 1;
    for (int y = 0; y < nbSommets; y++) {
      if(x != y){
        if(p.tab[x][y] < p.tab[y][x])
          gagnant_potentiel = 0;
      }
    }
    if(gagnant_potentiel == 1)
      ensemble_gagnants_potentiels->tab[x] = 1;
  }
}

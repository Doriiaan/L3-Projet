/**
* @file utils_scrutins.c
* @brief Fichier contenant les fonctions utiles pour les fonctions de scrutins \n
* exemple : vainqueurCondorcet
* @author ALARY Dorian
* @date Janvier 2022
*/

#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"
#include "fichiers_h/utils_scrutins.h"


/**
* @fn int vainqueurCondorcet(liste larcs, int nbSommets)
* @brief renvoie l'indice du vainqueur de Condorcet s'il y en a un sinon renvoie -1
* @param[in] liste liste des arcs
* @param[out] int indice vainqueur de condorcet ou -1
*/
int vainqueurCondorcet(liste larcs, int nbSommets){

  int vainqueur = -1;

  int x = larcs.Tabliste[0].orig; //sommet actuel
  int nombre_victoire = 1;

  int i_arc = 1;
  while (i_arc < nbEltList(larcs) && nombre_victoire != nbSommets-1) {
    /*
    On parcourt toute la liste,
    si un sommet à autant de victoire qu'il y a d'autres sommet alors il est vainqueur
    sinon on teste avec le prochain sommet
    */
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

/**
* @fn int creer_liste_arc_etiquette(liste *liste_arc, t_mat_int_dyn duels_mat))
* @brief creer la liste des arcs etiquette(graphique)
* @param[in] t_mat_int_dyn matrice des duels
* @param[in, out] liste liste des arcs etiquette(graphique)
*/
void creer_liste_arc_etiquette(liste *liste_arc, t_mat_int_dyn duels_mat){

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
        if(duels_mat.tab[x][y] > duels_mat.tab[y][x] && !belongEltList(*liste_arc, arc_inverse)){ //si "x prefere a y" et on test si "y prefere x" n'y est pas
          addTailList(liste_arc, arc);
        }
      }
    }
  }
}

/**
* @fn int creer_liste_arc_pondere(liste *liste_arc, t_mat_int_dyn duels_mat)
* @brief creer la liste des arcs pondere (graphique)
* @param[in] t_mat_int_dyn matrice des duels
* @param[in, out] liste liste des arcs pondere (graphique)
*/
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

/**
* @fn void construct_mat_duels_d(t_mat_char_star_dyn tabmots,t_mat_int_dyn *duels_mat,int nbCandidats,FILE *outfp)
* @brief creer la matrice des duels
* @param[in] t_mat_char_star_dyn tabmots
* @param[in, out] t_mat_int_dyn *duels_mat
*/
void construct_mat_duels_d(t_mat_char_star_dyn tabmots,t_mat_int_dyn *duels_mat,int nbCandidats,FILE *outfp){

  creer_t_mat_int_dyn(duels_mat, nbCandidats, nbCandidats);
  int nombreVotant = tabmots.nbRows-1;
  int somme_vote_x_superieur_y = 0;

  for (int x = 0; x < nbCandidats; x++) {
    for (int y = 0; y < nbCandidats; y++) {
      if(x != y){

        //pour chaque ligne on va verifier si x prefere y
        for (int i_ligne = 1; i_ligne < nombreVotant; i_ligne++) {

          //on regarde si x prefere y dans la ligne
          if(atoi(tabmots.tab[i_ligne][x + tabmots.offset]) < atoi(tabmots.tab[i_ligne][y + tabmots.offset]) && atoi(tabmots.tab[i_ligne][x + tabmots.offset]) <= 10 && atoi(tabmots.tab[i_ligne][x + tabmots.offset]) >= 1){
            somme_vote_x_superieur_y++;
          }

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

/**
* @fn void copie_tabmots_duels_mat(t_mat_char_star_dyn tabmots, t_mat_int_dyn *duels_mat, int nbCandidats)
* @brief pour l'option -d copier tabmots pour creer la matrice des duels
* @param[in] t_mat_char_star_dyn tabmots
* @param[in, out] t_mat_int_dyn *duels_mat
*/
void copie_tabmots_duels_mat(t_mat_char_star_dyn tabmots, t_mat_int_dyn *duels_mat, int nbCandidats){

  creer_t_mat_int_dyn(duels_mat, nbCandidats, nbCandidats);

  for (size_t x = 1; x < nbCandidats+1; x++) {
    for (size_t y = 0; y < nbCandidats; y++) {
      duels_mat->tab[x-1][y] = atoi(tabmots.tab[x][y]);
    }
  }
}

/**
* @fn t_tab_int_dyn creer_vote_par_candidat(t_mat_char_star_dyn tabmots, int nombreCandidat)
* @brief creer le tableau du nombre de votes des electeurs pour chaqye candidats pour uni1 et uni2
* @param[in] t_mat_char_star_dyn tabmots
* @param[out] t_tab_int_dyn candidats_classement
*/
t_tab_int_dyn creer_vote_par_candidat(t_mat_char_star_dyn tabmots, int nombreCandidat){

  t_tab_int_dyn candidats_classement;
  creer_t_tab_int_dyn(&candidats_classement, nombreCandidat);
  init_tab_int(candidats_classement.tab, nombreCandidat, 0);

  for (int i_ligne = 1; i_ligne < tabmots.nbRows-1; i_ligne++) { //on parcourt les lignes
    for (int i_colonne = tabmots.offset; i_colonne < tabmots.nbCol; i_colonne++) { //on parcourt les colonnes pour chercher le min

      // les votes sont compris entre 1 et 10 sinon c'est considéré comme vote nul
      // on cherche tous les minimum de la ligne parce qu'il peut y avoir des ex equo
      if (atoi(tabmots.tab[i_ligne][i_colonne]) == minimum_ligne(tabmots, nombreCandidat, i_ligne) && atoi(tabmots.tab[i_ligne][i_colonne]) <= 10 && atoi(tabmots.tab[i_ligne][i_colonne]) >= 1){
        candidats_classement.tab[i_colonne-tabmots.offset]++;
      }
    }
  }
  return candidats_classement;
}

/**
* @fn void affiche_resultat(FILE *outfp, char * scrutin, int nbCandidats, int nbVotants , float score, char * vainqueur)
* @brief affiche les resultats de uninominale
*/
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

/**
* @fn int minimum_ligne(t_mat_char_star_dyn tabmots, int nombreCandidat, int i_ligne)
* @brief cherche la valeur minimum d'une ligne du tableau csv
* @param[in] t_mat_char_star_dyn tabmots
* @param[out] int minimum
*/
int minimum_ligne(t_mat_char_star_dyn tabmots, int nombreCandidat, int i_ligne){

  int minimum = atoi(tabmots.tab[i_ligne][tabmots.offset]);
  for (int i = tabmots.offset; i < nombreCandidat+tabmots.offset; i++) {
    if(atoi(tabmots.tab[i_ligne][i]) < minimum)
      minimum = atoi(tabmots.tab[i_ligne][i]);
  }
  return minimum;
}

/**
* @fn void creer_mat_force_du_plus_fort_chemin(t_mat_int_dyn *p, t_mat_int_dyn duels_mat)
* @brief creer la matrice des forces des plus fort chemins \n
* Algorithme recuperer de la page wikipedia condorcet schulze anglophone \n
* https://en.wikipedia.org/wiki/Schulze_method
* @param[in] t_mat_int_dyn duels_mat
* @param[in, out] t_mat_int_dyn *p
*/
void creer_mat_force_du_plus_fort_chemin(t_mat_int_dyn *p, t_mat_int_dyn duels_mat){

  // etape 1) ecrit dans la matrice les score des duels gagnant et 0 pour les perdant
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

  /* etape 2) On prends tous les poids des arcs des chemins,
     on note leurs minimums de chaque chemin,
     on garde que le chemin qui a le plus fort des minimums
     on écrit son minimum dans la matrice
  */
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

/**
* @fn void creer_ensemble_gagnants_potentiels(t_tab_int_dyn *ensemble_gagnants_potentiels, t_mat_int_dyn p)
* @brief creer l'ensemble des gagnants potentiels de schulze
* @param[in] t_mat_int_dyn matrice force des plus fort chemin (p)
* @param[in, out] t_tab_int_dyn *ensemble_gagnants_potentiels
*/
void creer_ensemble_gagnants_potentiels(t_tab_int_dyn *ensemble_gagnants_potentiels, t_mat_int_dyn p){

  // si pour x, chaque chemin vers y est plus fort que le chemin de y vers x
  // alors x est un gagant potentiel
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

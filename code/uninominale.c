/**
* @file uninominale.c
* @brief Fichier contenant les fonctions d'election par methode uninominale \n
* @author ALARY Dorian
* @date Janvier 2022
*/


#include "fichiers_h/global.h"
#include "fichiers_h/utils_scrutins.h"
#include "fichiers_h/utils.h"

/**
* @fn void uninominal_un_tour(t_tab_int_dyn vote_par_candidat, t_mat_char_star_dyn tabmots, FILE *outfp)
* @brief affiche le vainqueur par la methode uninominale un tour
*/
void uninominal_un_tour(t_tab_int_dyn vote_par_candidat, t_mat_char_star_dyn tabmots, FILE *outfp){

  fprintf(outfp, "\n\n-------------------------------------\n");
  fprintf(outfp, "----------UNINOMINALE 1 TOUR---------\n");
  fprintf(outfp, "-------------------------------------\n\n");
  int nombreVotant = tabmots.nbRows-1;
  int nombreCandidat = vote_par_candidat.dim;

  // chercher le nom du vainqueur
  int indice_vainqueur = max_tab_indice(vote_par_candidat.tab, vote_par_candidat.dim); //on prend le max des vote par candidats

  //on redimensione le nom au cas ou la taille est trop petite
  int taille = LONGMOTS;
  char *nom_vainqueur = (char *) malloc(taille*sizeof(char));
  while(strlen(tabmots.tab[0][indice_vainqueur+tabmots.offset]) > taille){
    taille *= 2;
    nom_vainqueur = (char*) realloc(nom_vainqueur, taille*sizeof(char));
  }

  float score = ((float)(vote_par_candidat.tab[indice_vainqueur]) / (float)(nombreVotant)) * 100;
  copier_chaine_char(tabmots.tab[0][indice_vainqueur+tabmots.offset], nom_vainqueur);

  affiche_resultat(outfp, "uni1", nombreCandidat, nombreVotant,  score, nom_vainqueur);
  free(nom_vainqueur);
}

/**
* void uninominal_deux_tours(t_tab_int_dyn vote_par_candidat, t_mat_int_dyn duels_mat, t_mat_char_star_dyn tabmots, FILE *outfp)
* @brief affiche le vainqueur par la methode uninominale deux tours
*/
void uninominal_deux_tours(t_tab_int_dyn vote_par_candidat, t_mat_int_dyn duels_mat, t_mat_char_star_dyn tabmots, FILE *outfp){

  fprintf(outfp, "\n\n-------------------------------------\n");
  fprintf(outfp, "---------UNINOMINALE 2 TOURS---------\n");
  fprintf(outfp, "-------------------------------------\n\n");
  int nombreVotant = tabmots.nbRows-1;
  int nombreCandidat = tabmots.nbCol-tabmots.offset;

  // chercher le nom du vainqueur
  int indice_vainqueur1 = max_tab_indice(vote_par_candidat.tab, vote_par_candidat.dim);//on prend le max des vote par candidats

  int indice_vainqueur2 = 0; //on cherche le deuxieme max de la liste
  if(indice_vainqueur1 == 0)
    indice_vainqueur2 = 1;
  for (int i = 0; i < vote_par_candidat.dim; i++) {
    if(vote_par_candidat.tab[indice_vainqueur2] < vote_par_candidat.tab[i] && i != indice_vainqueur1)
      indice_vainqueur2 = i;
  }
  float score_vainqueur1 = ((float)(vote_par_candidat.tab[indice_vainqueur1]) / (float)(nombreVotant)) * 100;
  float score_vainqueur2 = ((float)(vote_par_candidat.tab[indice_vainqueur2]) / (float)(nombreVotant)) * 100;

  //on redimensione le nom au cas ou la taille est trop petite
  int taille = LONGMOTS;
  char *nom_vainqueur1 = (char *) malloc(taille*sizeof(char));
  while(strlen(tabmots.tab[0][indice_vainqueur1+tabmots.offset]) > taille){
    taille *= 2;
    nom_vainqueur1 = (char*) realloc(nom_vainqueur1, taille*sizeof(char));
  }

  //on redimensione le nom au cas ou la taille est trop petite
  taille = LONGMOTS;
  char *nom_vainqueur2 = (char *) malloc(taille*sizeof(char));
  while(strlen(tabmots.tab[0][indice_vainqueur2+tabmots.offset]) > taille){
    taille *= 2;
    nom_vainqueur2 = (char*) realloc(nom_vainqueur2, taille*sizeof(char));
  }

  copier_chaine_char(tabmots.tab[0][indice_vainqueur1+tabmots.offset], nom_vainqueur1);
  copier_chaine_char(tabmots.tab[0][indice_vainqueur2+tabmots.offset], nom_vainqueur2);

  affiche_resultat(outfp, "uni2 tour1", nombreCandidat, nombreVotant,  score_vainqueur1, nom_vainqueur1);
  affiche_resultat(outfp, "uni2 tour1", nombreCandidat, nombreVotant,  score_vainqueur2, nom_vainqueur2);
  if(duels_mat.tab[indice_vainqueur1][indice_vainqueur2] > duels_mat.tab[indice_vainqueur2][indice_vainqueur1]){
    float score_vainqueur = ((float)(duels_mat.tab[indice_vainqueur1][indice_vainqueur2]) / (float)(nombreVotant)) * 100;
    affiche_resultat(outfp, "uni2 tour2", nombreCandidat, nombreVotant,  score_vainqueur, nom_vainqueur1);
  }
  else{
    float score_vainqueur = ((float)(duels_mat.tab[indice_vainqueur2][indice_vainqueur1]) / (float)(nombreVotant)) * 100;
    affiche_resultat(outfp, "uni2 tour2", nombreCandidat, nombreVotant,  score_vainqueur, nom_vainqueur2);
  }
  free(nom_vainqueur1);
  free(nom_vainqueur2);
}

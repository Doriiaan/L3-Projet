/**
* @file analyse_csv.c
* @brief Fichier contenant les fonctions de traitement du fichier csv
* @author ALARY Dorian
* @date Janvier 2022
*/

#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"


/**
* @fn void read_voting_file(char * filename,char *delimiteur,t_mat_char_star_dyn *t_tabmots)
* @brief
* etape 1) compte le nombre de lignes et de colonnes \n
* etape 2) fait les realloc necessaire \n
* etape 3) rentre tous le tableau mot par mot dans un tableau de type t_mat_char_star_dyn \n
*/
void read_voting_file(char * filename,char *delimiteur,t_mat_char_star_dyn *t_tabmots){

  // ouvrir fichier
  FILE * fichier;
  fichier = fopen(filename, "r");

  int nb_lignes = 0;
  int nb_colonnes = 0;
  char ligne[MAX];

  // compter lignes et colonnes
  while (fgets(ligne, MAX, fichier) != NULL) { // tant que des lignes existent
    char * mot = strtok(ligne, delimiteur); // toutes les lettres avant un delimiteur forme un "mot"
    nb_lignes++;
    nb_colonnes = 0;
    while (mot != NULL) { // tant que les mots existent dans la lignes
        nb_colonnes++;
        mot = strtok(NULL, delimiteur);

    }
  }

  // realloc
  t_tabmots->tab = (char***) realloc(t_tabmots->tab, nb_lignes*sizeof(char**)); // realoc lignes
  for (int i_ligne = 0; i_ligne < nb_lignes; i_ligne++) {
    t_tabmots->tab[i_ligne] = (char**) realloc(t_tabmots->tab[i_ligne], nb_colonnes*sizeof(char*)); // realoc colonnes
    for (int i_colonne = 0; i_colonne < nb_colonnes; i_colonne++) {
      t_tabmots->tab[i_ligne][i_colonne] = (char*) realloc(t_tabmots->tab[i_ligne][i_colonne], LONGMOTS*sizeof(char)); // realoc mots
    }
  }


  // ecrire dans la matrice de char
  int i = 0; //indice ligne
  int y = 0; //indice colonnes

  rewind(fichier); // initialise le pointeur du fichier au caractere 0
  while (fgets(ligne, MAX, fichier) != NULL) {
    char * mot = strtok(ligne, delimiteur);
    y = 0;
    while (mot != NULL) {

      copier_chaine_char(mot, t_tabmots->tab[i][y]);

      y++;
      mot = strtok(NULL, delimiteur);
    }
    i++;
  }
  t_tabmots->nbRows = nb_lignes;
  t_tabmots->nbCol = nb_colonnes;

  fclose(fichier);
}

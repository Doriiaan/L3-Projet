/**
* @file utils.c
* @brief Fichier contenant les fonctions de bases utiles pour toute sorte de fonction \n
* exemple : fonction copier_chaine_char
* @author ALARY Dorian
* @date Janvier 2022
*/
#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"
#include <stddef.h>

/**
* @fn void erreur(char *message)
* @brief ecrit un message d'erreur et quitte le programme
*/
void erreur(char *message){

  printf("%s\n", message);
  exit(EXIT_FAILURE);
}

/**
* @fn int* creer_tab_int(int dim)
* @brief creer un tableau dynamique de int
*/
int* creer_tab_int(int dim){

  int *tableau = (int*) malloc(dim*sizeof(int));
  if(tableau == NULL){
    exit(1);
  }

  return tableau;
}

/**
* @fn int** creer_mat_int(int nbRows,int nbCol)
* @brief creer une matrice dynamique de int
*/
int ** creer_mat_int(int nbRows,int nbCol){

  int** matrice = (int**) malloc(nbRows*sizeof(int*));

  if(matrice == NULL){
    exit(1);
  }
  for (int i = 0; i < nbRows; i++) {
    matrice[i] = (int*) malloc(nbCol*sizeof(int));
    if(matrice == NULL){
      exit(1);
    }
  }
  return matrice;
}

/**
* @fn void affiche_tab_int(int *tab,int dim, FILE *outfp)
* @brief affiche un tableau de int sur la sortie outfp
*/
void affiche_tab_int(int *tab,int dim, FILE *outfp){

  for (int i = 0; i < dim; i++) {
    fprintf(outfp, "%d ", tab[i]);
  }
  fprintf(outfp, "\n");
}

/**
* @fn void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *outfp)
* @brief affiche une matrice de int sur la sortie outfp
*/
void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *outfp){

  for (int i = 0; i < nbRows; i++) {
    for (int y = 0; y < nbCol; y++) {
      fprintf(outfp, "%d ", duels_mat[i][y]);
    }
    fprintf(outfp, "\n");
  }
}

/**
* @fn init_tab_int(int *tab,int dim,int valeur)
* @brief initialise un tableau de int avec une valeur
*/
void init_tab_int(int *tab,int dim,int valeur){

  for (int i = 0; i < dim; i++) {
    tab[i] = valeur;
  }
}

/**
* @fn void init_mat_int(int **mat,int nbRows,int nbCol,int valeur)
* @brief initialise une matrice de int avec une valeur
*/
void init_mat_int(int **mat,int nbRows,int nbCol,int valeur){
  for (int i = 0; i < nbRows; i++) {
    for (int y = 0; y < nbCol; y++) {
      mat[i][y] = valeur;
    }
  }
}

/**
* @fn int max_tab_indice(int *tab, int dim)
* @brief renvoie l'indice de la valeur maximale dans un tableau
*/
int max_tab_indice(int *tab, int dim){
  int imax = 0;
  for (int i = 1; i < dim; i++) {
    if(tab[i] > tab[imax])
      imax = i;
  }
  return imax;
}

/**
* @fn int min_tab_indice_non_j(int *tab, int dim,int j)
* @brief renvoie l'indice de la valeur minimale dans un tableau qui n'est pas d'indice j
*/
int min_tab_indice_non_j(int *tab, int dim,int j){

  int imin;
  if(j != 0)
    imin = 0;
  else
    imin = 1;

  for (int i = 0; i < dim; i++){
    if(i != j){
      if(tab[imin] < tab[i])
        imin = i;
    }
  }
  return imin;

}

/**
* @fn void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim)
* @brief creer une variable t_tab_int_dyn grace a la fonction creer_tab_int
*/
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim){
  stTab->tab = creer_tab_int(dim);
  stTab->dim = dim;
}

/**
* @fn void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol)
* @brief creer une variable t_mat_int_dyn grace a la fonction creer_mat_int
*/
void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol){
  stTab->tab = creer_mat_int(nbRows, nbCol);
  stTab->nbRows = nbRows;
  stTab->nbCol = nbCol;
}

/**
* @fn void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots)
* @brief creer une variable t_mat_char_star_dyn, initialise sa matrice de 3 dimensions dynamiquement
*/
void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots){
  char *** mat = (char***) malloc(sizeof(char**));
  mat[0] = (char **)malloc(sizeof(char*));
  mat[0][0] = (char*) malloc(LONGMOTS*sizeof(char));

  s_tabmots->tab = mat;
  s_tabmots->nbRows = 1;
  s_tabmots->nbCol = 1;
  s_tabmots->offset = NBCOLADM+1;
}

/**
* @fn void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *outfp)
* @brief affiche une matrice de chaine de caractere, le tableau csv ici
*/
void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *outfp){

  for (int i = 0; i < t_tabmots.nbRows; i++) {
    for (int y = 0; y < t_tabmots.nbCol; y++) {
      fprintf(outfp, "%s, ", t_tabmots.tab[i][y]);
    }
    fprintf(outfp, "\n");
  }
}

/**
* @fn void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *outfp)
* @brief affiche une matrice de int
*/
void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *outfp){
  for (int i = 0; i < t_tab.nbRows; i++) {
    for (int y = 0; y < t_tab.nbCol; y++) {
      fprintf(outfp, "%4d ", t_tab.tab[i][y]);
    }
    fprintf(outfp, "\n");
  }
}

/**
* @fn void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *outfp)
* @brief affiche un tableau de int
*/
void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *outfp){
  for (int i = 0; i < t_tab.dim; i++) {
      fprintf(outfp, "%4d ", t_tab.tab[i]);
    }
    fprintf(outfp, "\n");
}

/**
* @fn void copier_chaine_char(char const *source, char *destination)
* @brief copie une chaine de caractere source dans une chaine de caractere destination
*/
void copier_chaine_char(char const *source, char *destination){

  int i= 0;
  for (i; source[i] != '\0'; i++) {
    destination[i] = source[i];
  }
  destination[i] = '\0';
}

/**
* @fn int comparer_chaine_char(char const *source1, char const* source2)
* @brief compare deux chaine de caracteres
*/
int comparer_chaine_char(char const *source1, char const* source2){
  if (sizeof(source1) != sizeof(source2))
    return 0;
  for (int i = 0; source1[i] != '\0' && source2[i] != '\0'; i++){
    if(source1[i] != source2[i])
      return 0;
  }
  return 1;
}

/**
* @fn int max(int a, int b)
* @brief renvoit le max entre 2 int
*/
int max(int a, int b){
  if(a > b)
    return a;
  return b;
}

/**
* @fn int min(int a, int b)
* @brief renvoit le min entre 2 int
*/
int min(int a, int b){
  if(a < b)
    return a;
  return b;
}

/**
* @fn int verifier_fichier_txt(const char* nom_de_fichier)
* @brief verifie si le fichier correspondant est a une extension .txt
*/
int verifier_fichier_txt(const char* nom_de_fichier){

  int taille_nom = 0;
  while (nom_de_fichier[taille_nom] != '\0') {
    taille_nom++;
  }
  if (nom_de_fichier[taille_nom-4] == '.' && nom_de_fichier[taille_nom-3] == 't' && nom_de_fichier[taille_nom-2] == 'x' && nom_de_fichier[taille_nom-1] == 't') {
    return 1;
  }
  return 0;
}

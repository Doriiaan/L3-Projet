#include "fichiers_h/global.h"
#include <stddef.h>



// Je crois que ça affiche un *message d'erreur sur stderr
void erreur(char *message){

  printf("%s\n", message);
  exit(EXIT_FAILURE);
}

//Utile pour créer les tab dans les structures
int * creer_tab_int(int dim){

  int *tableau = (int*) malloc(dim*sizeof(int));
  if(tableau == NULL){
    exit(1);
  }

  return tableau;
}

// Utile pour créer les mat dans les structures
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

//Affiche un tableau
void affiche_tab_int(int *tab,int dim, FILE *outfp){

  for (int i = 0; i < dim; i++) {
    fprintf(outfp, "%d ", tab[i]);
  }
  fprintf(outfp, "\n");
}

//Affiche une matrice
void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *outfp){

  for (int i = 0; i < nbRows; i++) {
    for (int y = 0; y < nbCol; y++) {
      fprintf(outfp, "%d ", duels_mat[i][y]);
    }
    fprintf(outfp, "\n");
  }
}

//Initalise un tableau dynamique pour struc
void init_tab_int(int *tab,int dim,int valeur){

  for (int i = 0; i < dim; i++) {
    tab[i] = valeur;
  }
}

//Initialise une matrice dynamique pour struct
void init_mat_int(int **mat,int nbRows,int nbCol,int valeur){
  for (int i = 0; i < nbRows; i++) {
    for (int y = 0; y < nbCol; y++) {
      mat[i][y] = valeur;
    }
  }
}

// ...
int min_borne(char * tab[],int dim,int borne){

}

//Indice du max
int max_tab_indice(int *tab, int dim){
  int imax = 0;
  for (int i = 0; i < dim; i++) {
    if(tab[i] > tab[imax])
      imax = i;
  }
  return imax;
}

//Minimum qui n'est pas d'indice j
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

//Somme du tableau
int som_tab_indice(int *tab, int dim){

}

// Appeler creer_tab
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim){
  stTab->tab = creer_tab_int(dim);
  stTab->dim = dim;
}

// Appeler creer_mat
void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol){
  stTab->tab = creer_mat_int(nbRows, nbCol);
  stTab->nbRows = nbRows;
  stTab->nbCol = nbCol;
}
//[[""], [""], [""]]
// creer mat dynamique de chaine
void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots){

  char *** mat = (char***) malloc(sizeof(char**));
  mat[0] = (char **)malloc(sizeof(char*));
  mat[0][0] = (char*) malloc(LONGMOTS*sizeof(char));

  s_tabmots->tab = mat;
  s_tabmots->nbRows = 1;
  s_tabmots->nbCol = 1;
  s_tabmots->offset = 4;
}

// affiche la matrice structure dans l'output, un fichier
void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *outfp){
  for (int i = 0; i < t_tabmots.nbRows; i++) {
    for (int y = 0; y < t_tabmots.nbCol; y++) {
      printf("%s ", t_tabmots.tab[i][y]);
    }
    printf("\n");
  }
}

// affiche la matrice structure dans l'output, un fichier
void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *outfp){

  for (int i = 0; i < t_tab.nbRows-1; i++) {
    for (int y = 0; y < t_tab.nbCol-1; y++) {
      fprintf(outfp, "%d ", t_tab.tab[i][y]);
    }
    fprintf(outfp, "\n");
  }
}

// affiche le tableau structure dans l'output, un fichier
void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *outfp){
  for (int i = 0; i < t_tab.dim; i++) {
      fprintf(outfp, "%d ", t_tab.tab[i]);
    }
    fprintf(outfp, "\n");
}

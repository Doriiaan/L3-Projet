#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"
#include <stddef.h>


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
  for (int i = 1; i < dim; i++) {
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
  s_tabmots->offset = NBCOLADM+1;
}

// affiche la matrice structure dans l'output, un fichier
void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *outfp){

  for (int i = 0; i < t_tabmots.nbRows; i++) {
    for (int y = 0; y < t_tabmots.nbCol; y++) {
      fprintf(outfp, "%s, ", t_tabmots.tab[i][y]);
    }
    fprintf(outfp, "\n");
  }
}

// affiche la matrice structure dans l'output, un fichier
void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *outfp){
  for (int i = 0; i < t_tab.nbRows; i++) {
    for (int y = 0; y < t_tab.nbCol; y++) {
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

void copier_chaine_char(char const *source, char *destination){

  int i= 0;
  for (i; source[i] != '\0'; i++) {
    destination[i] = source[i];
  }
  destination[i] = '\0';
}

int comparer_chaine_char(char const *source1, char const* source2){
  if (sizeof(source1) != sizeof(source2))
    return 0;
  for (int i = 0; source1[i] != '\0' && source2[i] != '\0'; i++){
    if(source1[i] != source2[i])
      return 0;
  }
  return 1;
}

int max(int a, int b){
  if(a > b)
    return a;
  return b;
}

int min(int a, int b){
  if(a < b)
    return a;
  return b;
}

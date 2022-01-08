#include "fichiers_h/global.h"
#include "fichiers_h/utils.h"

// Va lire le tableur et mettre les infos dans une matrice t_mat_char_star_dyn (pour −i et −d).

void read_voting_file(char * filename,char *delimiteur,t_mat_char_star_dyn *t_tabmots){

  //ouvrir fichier
  FILE * fichier;
  fichier = fopen(filename, "r");

  int nb_lignes = 0;
  int nb_colonnes = 0;
  char ligne[MAX];

  //compter lignes et colonnes
  while (fgets(ligne, MAX, fichier) != NULL) { //tant que des lignes existent
    char * mot = strtok(ligne, delimiteur); //toutes les lettres avant un delimiteur forme un "mot"
    nb_lignes++;
    nb_colonnes = 0;
    while (mot != NULL) { //tant que les mots existent dans la lignes
        nb_colonnes++;
        mot = strtok(NULL, delimiteur);

    }
  }

  //realloc
  t_tabmots->tab = (char***) realloc(t_tabmots->tab, nb_lignes*sizeof(char**)); //realoc ligne
  for (int i_ligne = 0; i_ligne < nb_lignes; i_ligne++) {
    t_tabmots->tab[i_ligne] = (char**) realloc(t_tabmots->tab[i_ligne], nb_colonnes*sizeof(char*)); //realoc colonne
    for (int i_colonne = 0; i_colonne < nb_colonnes; i_colonne++) {
      t_tabmots->tab[i_ligne][i_colonne] = (char*) realloc(t_tabmots->tab[i_ligne][i_colonne], LONGMOTS*sizeof(char)); //realoc mot
    }
  }


  //ecrire dans le tableau
  int i = 0; //indice ligne
  int y = 0; //indice colonnes
  int z = 0; //indice lettre dans le mot

  rewind(fichier);
  while (fgets(ligne, MAX, fichier) != NULL) {
    char * mot = strtok(ligne, delimiteur);
    y = 0;
    while (mot != NULL) {
      int taille = LONGMOTS;
      while(strlen(mot) > taille){
        taille *= 2;
        t_tabmots->tab[i][y] = (char*) realloc(t_tabmots->tab[i][y], taille*sizeof(char));
      }
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

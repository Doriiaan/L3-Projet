#include <stdio.h>
#include "fichiers_h/global.h"

int main(int argc, char const *argv[]) {

  t_mat_char_star_dyn tab;
  creer_t_mat_char_dyn(&tab);
  read_voting_file("calcul2.csv", ",\n", &tab);
  affiche_t_mat_char_star_dyn(tab, stdout);
  return 0;
}

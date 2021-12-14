#include <stdio.h>
#include "fichiers_h/global.h"

int main(int argc, char const *argv[]) {
  printf("Hello World \n");
  erreur("Dommage !");
  t_mat_char_star_dyn s_tabmots;
  creer_t_mat_char_dyn(&s_tabmots);
  printf("%d\n", s_tabmots.offset);
  return 0;
}

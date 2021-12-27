#include <stdio.h>
#include "fichiers_h/global.h"

void copier_chaine_char(char const *source, char* destination);
int comparer_chaine_char(char const *source1, char const* source2);

int main(int argc, char const *argv[]) {

  // TRAITEMENT OPTIONS---------------------------------------------------------
  int options[NB_BALISES] = {0, 0, 0, 0}; //1 si l'option est la, 0 sinon (-i, -d, -o, -m)
  int methode[NB_METHODES] = {0, 0, 0, 0, 0}; //1 si la methode est demande, 0 sinon
  FILE* output = stdout;
  FILE* fichier_csv;

  if(argc <= 7){

    //compte les options
    for (int i_opt = 1; i_opt < argc; i_opt++) { //boucle des options

      if (comparer_chaine_char(argv[i_opt], "-i")) { //traitement de l'option -i
        if (options[0] == 1)
          erreur("Ne pas mettre deux fois la meme option\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        if(i_opt == argc-1 || argv[i_opt+1][0] == '-')
          erreur("Il faut rajouter un fichier csv en argument\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

        fichier_csv = fopen(argv[i_opt+1], "r");
        if(fichier_csv == NULL)
          erreur("Le fichier csv n'est pas accessible\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        options[0] = 1;
      }

      else if (comparer_chaine_char(argv[i_opt], "-d")){ //traitement de l'option -d
        if (options[1] == 1)
          erreur("Ne pas mettre deux fois la meme option\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        if(i_opt == argc-1 || argv[i_opt+1][0] == '-')
          erreur("Il faut rajouter un fichier csv en argument\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

        fichier_csv = fopen(argv[i_opt+1], "r");
        if(fichier_csv == NULL)
          erreur("Le fichier csv n'est pas accessible\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        options[1] = 1;
      }

      else if (comparer_chaine_char(argv[i_opt], "-o")){ //traitement de l'option -o
        if (options[2] == 1)
          erreur("Ne pas mettre deux fois la meme option\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        if(i_opt == argc-1 || argv[i_opt+1][0] == '-')
          erreur("Il faut rajouter un fichier log en argument\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

        output = fopen(argv[i_opt+1], "r");
        if(output == NULL)
          output = stdout;
        else
          options[2] = 1;
      }

      else if (comparer_chaine_char(argv[i_opt], "-m")){ //traitement de l'option -m
        if (options[3] == 1)
          erreur("Ne pas mettre deux fois la meme option\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        if(i_opt == argc-1 || argv[i_opt+1][0] == '-')
          erreur("Il faut rajouter une methode\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

        options[3] = 1;
        if (comparer_chaine_char(argv[i_opt+1], "uni1"))
          methode[0] = 1;
        else if (comparer_chaine_char(argv[i_opt+1], "uni2"))
          methode[1] = 1;
        else if (comparer_chaine_char(argv[i_opt+1], "cm"))
          methode[2] = 1;
        else if (comparer_chaine_char(argv[i_opt+1], "cs"))
          methode[3] = 1;
        else if (comparer_chaine_char(argv[i_opt+1], "all")){
          methode[4] = 1;
        }
      }

      if(options[0] == 1 && options[1] == 1) // si -d et -i STOP
        erreur("les options -i et -d ne sont pas compatibles\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
    }
    if(options[0] == 0 && options[1] == 0 || options[3] == 0) // si pas de -i ou -d et pas de -m STOP
      erreur("Il faut rajouter l'option -i ou -d et -m\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
    if((methode[0] == 1 || methode[1] == 1) && options[1] == 1) // si uni1 ou uni2 et -d STOP
      erreur("Les methodes uni1 et uni2 ne fonctionnent pas avec l'option -d\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

    if(methode[4] == 1){ // si "all" -> utilise tout
      methode[0] = 1;
      methode[1] = 1;
      methode[2] = 1;
      methode[3] = 1;
      if(options[1] == 1){// si -d -> enleve uni1 et uni2
        methode[0] = 0;
        methode[1] = 0;
      }
    }

  }
  else // si trop d'arguments STOP
    erreur("Trop d'arguments\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

  // SUITE ---------------------------------------------------------------------




  if (options[2] == 1)
    fclose(output);
  fclose(fichier_csv);
  return 0;
}


// FONCTIONS ANNEXES------------------------------------------------------------

void copier_chaine_char(char const *source, char *destination){
  if(sizeof(destination) < sizeof(source))
    exit(EXIT_FAILURE);
  for (int i = 0; source[i] != '\0'; i++) {
    destination[i] = source[i];
  }
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

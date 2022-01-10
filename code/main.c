#include <stdio.h>
#include "fichiers_h/global.h"
#include "fichiers_h/utils_scrutins.h"
#include "fichiers_h/utils.h"

void copier_chaine_char(char const *source, char* destination);
int comparer_chaine_char(char const *source1, char const* source2);

int main(int argc, char const *argv[]) {

  // TRAITEMENT OPTIONS---------------------------------------------------------
  int options[NB_BALISES] = {0, 0, 0, 0}; //1 si l'option est la, 0 sinon (-i, -d, -o, -m)
  int methode[NB_METHODES] = {0, 0, 0, 0, 0}; //1 si la methode est demande, 0 sinon
  FILE* output = stdout;
  FILE* fichier_csv;
  char nom_fichier_csv[200];

  if(argc <= 7 && argc >= 5){

    //compte les options
    for (int i_opt = 1; i_opt < argc; i_opt++) { //boucle des options

      if(argv[i_opt][0] == '-' && !(comparer_chaine_char(argv[i_opt], "-i") || comparer_chaine_char(argv[i_opt], "-d") || comparer_chaine_char(argv[i_opt], "-m") || comparer_chaine_char(argv[i_opt], "-o")))
        erreur("Une option n'existe pas\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

      if (comparer_chaine_char(argv[i_opt], "-i")) { //traitement de l'option -i
        if (options[0] == 1)
          erreur("Ne pas mettre deux fois la meme option\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        if(i_opt == argc-1 || argv[i_opt+1][0] == '-')
          erreur("Il faut rajouter un fichier csv en argument\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

        fichier_csv = fopen(argv[i_opt+1], "r");
        if(fichier_csv == NULL)
          erreur("Le fichier csv n'est pas accessible\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        fclose(fichier_csv);
        copier_chaine_char(argv[i_opt+1], nom_fichier_csv);
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
        fclose(fichier_csv);
        copier_chaine_char(argv[i_opt+1], nom_fichier_csv);
        options[1] = 1;
      }

      else if (comparer_chaine_char(argv[i_opt], "-o")){ //traitement de l'option -o
        if (options[2] == 1)
          erreur("Ne pas mettre deux fois la meme option\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        if(i_opt == argc-1 || argv[i_opt+1][0] == '-')
          erreur("Il faut rajouter un fichier log en argument\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        if(!verifier_fichier_txt(argv[i_opt+1]))
          erreur("Le fichier log doit etre un fichier txt\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");
        output = fopen(argv[i_opt+1], "w");
        if(output == NULL){
          output = stdout;
          fprintf(stderr, "Le fichier log n'est pas accessible, la sortie se fera sur la sortie standard\n");
          fprintf(stderr, "-----------------------------------------------------------------------------\n");
        }
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
    erreur("Il n'y a pas le bon nombre d'arguments\nUtilisation: ./vote -i,-d fichier_csv -m methode [-o log.txt]\n");

  // SUITE ---------------------------------------------------------------------

  // VARIABLES
  t_mat_char_star_dyn tabmots;
  t_mat_int_dyn duels_mat;
  liste liste_arc;
  int nombreCandidat = 0;
  int nombreVotant = 0;

  creer_t_mat_char_dyn(&tabmots);
  read_voting_file(nom_fichier_csv,"\n,",&tabmots);

  createList(&liste_arc);

  // APPLIQUER LA METHODE EN FONCTION DES OPTIONS
  if(options[0] == 1){ // -i

    nombreVotant = tabmots.nbRows -1;
    nombreCandidat = tabmots.nbCol-tabmots.offset;
    t_tab_int_dyn vote_par_candidat = creer_vote_par_candidat(tabmots, nombreCandidat); //creer le nombre de vote par candidat
    construct_mat_duels_d(tabmots, &duels_mat, nombreCandidat, output); //creer la matrice des duels
    creer_liste_arc_etiquette(&liste_arc, duels_mat); //creer la liste des arcs etiquetté

    if(options[2] == 1){ //fichier log ouvert
      if(methode[0] == 1 || methode[1] == 1){
        fprintf(output, "\n\n-----TABLEAU VOTE PAR CANDIDAT-----\n");
        affiche_t_tab_int_dyn(vote_par_candidat, output);
      }
      fprintf(output, "\n\n-----MATRICE DES DUELS-----\n");
      affiche_t_mat_int_dyn(duels_mat, output);
      fprintf(output, "\n\n-----GRAPHE ORIENTE-----\n");
      dumpList(liste_arc, output);
      fprintf(output, "\n");
    }

    //methode uninominale 1 tour
    if(methode[0] == 1 || methode[4] == 1){
      uninominal_un_tour(vote_par_candidat, tabmots, output);
    }

    //methode uninominale 2 tour
    if(methode[1] == 1 || methode[4] == 1){
      uninominal_deux_tours(vote_par_candidat, duels_mat, tabmots, output);
    }

    //methode minimax
    if(methode[2] == 1 || methode[4] == 1){
      int indice_vainqueur = minimax(duels_mat,liste_arc, nombreCandidat, output);

      int taille = LONGMOTS;
      char *nom_vainqueur = (char *) malloc(taille*sizeof(char));
      while(strlen(tabmots.tab[0][indice_vainqueur+tabmots.offset]) > taille){
        taille *= 2;
        nom_vainqueur = (char*) realloc(nom_vainqueur, taille*sizeof(char));
      }

      copier_chaine_char(tabmots.tab[0][indice_vainqueur+tabmots.offset], nom_vainqueur);
      fprintf(output, "Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s\n\n", nombreCandidat, nombreVotant, nom_vainqueur);
    }

    //methode schulze
    if(methode[3] == 1 || methode[4] == 1){
      t_tab_int_dyn liste_gagnants_schulzes;
      creer_t_tab_int_dyn(&liste_gagnants_schulzes, nombreCandidat);
      liste_gagnants_schulzes = schulze(duels_mat, liste_arc, nombreCandidat, output);


      for (int i_gagnant = 0; i_gagnant < nombreCandidat; i_gagnant++) {
        if(liste_gagnants_schulzes.tab[i_gagnant] == 1){

          int taille = LONGMOTS;
          char *nom_vainqueur = (char *) malloc(taille*sizeof(char));
          while(strlen(tabmots.tab[0][i_gagnant+tabmots.offset]) > taille){
            taille *= 2;
            nom_vainqueur = (char*) realloc(nom_vainqueur, taille*sizeof(char));
          }

          copier_chaine_char(tabmots.tab[0][i_gagnant+tabmots.offset], nom_vainqueur);
          fprintf(output, "Mode de scrutin : Condorcet schulze, %d candidats, %d votants, vainqueur = %s\n", nombreCandidat, nombreVotant, nom_vainqueur);
        }
      }
    }
  }

  if(options[1] == 1){ // -d

    tabmots.offset = 0; //ajuste le offset
    nombreCandidat = tabmots.nbCol;
    copie_tabmots_duels_mat(tabmots, &duels_mat, nombreCandidat); // creer la matrice des duels
    nombreVotant = duels_mat.tab[0][1] + duels_mat.tab[1][0];
    creer_liste_arc_etiquette(&liste_arc, duels_mat); //creer la liste des arcs

    if(options[2] == 1){ //fichier log ouvert
        fprintf(output, "-----MATRICE DES DUELS-----\n\n");
        affiche_t_mat_int_dyn(duels_mat, output);
        fprintf(output, "\n-------GRAPHE ORIENTE------\n\n");
        dumpList(liste_arc, output);
        fprintf(output, "\n");
    }

    //methode minimax
    if(methode[2] == 1 || methode[4] == 1){
      int indice_vainqueur = minimax(duels_mat,liste_arc, nombreCandidat, output);

      int taille = LONGMOTS;
      char *nom_vainqueur = (char *) malloc(taille*sizeof(char));
      while(strlen(tabmots.tab[0][indice_vainqueur+tabmots.offset]) > taille){
        taille *= 2;
        nom_vainqueur = (char*) realloc(nom_vainqueur, taille*sizeof(char));
      }

      copier_chaine_char(tabmots.tab[0][indice_vainqueur+tabmots.offset], nom_vainqueur);
      fprintf(output, "Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s\n", nombreCandidat, nombreVotant, nom_vainqueur);
    }

    //methode schulze
    if(methode[3] == 1 || methode[4] == 1){
      t_tab_int_dyn liste_gagnants_schulzes;
      creer_t_tab_int_dyn(&liste_gagnants_schulzes, nombreCandidat);
      liste_gagnants_schulzes = schulze(duels_mat, liste_arc, nombreCandidat, output);

      for (int i_gagnant = 0; i_gagnant < nombreCandidat; i_gagnant++) {
        if(liste_gagnants_schulzes.tab[i_gagnant] == 1){

          int taille = LONGMOTS;
          char *nom_vainqueur = (char *) malloc(taille*sizeof(char));
          while(strlen(tabmots.tab[0][i_gagnant+tabmots.offset]) > taille){
            taille *= 2;
            nom_vainqueur = (char*) realloc(nom_vainqueur, taille*sizeof(char));
          }

          copier_chaine_char(tabmots.tab[0][i_gagnant+tabmots.offset], nom_vainqueur);
          fprintf(output, "Mode de scrutin : Condorcet schulze, %d candidats, %d votants, vainqueur = %s\n", nombreCandidat, nombreVotant, nom_vainqueur);
        }
      }
    }
  }



  if (options[2] == 1)
    fclose(output);
  return 0;
}

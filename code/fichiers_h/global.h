/// \file global.h
/// \author Vincent Dugat
/// \date august 2018
#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define NB_BALISES 4
#define NB_METHODES 5
#define OPT_I 0
#define OPT_D 1
#define OPT_O 2
#define OPT_M 3
#define OPT_H -1
#define SUCCESS 1
#define ERR -2


#define MAX 300 /// \def< longueur maximale de la ligne dans le fichier
#define MAXINT 1000 /// \def< entier max utile dans le programme
#define LONGMOTS 30 /// \def< longueur max d'une chaîne de caractères
#define NBCOLADM 3 /// \def< nb de colonnes administratives avant la colonne du premier choix
#define KO -1  /// \def< pas bon ou vide
#define OK 0 /// \def< bon
#define NBMAXOPTIONS 4 /// \def < ça parle en soi.
//
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAXI(a,b) (((a)>(b))?(a):(b))
//
/// \struct pour encapsuler des tableaux dynamiques d'entiers avec la dimension.
typedef struct s_tab_dyn{
  int * tab;
  int dim;
} t_tab_int_dyn;

typedef struct s_mat_dyn{
  int ** tab;
  int nbRows;
  int nbCol;
} t_mat_int_dyn;

/// \struct idem avec des chaînes de caractères
typedef struct s_mat_char_dyn{
  char *** tab;
  int nbRows;
  int nbCol;
  int offset;
} t_mat_char_star_dyn;

/// \struct arc pour les graphes
typedef struct s_arc_p{ /// arc pondéré = arc de préférence
  int orig;
  int dest;
  int poids;
} t_arc_p;

#include "elementliste.h"
#include "liste.h"

extern int nbCandidats;
extern int nbVotants;
extern int nbVotesNuls;

void help();
int getop(char **tab_balises, int argc, char **argv);
void affiche_resultat(FILE *outfp,char * scrutin,int nbCandidats, int nbVotants ,float score,char * vainqueur);

// // utils.c
void erreur(char *message);
int * creer_tab_int(int dim);
int ** creer_mat_int(int nbRows,int nbCol);
void affiche_tab_int(int *tab,int dim, FILE *outfp);
void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *outfp);
void init_tab_int(int *tab,int dim,int valeur);
void init_mat_int(int **mat,int nbRows,int nbCol,int valeur);
int min_borne(char * tab[],int dim,int borne);
int max_tab_indice(int *tab, int dim);
int min_tab_indice_non_j(int *tab, int dim,int j);
int som_tab_indice(int *tab, int dim);
//
void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol);
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim);
void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots);
void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *outfp);
void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *outfp);
void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *outfp);
//
// lecture_fich_csv
void read_voting_file(char * filename,char *delimiteur,t_mat_char_star_dyn *t_tabmots);
//
// traitement.c
char * code_candidat(int code,t_mat_char_star_dyn tabmots);
void scan_ligne(t_mat_char_star_dyn *tabmots,int ligne);
// void replace_value(char * tab[],int dim,int min,int cpt);
int construct_data_struct(t_mat_char_star_dyn *tabmots, t_tab_int_dyn *first_array,t_mat_int_dyn *duels_mat,FILE *outfp);
void construct_mat_duels_d(t_mat_char_star_dyn tabmots,t_mat_int_dyn *duels_mat,int nbCandidats,FILE *outfp);
//
// condorcet.c

//int condorcet_paires(liste larcs,FILE *outfp);
//
// minimax
int minimax(liste larcs, int nbSommets,FILE *outfp);
//
// utils_scrutins.c
int maxSommet(liste larcs);
//void scan_arcs(t_mat_int_dyn duels_mat,liste *larcs);
int trouveSuc(liste larcs,int sommet,int **tabVus);
bool dfs(liste larcs,int sommet,int * tabMark,int **tabVus);
int vainqueurCondorcet(liste larcs, int nbSommets);
int scoreInt(int som,liste larcs);
//
int schulze(t_mat_int_dyn duels_mat,FILE *outfp);

#endif

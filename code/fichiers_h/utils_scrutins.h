//methode de scrutins
void uninominal_un_tour(t_tab_int_dyn vote_par_candidat, t_mat_char_star_dyn tabmots,FILE *outfp);
void uninominal_deux_tours(t_tab_int_dyn vote_par_candidat, t_mat_int_dyn duels_mat, t_mat_char_star_dyn tabmots, FILE *outfp);
int minimax(t_mat_int_dyn duels_mat, liste larcs, int nbSommets,FILE *outfp);
t_tab_int_dyn schulze(t_mat_int_dyn duels_mat, liste larcs, int nbSommets, FILE *outfp);

//fontions pour aider les methodes de scrutins
t_tab_int_dyn creer_vote_par_candidat(t_mat_char_star_dyn tabmots, int nombreCandidat);
void affiche_resultat(FILE *outfp,char * scrutin,int nbCandidats, int nbVotants ,float score,char * vainqueur);
void copie_tabmots_duels_mat(t_mat_char_star_dyn tabmots, t_mat_int_dyn *duels_mat, int nbCandidats);
void creer_liste_arc_etiquette(liste *liste_arc, t_mat_int_dyn duels_mat);
int minimum_ligne(t_mat_char_star_dyn tabmots, int nombreCandidat, int i_ligne);
void creer_mat_force_du_plus_fort_chemin(t_mat_int_dyn *p, t_mat_int_dyn duels_mat);
void creer_ensemble_gagnants_potentiels(t_tab_int_dyn *ensemble_gagnants_potentiels, t_mat_int_dyn p);

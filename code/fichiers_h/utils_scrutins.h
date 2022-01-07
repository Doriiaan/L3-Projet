//methode de scrutins
void uninominal_un_tour(t_tab_int_dyn vote_par_candidat, t_mat_char_star_dyn tabmots,FILE *outfp);
void uninominal_deux_tours(t_tab_int_dyn vote_par_candidat, t_mat_int_dyn duels_mat, t_mat_char_star_dyn tabmots, FILE *outfp);


//fontions pour aider les methodes de scrutins
t_tab_int_dyn creer_vote_par_candidat(t_mat_char_star_dyn tabmots, int nombreCandidat);
void affiche_resultat(FILE *outfp,char * scrutin,int nbCandidats, int nbVotants ,float score,char * vainqueur);

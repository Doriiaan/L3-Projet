void uninominal_un_tour(t_mat_char_star_dyn tabmots,FILE *outfp);

t_tab_int_dyn creer_vote_par_candidat_candidat(t_mat_char_star_dyn tabmots, int nombreCandidat);
void affiche_resultat(FILE *outfp,char * scrutin,int nbCandidats, int nbVotants ,float score,char * vainqueur);

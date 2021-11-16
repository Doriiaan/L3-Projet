/// \brief main pour la fonction factorielle
/// \file main.c
/// \author Gérard Menvuuncodessibo
/// \date 9 octobre 2019

long fact(int n){
/// \brief Calcule la factorielle d'un nom entier positif ou nul
/// \param[in] n un entier positif ou nul
/// \return n!
/// \pre n>=0
/// \post fac(n) = n!
if (n==0)// condition d'arrêt
	return 1; // 0!
else
	return n*fact(n-1);
}

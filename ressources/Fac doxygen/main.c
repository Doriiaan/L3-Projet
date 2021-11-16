/// \brief Fonction factorielle
/// \file fac.c
/// \author Gérard Menvuuncodessibo
/// \date 9 octobre 2019
#include <stdio.h>
#include <assert.h>
#include "fac.h"

int main(){
	int N;
	printf("Envoie N <= 0 :");
	scanf("%d",&N);
	assert(N>=0);
	printf("%d! = %ld\n",N,fact(N));
	return 0;
}

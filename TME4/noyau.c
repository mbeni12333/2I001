#include <stdlib.h>
#include "noyau.h"
#include <stdio.h>
#include <string.h>

#define TMP_STR_SIZE 128



noyau_t *creer_noyau(unsigned int dim){

	noyau_t* n = (noyau_t*)malloc(sizeof(noyau_t));
	if(n){
		n->dim = dim;
		n->coeffs = (int*)malloc(sizeof(int)*dim*dim);
		if(n->coeffs){
			return n;
		}
	}
	return NULL;
}

void detruire_noyau(noyau_t *pn){
	if(pn){
		free(pn->coeffs);
		free(pn);
	}
}

noyau_t *charger_noyau(char *nom_fichier){

	FILE* fichier = fopen(nom_fichier, "r");
	int dim;
	fscanf(fichier, "%d", &dim);
	//printf("la dimension du kernel est : %d\n", dim);
	int temp;
	int i=0;
	noyau_t* kernel = creer_noyau(dim);
	//printf("Le noyau est cree avec success !! \n");
	if(kernel){
		while(fscanf(fichier, "%d", &temp) && i < dim*dim){
			//printf("le charactere actuel est : %d \n", temp);
			kernel->coeffs[i++] = temp;
		}

		//printf("I returned kernel ! \n");
		return kernel;
	}
	//printf("i returned null O.o \n");
	return NULL;
}

void afficher_noyau(noyau_t* n){

	int i=0; 
	int dim = n->dim;

	for(i = 0;i<dim*dim;i++){

		printf("%d" ,n->coeffs[i]);

		if((i+1)%dim == 0){
			printf("\n");
		}else{
			printf(" ");
		}
	}
}

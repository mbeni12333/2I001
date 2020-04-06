#include "utilitaires_tableaux.h"
#include <stdlib.h>
#include <stdio.h>

int* copier_tab2(int* tSource, int i, int j){
	int* dest = (int*)malloc(sizeof(j-i));
	int k = 0;
	for(k = 0; k <= j-i; k++){
		dest[k] = tSource[i+k];
	}
	return dest;
}

void copier_tab3(int* tabGrand, int* tabPetit, int i, int j){
	int k = 0;
	for(k = 0; k <= j-i; k++){
		tabGrand[k+i] = tabPetit[k];
	}
}

void triRapide(int tab[], int n) {
	int pivot = (int)n/2;

	int pmin = 0; 
	int pmax = n-1;
	int pactif = pmin;

	if(n == 0 || n == 1){return;}
	// creation de deux sous tableau inferieur et superieur pivot
	while(pmax > pmin){
		if(pactif <= pivot){
			if(tab[pactif] >= tab[pivot]){
				pactif = pmax;
			}else{
				pmin += 1;
				pactif = pmin;
			}
		}else{
			if(tab[pactif] <= tab[pivot]){
				echanger_elem_tab(tab, pmin, pmax);
				pmax -= 1;
				pactif = pmin;
			}else{
				pmax -= 1;
				pactif = pmax;
			}
		}

	}

	int* t1 = copier_tab2(tab, 0, pivot-1);
	int* t2 = copier_tab2(tab, pivot+1, n);

	triRapide(t1, pivot-1);
	triRapide(t2, n-pivot-2);

	copier_tab3(tab, t1, 0, pivot-1);
	copier_tab3(tab, t2, pivot+1, n-1);
	
	free(t1);
	free(t2);

}

	





int partitionner(int tab[], int s, int n){
      int p = 0;


      return p;
}

void triRapideAmeliore(int tab[], int s, int n){

}

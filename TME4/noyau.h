#ifndef NOYAU_
#define NOYAU_

#define NOY(noy,i,j) (noy)->coeffs[(i)*noy->dim + j]

typedef struct{

	unsigned int dim;
	int *coeffs;

} noyau_t;



noyau_t *creer_noyau(unsigned int dim);

void detruire_noyau(noyau_t *pn);

noyau_t *charger_noyau(char *nom_fic);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "noyau.h"
#include "trans_image.h"
#include "tri_rapide.h"
#include <math.h>
void triBulleAmeliore(int tab[], int n){
    int i, j = 0;
    int isSoreted = 1;
    for(i = 0; i < n-1; ++i){
        isSoreted = 1;
        for(j = 0; j < n-1-i; ++j){
            if(tab[j+1] < tab[j]){
                echanger_elem_tab(tab, j, j+1);
                isSoreted = 0;
            }
        }
        if(isSoreted){
            break; 
        }
    }
    return;
}
float sumof(int *t, int n){
	int i =0;
	int somme = 0;
	while(i < n){
		//printf("t[%d] = %d\n", i, t[i]);
		somme += t[i++];
		
	}
	//printf("Somme = %d\n", somme);
	if(somme){
		float coeffConv = (float)(1./somme);
		return coeffConv;
	}else{
		return 1;
	}
	
	
}
image_t *negatif(image_t *src){

	image_t* dest = copier_image(src);
	int w = dest->w, h = dest->h;
	int i, j;

	for(i=0; i<h; ++i){
		for(j=0; j<w; ++j){
			VAL(dest, i, j) = 255 - VAL(dest, i, j);
		}
	}  

	return dest;
}

image_t *rotation(image_t *src, int angle){ 
	 image_t *p = creer_image();
	 p->w=src->w;
	 p->h=src->h;
	 p->path=strdup(src->path);
	 p->buff=malloc(src->w*src->h);
	 int i,j;
	 if(angle==90){
		 p->w=src->h;
		 p->h=src->w;
		 for(i=0;i<p->h;i++){
			 for(j=0;j<p->w;j++){
				 VAL(p,i,j)=VAL(src,j,p->h-i-1);
			 }
		 }
		 return p;
	 }else if(angle==180){
		 for(i=0;i<p->h;i++){
			 for(j=0;j<p->w;j++){
				 VAL(p,i,j)=VAL(src,p->h-i,p->w-j);
			 }
		 }
		 return p;

	 }
	return NULL;
}

image_t *modifier_lumin(image_t *src, int pourcent){

	image_t* dest = copier_image(src);
	int w = dest->w;
	int h = dest->h;
	int i, j;

	for(i=0; i<h; ++i){
		for(j=0; j<w; ++j){
			VAL(dest, i, j) = (int)(VAL(dest, i, j) * pourcent/100);
			if(VAL(dest, i, j) >= 255){
				VAL(dest, i, j) = 255;
			}else if(VAL(dest, i, j) <= 0){
				VAL(dest, i, j) = 0;
			}
		}
	}  


	return dest;
}

image_t *bruiter_image(image_t *src, int pourcent){

	image_t* img = copier_image(src);
	int w = img->w;
	int h = img->h;
	int i,j;
	int temp;
	for(i=0;i<h;++i){
		for(j=0;j<w;j++){
			temp = rand()%100;
			
			if(temp<pourcent){
				VAL(img, i, j) = 255;
			}
		}
	}
	return img;
}

image_t *filtrer_median(image_t *src){


	int dim = 5;
	int w = src->w;
	int h= src->h;
	int dec = (int)(dim/2);
	int i, j;

	image_t* dest = copier_image(src);
	for(i = 0 ;i<h;i++){
		for(j = 0; j<w; j++){
			// chaque pixel
			int somme = 0;
			// 
			int med1, med2;
			int temp[21];
			int k = 0;
			int indiceI=0;
			int indiceJ=0;
			for(med1 = -dec; med1 <= dec; med1++){
				for(med2 = -dec; med2 <= dec; med2++){
					
					if(!((med1 == -dec && med2 == -dec)||
					(med1 == -dec && med2 == dec)||
					(med1 == dec && med2 == -dec)||
					(med1 == dec && med2 == dec))){
					
					indiceI = i+med1;
					indiceJ = j+med2;


					if(indiceI < 0){
						indiceI = 0;
					}else if(indiceI>= h){
						indiceI = h-1;
					}
					if(indiceJ < 0){
						indiceJ = 0;
					}else if(indiceJ >= w){
						indiceJ = w-1;
					}
						temp[k++] = (int)VAL(src, indiceI, indiceJ);
					}
				}
			}

			triBulleAmeliore(temp, 21);
			VAL(dest, i, j) = temp[10];
		}
	}

	return dest;
}

image_t *convoluer(image_t *src, noyau_t *pn){

	int dim = pn->dim;
	int w = src->w;
	int h= src->h;
	int dec = (int)(dim/2);
	int i, j;

	image_t* dest = copier_image(src);
	afficher_noyau(pn);
	float convCoeff = sumof(pn->coeffs, pn->dim*pn->dim);
	for(i = 0 ;i<h;i++){
		for(j = 0; j<w; j++){
			// chaque pixel
			int somme = 0;
			// 
			int conv1, conv2;


			for(conv1 = -dec; conv1 <= dec; conv1++){
				for(conv2 = -dec; conv2 <= dec; conv2++){
					
					if(i+(conv1) < h && i+conv1 >=0){
						if(j+conv2 < w && j+conv2 >= 0){
							somme += VAL(src, i+conv1, j+conv2)*NOY(pn, conv1+dec, conv2+dec);
						}else{
							int indiceJ = j < w-j ? 0:w-1;
							somme += VAL(src, i+conv1, indiceJ)*NOY(pn, conv1+dec, conv2+dec);
						}
					}else{
						int indiceI = i < h-i ? 0:h-1;
						if(j+conv2 < w && j+conv2 >= 0){
							somme += VAL(src, indiceI, j+conv2)*NOY(pn, conv1+dec, conv2+dec);
						}else{
							int indiceJ = j < j-w ? 0:w-1;
							somme += VAL(src, indiceI, indiceJ)*NOY(pn, conv1+dec, conv2+dec);
						}
					}
				}
			}

			if(somme*convCoeff <= 255){
				VAL(dest, i, j) = abs((int)(somme*convCoeff));
				//printf("truc = %f es ce aue c'est egale a l'autre truc ? : %d \n", somme*convCoeff, abs((int)(somme*convCoeff)) == VAL(src, i, j));
			}else{	
				VAL(dest, i, j) = 255;	
			}
			//printf("pixel i = %d, j = %d, : %hhu \n", i, j, VAL(dest, i, j));
		}
	}

	return dest;
}

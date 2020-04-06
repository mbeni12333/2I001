#include<stdlib.h>
#include<string.h>
#include "image.h"

image_t *creer_image(){
// commentaire
		image_t* p;
		p = malloc(sizeof (image_t));
		p->w=0;
		p->h=0;
		p->path=NULL;
		p->buff=NULL;
	return p;
}

image_t *copier_image(image_t *src){

		image_t* p = creer_image();
		p->w = src->w;
		p->h = src->h;
		p->path = strdup(src->path);
		p->buff = malloc(sizeof (unsigned char)*(src->w*src->h));
		memcpy(p->buff,src->buff, sizeof (unsigned char)*(src->w*src->h));

	return p;
}

void detruire_image(image_t *p){
	if(p){
		free(p->path);
		free(p->buff);
		free(p);
	}
	return;
}

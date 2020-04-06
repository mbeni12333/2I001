#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "image.h"
#define TMP_STR_SIZE 256



char* sauter_commentaires(FILE* fichier, char *tmp_str){

	while(fgets(tmp_str, TMP_STR_SIZE, fichier) && tmp_str[0] == '#');

	return tmp_str;
}

image_t *charger_image_pgm(char *nom_fichier){
	

	FILE *fichier; // pointeur vers le fichier;
	unsigned int nb_niveaux_gris ;
	char tmp_str[TMP_STR_SIZE];
	//enum format {BIN, ASCII} pgm_form;

	// creation de l'image
	image_t* p = creer_image();
	p->path = strdup(nom_fichier);
	// ouverture du fichier
	fichier = fopen(nom_fichier, "r");
	if(!fichier){
		fprintf(stderr, "Erreur fichier innexistant");
		detruire_image(p);
		fclose(fichier);
		return NULL;
	}
	// lecture de la premiere ligne du fichier
	fgets(tmp_str, TMP_STR_SIZE, fichier);

	if(!strncmp(tmp_str, "P2",2)){
		// traitement pour le format ASCII
		//pgm_form = ASCII;

		sauter_commentaires(fichier, tmp_str);

		// lecture de W et H
		if(sscanf(tmp_str, "%lu %lu\n", &(p->w), &(p->h)) != 2){
			fprintf(stderr, "Erreur de lecture W = %lu, H = %lu", p->w, p->h);
			detruire_image(p);
			fclose(fichier);
			return NULL;			
		}
	

		sauter_commentaires(fichier, tmp_str);

		// lecture du niveaux de gris

		if(sscanf(tmp_str, "%u", &nb_niveaux_gris) == 1){
			if(nb_niveaux_gris != 255){
				fprintf(stderr, "Erreur niveau gris non supportee");
				detruire_image(p);
				fclose(fichier);
				return NULL;
			}

		}else{
			fprintf(stderr, "Erreur lecture de niveaux_gris");
			detruire_image(p);
			fclose(fichier);
			return NULL;
		}
		// tout marche bien , on commence par lire les valeur des pixels
		int i, j;
		// allocation del'espace necessaire
		p->buff = (unsigned char*)malloc(sizeof(unsigned char)*p->w*p->h);

		if(!p->buff){
			fprintf(stderr, "Erreur d'allocation de buffer");
			detruire_image(p);
			fclose(fichier);
			return NULL;
		}
		// lecture des pixels
		for(i = 0; i < p->h;i++){
			for(j = 0; j < p->w; j++){
				fscanf(fichier, " %hhu ", &VAL(p, i, j));
			}
		}

		fclose(fichier);

	}else if(!strncmp(tmp_str, "P5", 2)){
		// traitement format binaire
		//pgm_form = BIN;
sauter_commentaires(fichier, tmp_str);

		// lecture de W et H
		if(sscanf(tmp_str, "%lu %lu\n", &(p->w), &(p->h)) != 2){
			fprintf(stderr, "Erreur de lecture W = %lu, H = %lu", p->w, p->h);
			detruire_image(p);
			fclose(fichier);
			return NULL;			
		}
	

		sauter_commentaires(fichier, tmp_str);

		// lecture du niveaux de gris

		if(sscanf(tmp_str, "%u", &nb_niveaux_gris) == 1){
			if(nb_niveaux_gris != 255){
				fprintf(stderr, "Erreur niveau gris non supportee");
				detruire_image(p);
				fclose(fichier);
				return NULL;
			}

		}else{
			fprintf(stderr, "Erreur lecture de niveaux_gris");
			detruire_image(p);
			fclose(fichier);
			return NULL;
		}
		// tout marche bien , on commence par lire les valeur des pixels

		// allocation del'espace necessaire
		p->buff = (unsigned char*)malloc(sizeof(unsigned char)*p->w*p->h);

		if(!p->buff){
			fprintf(stderr, "Erreur d'allocation de buffer");
			detruire_image(p);
			fclose(fichier);
			return NULL;
		}
		// lecture des pixels
		fread(p->buff, sizeof(unsigned), p->w*p->h, fichier);

		fclose(fichier);


	}else{

		fprintf(stderr, "Erreur enum format ");
		detruire_image(p);
		fclose(fichier);
		return NULL;

	}

	return p;
}

int sauver_image_pgm(char *nom_fichier, image_t *img){

	FILE* fichier = fopen(nom_fichier, "w");

	fprintf(fichier, "P2\n");
	fprintf(fichier, "%lu %lu\n", img->w, img->h);
	fprintf(fichier, "%u\n", 255);
	int i,j;
	for(i = 0; i < img->h; i++){
		for(j = 0; j < img->w -1 ; j++){
			fprintf(fichier, "%hhu " , VAL(img, i, j));
		}
		fprintf(fichier, "%hhu\n" , VAL(img, i, j));	
	}
	fclose(fichier);

	return 1;
}

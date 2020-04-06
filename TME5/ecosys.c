
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* Pour utiliser la correction automatique:
cavecorrector 6-7 repertoire
 */

Animal *creer_animal(int x, int y, float energie) {

  // Allocation de la memoire
  Animal* node = (Animal*)malloc(sizeof(Animal));
  // initialization 
  node->x = x;
  node->y = y;
  node->energie = energie;
  node->precedent = NULL;
  node->suivant = NULL;
  node->dir[0] = (rand()%3-1);
  node->dir[1] = (rand()%3-1);

  return node;
} 

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  
  if(liste){

    if(animal){
      animal->suivant = liste;
      animal->precedent = NULL;
      liste->precedent = animal;
      liste = animal;
    }
  }

  return animal;
}

void ajouter_animal(int x, int y, Animal **liste_animal) {
  
  if(*liste_animal){
    *liste_animal = ajouter_en_tete_animal(*liste_animal, creer_animal(x, y, energie));
  }else{
    *liste_animal = creer_animal(x, y, energie);
  } 
}


void enlever_animal(Animal **liste, Animal *animal) {

  /* a completer */
  if(!liste){
    return;
  }
  if(*liste){
    if(animal){

      if(animal == *liste){

        *liste = (*liste)->suivant;

        if(*liste){
          (*liste)->precedent = NULL;
        }

        free(animal);

        return;

      }else if(animal->suivant){

        animal->suivant->precedent = animal->precedent;
        animal->precedent->suivant = animal->suivant;

        free(animal);
        return; 
      }else{

        animal->precedent->suivant = animal->suivant;

        free(animal);
        return; 
      }
    }
  }
}

unsigned int compte_animal_rec(Animal *la) {

  if(!la){
    return 0;
  }

  return 1+compte_animal_rec(la->suivant);
}

unsigned int compte_animal_it(Animal *la) {
  unsigned int compteur = 0;

  while(la){
    la = la->suivant;
    compteur++;
  }

  return compteur;
}

void bouger_animaux(Animal *la) {
  /* a completer */

  while(la){

    // mouvement de l'animal
    la->x = (la->x + la->dir[0] + SIZE_X)%SIZE_X;

    la->y = (la->y + la->dir[1] + SIZE_Y)%SIZE_Y;
    
   
    float n = rand()/(float)RAND_MAX;
    
    if(n <= p_ch_dir){

      la->dir[0] = rand()%3 - 1;
      la->dir[1] = rand()%3 - 1;

      //printf("dir 0 = %d,  dir1 = %d", la->dir[0], la->dir)
    }
    la = la->suivant;
  }
}

void reproduce(Animal **liste_animal) {

  if(!liste_animal){
    return;
  }
  if(*liste_animal){

    Animal* tmp = *liste_animal;

    while(tmp){
      float produce = rand()/(float)RAND_MAX;

      if(produce <= p_reproduce){
        ajouter_animal(tmp->x, tmp->y, liste_animal);
      }

      tmp = tmp->suivant;

    }
  }
}

void rafraichir_proies(Animal **liste_proie) {

  if(!liste_proie){
    return;
  }
   bouger_animaux(*liste_proie);
  if(*liste_proie){

    Animal* tmp = *liste_proie;
    Animal* copy = NULL;

   


    while(tmp){

      tmp->energie -= d_proie;

      if(tmp->energie <= 0){
        enlever_animal(liste_proie, tmp);
      }

      tmp = tmp->suivant;
    }

    reproduce(liste_proie);

  }
}

Animal *animal_en_XY(Animal *l, int x, int y) {


    while(l){
      if(l->x == x && l->y == y){
        return l;
      }
      l = l->suivant;
    }

  return NULL;
} 

void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  /* a completer */
  if(!liste_predateur){
    return;
  }
  if(*liste_predateur){

    Animal* tmp = *liste_predateur;
    Animal* copy = NULL;
    bouger_animaux(tmp);

    float eat = 0.f;
    while(tmp){


      tmp->energie -= d_predateur;

      if(tmp->energie <= 0){

        enlever_animal(liste_predateur, tmp->precedent);

      }

      Animal* proie_xy = animal_en_XY(*liste_proie, tmp->x, tmp->y);

      if(proie_xy){
        eat = rand()/(float)RAND_MAX;

        if(eat < p_manger){
          tmp->energie += proie_xy->energie;
          enlever_animal(liste_proie, proie_xy);
        }

      }

        tmp = tmp->suivant;

    }

    reproduce(liste_predateur);
  }

}

void afficher_ecosys(Animal *liste_proie,Animal *liste_predateur) {
  int i, j;


  Animal* proie_temp = NULL;
  Animal* predateur_temp = NULL;

  for(i=0; i<SIZE_X; i++){
    for(j=0; j<SIZE_Y; j++){

      proie_temp = animal_en_XY(liste_proie, i, j);
      predateur_temp = animal_en_XY(liste_predateur, i, j);
      

      if(proie_temp && predateur_temp){
        printf(" @ ");
      }else if(proie_temp){
        printf(" 0 ");
      }else if(predateur_temp){
        printf(" * ");
      }else{
        printf(" . ");
      }
    }
    printf("\n");
  }

}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

#include "ecosys.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_PROIES 20
#define NB_PREDATEURS 20

  /* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float d_proie=1;
float d_predateur=1;
float p_manger=0.2;
float p_reproduce=0.01;
float energie=50;


int main(void) {

  srand(time(NULL));
  int i;
  Animal* proie = NULL;
  Animal* predateur = NULL;

  for(i=0; i<NB_PROIES; i++){
    proie = ajouter_en_tete_animal(proie, creer_animal(rand()%SIZE_X, rand()%SIZE_Y, energie));
  }

  for(i=0; i<NB_PREDATEURS; i++){
    predateur = ajouter_en_tete_animal(predateur, creer_animal(rand()%SIZE_X, rand()%SIZE_Y, energie));
  }

  /* a completer */
  while(1){
      rafraichir_predateurs(&predateur, &proie);
      rafraichir_proies(&proie);
      afficher_ecosys(proie, predateur);
      printf("===================================================\n");
      usleep(1000000);
  }


  return 0;
}

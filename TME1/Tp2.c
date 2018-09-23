#include <stdlib.h>
#include <stdio.h>

// DIMENSION
#define DIM 8
// PALETTE
char p[] = {' ', '*', 'M','O'};



void ligne(){
	/*
		Cette fonction affiche la partie haute et basse du cadre du
		Labyrinth
	*/
    printf("+");
    int i=0;
    while(i < DIM){
        printf("-");
        i++;
    }
    printf("+\n");
}

void afficher_lab(int lab[DIM][DIM], char palette[]){
	/*
		Cette fonction affiche labyrinth.

		lab: tableau 2D de taille DIM*DIM contenant des
			valeur 0(chemin libre), 1(chemin blocké)
		palette: tableau contenant les symboles utilise 
			dans l'affichage de la labytinth

	*/

    int i, j;


    ligne();
    for(i=0; i<DIM;i++){
        printf("|");
        for(j=0; j<DIM;j++){
            printf("%c",palette[lab[i][j]]); 
        }
        printf("|\n");
    }
    ligne();
}
int chercherChemin(int tab[DIM][DIM]){
    return chercher_chemin_rec(tab,0,0);
}

int chercher_chemin_rec(int lab[DIM][DIM],int lc,int cc){
    if(lc < 0 || cc < 0 || lc >= DIM || cc >= DIM) {
        return 0;
    }
    
    if((lc == DIM-1 ) && (cc == DIM-1)){
        lab[lc][cc] = 2;
        return 1;
    }
    if(lab[lc][cc] != 0){
        return 0;
    }

    lab[lc][cc] = 2;
    int cheminExiste = chercher_chemin_rec(lab, lc-1, cc) ||
      				   chercher_chemin_rec(lab, lc+1, cc) ||
        			   chercher_chemin_rec(lab, lc, cc-1) ||
         			   chercher_chemin_rec(lab, lc, cc+1);

    if(!cheminExiste)lab[lc][cc] = 3;
    return cheminExiste;

}
int main(){
	// test case 
    int t[DIM][DIM] = {{0,0,1,0,0,0,1,1},
                       {1,0,0,1,1,0,1,0},
                       {1,0,0,1,1,0,0,0},
                       {1,1,0,0,0,0,1,1},
                       {0,1,1,1,0,0,0,1},
                       {0,0,0,1,1,1,0,1},
                       {1,1,1,1,0,1,0,1},
                       {1,0,1,1,0,0,0,0}};
    afficher_lab(t, p);
    printf("\n%d\n", chercherChemin(t));
    afficher_lab(t, p);

    return 0;
}
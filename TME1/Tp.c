#include <stdlib.h>
#include <stdio.h>

void printNombres(int N){
    int i;
    for(i=0; i<N; i++){
        printf("%d\n", i);
    }

}

int main(){

    int n;
    printf("Entrez un nombre : ");
    scanf("%d", &n);
    printNombres(n);

    return 0;
}
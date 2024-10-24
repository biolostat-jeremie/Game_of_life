#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int creer_tableau() {
        int** grille = (int**)malloc(sizeof(int*)*30);
    if (grille == NULL) {
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<50; i++) {
        grille[i] = (int*)malloc(sizeof(int)*50);
    }
    int m,n;
    char morte = 'O';
    for(m = 0; m < 30; m++) {
        for(n = 0; n <50; n++) {
            grille[m][n] = morte;
            printf("%c", grille[m][n]);
        }
        printf("\n");
}

}

int main(int argc, char **argv){
    printf("%d",creer_tableau()); 
    return 0 ;
}


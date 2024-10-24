#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int creer_tableau() {
        int** grille = (int**)malloc(sizeof(int*)*50);
    if (grille == NULL) {
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<50; i++) {
        grille[i] = (int*)malloc(sizeof(int)*30);
    }
    return grille[0][0] ;
}

int main(int argc, char **argv){
    printf("hello");
    return 0 ;
}


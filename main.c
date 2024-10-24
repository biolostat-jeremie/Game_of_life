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
    int m,n;
    for(m = 0; m < 50; m++) {
        for(n = 0; n <30; n++) {
            printf("%d",0);
        }
        printf("\n");
}

}

int main(int argc, char **argv){
    printf("%d",creer_tableau()); 
    return 0 ;
}


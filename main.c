#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define H 30

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


int grilleij(int (*grille)[H], int i , int j){
    int* ligne = grille [i];
    return ligne [j];
    } 


int nb_voisin(int (*grille)[H] , int  m , int n ,int i ,int j){
if (i != 0 && i != n && j != 0 && j!=m){
  return grilleij(grille, i-1 , j-1 ) + grilleij(grille, i-1 , j ) + grilleij(grille, i-1 , j+1 )+ 
         grilleij(grille, i , j-1 )   + grilleij(grille, i , j+1 )+
         grilleij(grille, i+1 , j-1 ) + grilleij(grille, i+1 , j ) + grilleij(grille, i+1 , j+1 );
         }
else if (i==0){
  return grilleij(grille, i , j-1 )   + grilleij(grille, i , j+1 ) +
         grilleij(grille, i+1 , j-1 ) + grilleij(grille, i+1 , j ) + grilleij(grille, i+1 , j+1 );
}
else if (i==n){
  return  grilleij(grille, i-1 , j-1 ) + grilleij(grille, i-1 , j ) + grilleij(grille, i-1 , j+1 )+ 
          grilleij(grille, i , j-1 )   + grilleij(grille, i , j+1 );
}
else if (j==0){
    return grilleij(grille, i-1 , j ) + grilleij(grille, i-1 , j+1 ) +
           grilleij(grille, i , j-1 ) + grilleij(grille, i , j+1 ) +
           grilleij(grille, i+1 , j ) + grilleij(grille, i+1 , j+1 );
}
else if (j==m){
  return grilleij(grille, i-1 , j-1 ) + grilleij(grille, i-1 , j ) +
         grilleij(grille, i , j-1 )+   
         grilleij(grille, i+1 , j-1 ) + grilleij(grille, i+1 , j ) ;
}
else {
  return 0;
}
}

}

int main(int argc, char **argv){
    printf("%d",creer_tableau()); 
    return 0 ;
}


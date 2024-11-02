#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define H 30

int creer_tableau() {
        int** grille = (int**)malloc(sizeof(int*)*30);
    if (grille == NULL) {
        exit(EXIT_FAILURE);
        free(grille);
    }
    for(int i=0; i<50; i++) {
        grille[i] = (int*)malloc(sizeof(int)*50);
        if (grille[i]){
        exit(EXIT_FAILURE);
        free (grille[i]);
        }
    }
    int nb_cellules;
    printf("Combien de cellules voulez vous modifier ?");
    scanf("%d",&nb_cellules);
    for (int i=0; i<nb_cellules;i++) {
        int x,y;
        printf("Coordonnées de la cellule à modifier");
        scanf("%d","%d",&x,&y);
    int m,n;
    for(m = 0; m < 30; m++) {
        for(n = 0; n <50; n++) {
            if (m!=x || n!=x) {
            grille[m][n] = 'O';
            }
            else {
                grille[m][n] = 'V';
            }
            printf("%c", grille[m][n]);
        }
        printf("\n");
}

}

}
int grilleij(int (*grille)[H], int i , int j) {
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

/*
int generation_k(int** matrice, int m, int n, int k) {
    for (int a = 0; a < k; a++) {
        for (int b = 0; b<m; b++){
            for (int c = 0; c<n; b++){
                if (nb_voisin((*matrice)[H],30,50,b,c) > 3 ) {
                    matrice[b][c]='O';
                }
                else if (nb_voisin(*matrice[H],30,50,b,c) ==3 ) {
                    matrice[b][c] = 'V';
                }
                else if (nb_voisin(*matrice[H],30,50,b,c) == 2 && matrice[b][c] == 'V') {
                    matrice[b][c] = 'V';
                }
                else {
                    matrice[b][c] = 'O';
                }
            } 
        }

    }

}
*/
int main(int argc, char **argv){
    creer_tableau();
    return 0 ;
}


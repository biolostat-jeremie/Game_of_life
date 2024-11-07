#include "main.h"

int** creer_tableau(int H , int L) {
        int** grille = (int**)malloc(sizeof(int*)*H);
    if (grille == NULL) {
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<H; i++) {
        grille[i] = (int*)malloc(sizeof(int)*L);
        if (grille[i] == NULL){
        for(int j ; j < i ; j++){
            free (grille[j]);
        }
        exit(EXIT_FAILURE);
        }
    }
return grille ;
}

void free_tableau(int **grille , int H ){
for (int i =0; i < H ; i++){
        free (grille[i]); 
    }
    free (grille) ; 
}

void afficher_tableau (int **grille , int H , int L){
    printf("\e[2J");
    int m,n;
    for(m = 0; m < H; m++) {
            for(n = 0; n <L; n++) {
                if (grille[m][n]==1){
                    printf("█");
                }
                else{
                    printf("▒");
                }    

            }
            printf("\n");
} 
}

int** init_grille(int** grille , int H , int L){     
    int i,j;
    for (i=0 ; i<H ; i++){
        for(j=0 ; j<L ; j++){
            grille[i][j]=0;
        }
    }
    int nb_cellules;
    printf("Combien de cellules voulez vous modifier ?\n");
    scanf("%d",&nb_cellules);
    for (int i=0; i<nb_cellules;i++) {
        int x,y;
        afficher_tableau(grille ,H, L);
        printf("Coordonnées de la cellule à modifier au format x,y\n");
        scanf("%d,%d",&x,&y);
        grille[x][y] = 1;    
        afficher_tableau(grille ,H, L);
    }
    return grille ;
}

int nb_voisins(int** matrice, int H, int L, int i, int j) {
    int acc = 0;
    for (int a = -1; a <= 1; a++) {
        for (int b = -1; b <= 1; b++) {
            int ligne = i + a;
            int col = j + b;
            if (!(a == 0 && b == 0) && ligne >= 0 && ligne < H && col >= 0 && col < L) {
                if (matrice[ligne][col] ==1){ 
                    acc++;
                }
            }
        }
    }

    return acc;
}

void generation_suivante (int** matrice_in,int** matrice_out, int H, int L){
    for (int b = 0; b<H; b++){
        for (int c = 0; c<L; c++){
            if (nb_voisins(matrice_in ,H,L,b,c) > 3 ) {
                matrice_out[b][c]= 0;
            }
            else if (nb_voisins(matrice_in,H,L,b,c) ==3 ) {
                matrice_out[b][c] = 1;
            }
            else if (nb_voisins(matrice_in,H,L,b,c) == 2 && matrice_in[b][c] == 1) {
                matrice_out[b][c] = 1;
            }
            else {
                matrice_out[b][c] = 0;
            }
        } 

    }

}



//attend ms milliseconde
int        td_wait(long    ms)
{

    //nanosleep accept un struct en seconds et nanosecondes
    //on convertit donc l'entrée
    struct timespec ts;
    ts.tv_sec  = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    return nanosleep(&ts, &ts);

}


int main(){
    
    //Detecte la taille du terminal 
    struct winsize raw_termsize;
    ioctl(0, TIOCGWINSZ, &raw_termsize);
    int termsize_col    = raw_termsize.ws_col;
    int termsize_row    = raw_termsize.ws_row;

    printf("Indiquer la taille du tableau au format Longeur,Largeur : \n"
    "(Taille maximale conseillée : %d,%d)", termsize_row-1 , termsize_col);
    int H , L;
    scanf("%d,%d" , &H ,&L);
    int **grille1 = creer_tableau(H ,L );
    init_grille(grille1 , H , L );
    int **grille2 = creer_tableau (H , L);
    int k ;
    printf ("Combien de générations ?\n");
    scanf ("%d",&k);
    printf ("Nombre de miliseconde entre chaque génération ?");
    int delay;
    scanf("%d", &delay); 

    for (int i = 0 ; i<k ; i++ ){
        generation_suivante(grille1 , grille2 , H , L);
        int **temp = grille1;
        grille1 = grille2;
        grille2 = temp;
        td_wait(delay);
        afficher_tableau(grille1,H,L);
    }

    free_tableau(grille1 ,H);
    free_tableau(grille2 ,H);
    
    return 0 ;
}



#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

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




struct termios orig_term_settings;
int termsize_col,termsize_row;

#define OUT_BUF_SIZE 100
char stdout_buffer[OUT_BUF_SIZE];

void    graphical_cleanup(void)
{
    //appellé a la sortie, responsable de clean les graphisme et de restaurer le terminal

    //restore les attributs du terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_term_settings);
    //réaffiche le curseur, et reset la couleur d'affichage au valeur par défault
    printf("%s", "\33[H \33[?25h \33[0m \33[2J \e[?1003l");
}

void    init_graphical(void)
{
    //mets en place les graphismes
	
    //mets en place le buffering
    setvbuf(stdout, stdout_buffer, _IOFBF, OUT_BUF_SIZE);
    //cache le curseur
    printf("%s", "\33[?25l");
    //obtention de la taille de l'écran
    struct winsize raw_termsize;
    ioctl(0, TIOCGWINSZ, &raw_termsize);
    termsize_col    = raw_termsize.ws_col;
    termsize_row    = raw_termsize.ws_row;

    //setup du terminal sur linux
    #if __unix__
    //sauvegarde les attributs terminal (pour restauration future) et mets le term en raw mode
    //Voir http://manpagesfr.free.fr/man/man3/termios.3.html pour plus de détails
    tcgetattr(STDIN_FILENO, &orig_term_settings);
    struct termios raw = orig_term_settings;
    raw.c_lflag   &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    raw.c_iflag   &= ~( IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    raw.c_oflag   &= ~(OPOST);
    raw.c_cflag   &= ~(CSIZE | PARENB);
    raw.c_cflag   |= CS8;

	//VTIME et VMIN permettent a scanf (read) de retourner instantanément 0 si l'utilisateur n'a rien rentré
	//et de fonctionner normalement sinon
    raw.c_cc[VMIN] = 1; raw.c_cc[VTIME] = 1;
    //applique tout les changements
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    #else
        #error  "non POSIX system unsupported"
    #endif //SYSTEM_POSIX

    //set la langue a rien, pour que certaint settings de langue bizarre
	//(ex langue de droite a gauche) n'influent pas sur le programme
    setlocale(LC_ALL, "");
    printf("\e[?1003h\e[?1015h\e[?1006h");
    fflush(stdout);
}

void clear_input(){
    scanf("%*[^\e]");
}





int main(){
    
    printf("Indiquer la taille du tableau au format Longeur,Largeur : \n");
    int H , L;
    scanf("%d,%d" , &H ,&L);
    int **grille1 = creer_tableau(H ,L );
    init_grille(grille1 , H , L );
    int **grille2 = creer_tableau (H , L);
    int k ;
    printf ("Combien de générations ?\n");
    scanf ("%d",&k);

    for (int i = 0 ; i<k ; i++ ){
        generation_suivante(grille1 , grille2 , H , L);
        int **temp = grille1;
        grille1 = grille2;
        grille2 = temp;
        sleep(1);
        afficher_tableau(grille1,H,L);
    }

    free_tableau(grille1 ,H);
    free_tableau(grille2 ,H);
    
   
    int x,y,btn;
    bool up;
    init_graphical();
    
    char c=0;
    while(c!='m'){
        x=0;
        y=0;
        btn=0;
        int num_read=0;
        num_read = scanf("\e[<%i;%i;%i%c",&btn,&x,&y,&c);
        if (num_read!=4){
            fflush(stdout);
            clear_input();
            continue;
        }
        up=(c=='m');
        printf("\n\rbtn:%i x:%i y:%i up:%i",btn,x,y,up);
        fflush(stdout);
        c=0;
    }
    
    graphical_cleanup();
    return 0 ;
}

//gcc -o main -std=c99 -Wall -Wextra -Wvla -fsanitize=address,undefined -O0 -g main.c 

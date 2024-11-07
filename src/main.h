#define _POSIX_C_SOURCE 199309L //sinon, nanosleep n'est pas définie (et usleep non plus)
                                //(et je ne comprends pas quelle fonction on devrait utiliser)

#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <time.h>

void afficher_tableau (int **grille , int H , int L);
int nb_voisins(int** matrice, int H, int L, int i, int j);
int** creer_tableau(int H , int L);
void free_tableau(int **grille , int H );
void afficher_tableau (int **grille , int H , int L);
int** init_grille(int** grille , int H , int L);
int nb_voisins(int** matrice, int H, int L, int i, int j);
void generation_suivante (int** matrice_in,int** matrice_out, int H, int L);
int td_wait(long ms);
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


int** creer_tableau(int H , int L);

//la fonction prend en paramètre le nombre de ligne et de colonnes du tableau et renvoie un pointeur vers
//un tableau de pointeur
//On vérifie que le malloc n’aie pas échoué

void free_tableau(int **grille , int H );

//Fonction qui libère la mémoire alloué aux pointeurs, appelée à la fin du programme

void afficher_tableau (int **grille , int H , int L);

// Fonction qui affiche le tableau en fonction de la valeur associée a chacune des cellules – 0 pour morte 1
//pour vivante – avec des caractères de la table ASCII

int** init_grille(int** grille , int H , int L);

// Fonction qui associe des 0 et des 1 aux cellules de la grille en fonction de l’état que veut leur attribuer
//l’utilisateur

int nb_voisins(int** matrice, int H, int L, int i, int j);

//Fonction qui prend en paramètre une cellule et qui renvoie le nombre de voisins vivants de celle-ci

void generation_suivante (int** matrice_in,int** matrice_out, int H, int L);

//Fonction qui prend en parramètre deux tableau de tableau et leur taille et qui renvoie l'évolution du premier 
// tableau par les règles du jeu de la vie de Conway 

int td_wait(long ms);

//Déclare une structure et l'utilise pour attendre un certain nombre de milisecondes 
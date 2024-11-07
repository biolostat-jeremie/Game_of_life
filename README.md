# Game_of_life

Le projet que nous avons préparé est un jeu de la vie. Initialement imaginé par le mathématicien John
Conway, le jeu de la vie est un automate cellulaire, un modèle ou chaque état conduit mécaniquement à
l’état suivant à partir de règles préétablies, évoluant sur une matrice de dimension 2 théoriquement infinie
(ce ne sera pas le cas ici pour des raisons évidentes). Chaque case de la grille est une cellule pouvant être
morte ou vivante et dont l’état évolue à chaque génération.

Voici les règles appliquées à chaque génération du jeu de la vie de Conway :
- Si nb_voisins_vivants = 2 et cellule = vivante : cellule → vivante
- Si nb_voisins_vivants = 3 : cellule → vivante
-Sinon : cellule → morte


Cependant il existe des variantes au jeu de la vie de Conway qui prennent des règles différentes, ou
introduisent un espace différent sur lequel évoluent les cellules
Notre programme génère une grille de la dimension souhaitée par l’utilisateur et permet à ce dernier de
selectionner une variante du jeu de la vie parmi plusieurs choix disponibles.
L’utilisateur peut ensuite renseigner quelles cellules sont vivantes et quelles cellules sont mortes
initialement. Ensuite le programme affiche dans la console l’état de la grille à chaque génération et
s’arrête à la génération renseignée par l’utilisateur.


Pour savoir à quoi servent les différentes fonction, vous pouvez regardesz le document main.h


Pour la compilation, il vous suffit de taper la commande 

```make```

Dans votre terminal. Si vous avez besoin d'aide , vous pouvez taper : 

```make help```

Le fichier sera alors compilé

Si vous souhaitez compiler sur windows , commentez la fonction "td_wait" et remplacez la ligne précisée dans 
la fonction main() .
Vous aurez alors à attendre 1 seconde entre chaque génération, et de ce fait nous vous conseillons de compiler sur caséine 


Voiçi une commande qui rentre tous les imputs pour observer un "planeur", l'une des structures les plus importantes du jeu de la vie 

```echo "20,50                                                                          ✘ 0|127  at  20:33:58
5
12,11
12,12
12,13
11,13
11,12
500
200
" | ./main
```

Vous pouvez aussi rentré des structures de votre choix comme celle çi, qui évolue de manière carractéristique :

```echo "20,50                                                                          ✘ 0|127  at  20:33:58
5
12,11
12,12
12,13
11,13
13,12
500
200
" | ./main
```


Pour rentrez vos coordonées, faites attention au fait que la première case en haut à pour coordonées 0,0

Bonne exploration !

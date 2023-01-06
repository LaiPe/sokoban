# Sokoban

## Compilation du programme
  Notre fichier principal s'appelle main.c. Afin de pouvoir le compiler pour la première fois on doit initiaiser le sous répertoire `bin`, nous écrivons la ligne suivante:  
  `mkdir ./programme/bin`  
Ensuite, pour compiler et lancer le programme nous devons tapper le ligne:  
`gcc programme/main.c programme/affichage.c programme/partie.c -o programme/bin/prog && ./programme/bin/prog `

## Règles du jeu
Sokoban est un jeu de puzzle dans lequel le joueur doit pousser des caisses sur des cibles. Voici comment le jeu fonctionne:

  Le joueur peut se déplacer dans quatre directions: haut, bas, gauche, droite.

  Le joueur doit pousser les caisses sur les cibles, mais il ne peut pousser qu'une caisse à la fois et ne peut pas tirer une caisse.

  Les caisses ne peuvent être poussées que sur des espaces vides ou sur des cibles. Elles ne peuvent pas être poussées contre des murs ou d'autres caisses.

  Le joueur doit utiliser sa stratégie et ses habiletés de résolution de problèmes pour déplacer toutes les caisses sur les cibles dans le niveau le plus efficacement possible.

  Le jeu se termine lorsque toutes les caisses ont été déplacées sur les cibles ou lorsque le joueur abandonne.

Dans notre versions du sokoban, nous avons utiliser les caractère suivant pour symboliser les différents éléments:

- caisse = `O`
- cible = `x`
- caisse sur cible = `0`
- joueur = `P`
- mur = `#`

## Contrôles
 Afin de pouvoir se déplacer dans la direction voulu, le joueur devra taper sur les touches suivantes:
- `h` pour monter d'une case
- `b` pour descendre d'une case
- `d` pour se déplacer d'une case vers la droite
- `g` pour se déplacer d'une case vers la gauche

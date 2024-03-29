#ifndef AFFICHAGE
#define AFFICHAGE
#include "affichage.h"
#endif

#ifndef STRUCTURE
#define STRUCTURE
#include "struct.h"
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STRING
#define STRING
#include <string.h>
#endif


//FONCTION PARTIE
int obstacle(char a){
    return a=='#' || a=='0' || a=='O';
}
int partieSokoban(partie *game){
    //Variables de déplacement du personage
    int x;
    int y;
    char input[10];

    //Affichage Interface
    system("clear");
    texte_encadre(game->nom,80);
    printTerrain(game->terrain);

    //Entrée utilisateur
    printf("Entrez 'a' pour abandonner.\n");
    printf("Déplacement ? (g/h/d/b): ");
    scanf("%s", input);

    while (strcmp(input, "a") != 0 && game->puntos<game->terrain->nbCibles) {
        
        //Valeurs en fonction du déplacement indiqué par l'utilisateur
        if (strcmp(input, "h") == 0) {y=-1;x=0;}
        else if (strcmp(input, "b") == 0) {y=1;x=0;} 
        else if (strcmp(input, "g") == 0) {y=0;x=-1;} 
        else if (strcmp(input, "d") == 0) {y=0;x=1;}
        else {y=0;x=0;}

        // Regles déplacement
        if (game->terrain->data[game->perso->lign + y][game->perso->col + x] == ' ') {
            // Vers une case vide
            game->terrain->data[game->perso->lign][game->perso->col] = ' ';
            game->perso->lign += y;
            game->perso->col += x;
            game->terrain->data[game->perso->lign][game->perso->col] = 'P';

            //De plus: si le perso se trouve sur une cible
            if (game->perso->surCible){
                game->terrain->data[game->perso->lign - y][game->perso->col - x] = 'x';
                game->perso->surCible--;
            }
        }
        else if (game->terrain->data[game->perso->lign + y][game->perso->col + x] == 'O' && !(obstacle(game->terrain->data[game->perso->lign + 2*y][game->perso->col + 2*x]))){
            // Vers une caisse à pousser sans obstacle derrière
            if (game->terrain->data[game->perso->lign + 2*y][game->perso->col + 2*x] == 'x'){
                // S'il y a une cible derrière la caisse
                game->terrain->data[game->perso->lign][game->perso->col] = ' ';
                game->perso->lign += y;
                game->perso->col += x;
                game->terrain->data[game->perso->lign][game->perso->col] = 'P';
                game->terrain->data[game->perso->lign + y][game->perso->col + x] = '0';
                game->puntos++;
            }
            else{
                game->terrain->data[game->perso->lign][game->perso->col] = ' ';
                game->perso->lign += y;
                game->perso->col += x;
                game->terrain->data[game->perso->lign][game->perso->col] = 'P';
                game->terrain->data[game->perso->lign + y][game->perso->col + x] = 'O';
            }

            //De plus: si le perso se trouve sur une cible
            if (game->perso->surCible){
                game->terrain->data[game->perso->lign - y][game->perso->col - x] = 'x';
                game->perso->surCible--;
            }
        }
        else if (game->terrain->data[game->perso->lign + y][game->perso->col + x] == '0' && !(obstacle(game->terrain->data[game->perso->lign + 2*y][game->perso->col + 2*x]))){
            // Vers une caisse sur une cible (sans obstacle derrière)
            if (game->terrain->data[game->perso->lign + 2*y][game->perso->col + 2*x] == 'x'){
                // S'il y a une cible derrière la caisse
                game->terrain->data[game->perso->lign][game->perso->col] = ' ';
                game->perso->lign += y;
                game->perso->col += x;
                game->terrain->data[game->perso->lign][game->perso->col] = 'P';
                game->terrain->data[game->perso->lign + y][game->perso->col + x] = '0';

                //De plus: si le perso se trouve sur une cible
                if (game->perso->surCible){
                    game->terrain->data[game->perso->lign - y][game->perso->col - x] = 'x';
                    game->perso->surCible--;
                }
                game->perso->surCible++;
            }
            else{
                game->terrain->data[game->perso->lign][game->perso->col] = ' ';
                game->perso->lign += y;
                game->perso->col += x;
                game->terrain->data[game->perso->lign][game->perso->col] = 'P';
                game->terrain->data[game->perso->lign + y][game->perso->col + x] = 'O';
                game->puntos--;

                //De plus: si le perso se trouve sur une cible
                if (game->perso->surCible){
                    game->terrain->data[game->perso->lign - y][game->perso->col - x] = 'x';
                    game->perso->surCible--;
                }
                game->perso->surCible++;
            }
        }
        else if (game->terrain->data[game->perso->lign + y][game->perso->col + x] == 'x') {
            // Vers une cible
            game->terrain->data[game->perso->lign][game->perso->col] = ' ';
            game->perso->lign += y;
            game->perso->col += x;
            game->terrain->data[game->perso->lign][game->perso->col] = 'P';
            //De plus: si le perso se trouve sur une cible
            if (game->perso->surCible){
                game->terrain->data[game->perso->lign - y][game->perso->col - x] = 'x';
                game->perso->surCible--;
            }
            game->perso->surCible++;
        }
        //Affichage Interface
        system("clear");
        texte_encadre(game->nom,80);
        printTerrain(game->terrain);

        if(game->puntos < game->terrain->nbCibles){
            //Entrée utilisateur
            printf("Entrez 'a' pour abandonner.\n");
            printf("Déplacement ? (g/h/d/b): ");
            scanf("%s", input);
        }
    }
    //Affichage de fin
    if (game->puntos==game->terrain->nbCibles){
        afficher_ascii_art("./programme/ressources/victoire.txt");
    }
    else{
        afficher_ascii_art("./programme/ressources/defaite.txt");
    }
    printf("\n");
    printf("\n");
    for (int i=0;i<80;i++){
        printf("=");
    }
    printf("\n");
    if (game->puntos==game->terrain->nbCibles){
        printf("Incroyable, tu as gagné !\n");
    }
    else{
        printf("Malheureusement, tu as perdu !\n");
    }
    printf("Appuie sur N'IMPORTE quelle touche puis ENTRER pour retourner au menu\n");
    char random[10];
    scanf("%s", random);
}
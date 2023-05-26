#ifndef STRUCTURE
#define STRUCTURE
#include "struct.h"
#endif

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STRING
#define STRING
#include <string.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

//FONCTIONS AFFICHAGE
void afficher_ascii_art(const char *nom_fichier) {
    FILE *fp;
    int c;
    //Ouverture du fichier
    fp = fopen(nom_fichier, "r");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    //Lecture et affichage de chaque caractère 
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
    fclose(fp);
}


void texte_encadre(const char * mot, int bande){
  //Affiche une demi-bande de =
  bande=(bande-strlen(mot)-2)/2;
    for (int i=0;i<bande;i++){
        printf("=");
    }
    //Affichage du mot entre deux espace
    printf(" ");
    printf("%s",mot);
    printf(" ");
  
    //Affichage de la seconde demi-bande
    for (int i=0;i<bande;i++){
        printf("=");
    }
    printf("\n");
}

void printMenu(){
  //Clear du terminal
    system("clear");
  //Affichage du fichier sokoban.txt
    afficher_ascii_art("./programme/ressources/sokoban.txt");
    printf("\n");
    printf("\n");
  //Affichage du mot MENU entre deux bandes
    texte_encadre("MENU",80);
    printf("\t1. Jouer à la partie de test\n"); 
    //printf("\t2. Jouer au mode histoire\n");
    //printf("\t3. Jouer à une partie enregistée dans un fichier .csv\n");
    printf("\tq. Quitter\n");
    for (int i=0;i<80;i++){
        printf("=");
    }
    printf("\n");
}
void printTerrain(terrain *t){
  //Affichage de chaque caractère du terrain
    for (int i=0;i<t->nbLigns;i++){
        for (int j=0;j<t->nbCols;j++){
            printf("%c",t->data[i][j]);
        }
        printf("\n");
    }
}
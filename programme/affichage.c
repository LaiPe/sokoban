#include "affichage.h"

//FONCTIONS AFFICHAGE
void afficher_ascii_art(const char *nom_fichier) {
    FILE *fp;
    int c;
    fp = fopen(nom_fichier, "r");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
    fclose(fp);
}
void texte_encadre(const char * mot, int bande){
    bande=(bande-strlen(mot)-2)/2;
    for (int i=0;i<bande;i++){
        printf("=");
    }
    printf(" ");
    printf("%s",mot);
    printf(" ");
    for (int i=0;i<bande;i++){
        printf("=");
    }
    printf("\n");
}

void printMenu(){
    system("clear");
    afficher_ascii_art("./programme/ressources/sokoban.txt");
    printf("\n");
    printf("\n");
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
    for (int i=0;i<t->nbLigns;i++){
        for (int j=0;j<t->nbCols;j++){
            printf("%c",t->data[i][j]);
        }
        printf("\n");
    }
}
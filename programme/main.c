#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIGNS 10
#define COLS 10

char terrain[LIGNS][COLS] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', 'x', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', '0', 'O', '0', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

int nbCibles=3;

//Variables de position du personage
int persoLign= 5;
int persoCol= 5;
short int persoSurCible = 0;

//Variables de déplacement du personage
int x;
int y;

int puntos=2;

int obstacle(char a){
    return a=='#' || a=='0' || a=='O';
}

void printTerrain() {
    for (int lign = 0; lign < LIGNS; lign++) {
        for (int col = 0; col < COLS; col++) {
            printf("%c", terrain[lign][col]);
        }
        printf("\n");
    }
}

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
    printf("\t1. Jouer à la partie codée en dur\n");
    printf("\t2. Jouer au mode histoire\n");
    printf("\t3. Jouer à une partie enregistée dans un fichier .csv\n");
    printf("\tq. Quitter\n");
    for (int i=0;i<80;i++){
        printf("=");
    }
    printf("\n");
}

int main() {
    int conti=1;
    while(conti){
        fflush(stdout);
        printMenu();
        char choix[10];
        printf("Choix?(1,2,3 ou q): ");
        scanf("%s", choix);
        if (strcmp(choix, "1") == 0){
            char input[10];
            while (puntos<nbCibles) {
                //Affichage Interface
                system("clear");
                printTerrain();
                printf("puntos:%d\n",puntos);

                //Entrée utilisateur
                printf("Déplacement ? (g/h/d/b): ");
                scanf("%s", input);
                

                //Valeurs en fonction du déplacement indiqué par l'utilisateur
                if (strcmp(input, "h") == 0) {y=-1;x=0;}
                else if (strcmp(input, "b") == 0) {y=1;x=0;} 
                else if (strcmp(input, "g") == 0) {y=0;x=-1;} 
                else if (strcmp(input, "d") == 0) {y=0;x=1;}
                else {y=0;x=0;}

                // Regles déplacement
                if (terrain[persoLign + y][persoCol + x] == ' ') {
                    // Vers une case vide
                    terrain[persoLign][persoCol] = ' ';
                    persoLign += y;
                    persoCol += x;
                    terrain[persoLign][persoCol] = 'P';

                    //De plus: si le perso se trouve sur une cible
                    if (persoSurCible){
                        terrain[persoLign - y][persoCol - x] = 'x';
                        persoSurCible--;
                    }
                }
                else if (terrain[persoLign + y][persoCol + x] == 'O' && !(obstacle(terrain[persoLign + 2*y][persoCol + 2*x]))){
                    // Vers une caisse à pousser sans obstacle derrière
                    if (terrain[persoLign + 2*y][persoCol + 2*x] == 'x'){
                        // S'il y a une cible derrière la caisse
                        terrain[persoLign][persoCol] = ' ';
                        persoLign += y;
                        persoCol += x;
                        terrain[persoLign][persoCol] = 'P';
                        terrain[persoLign + y][persoCol + x] = '0';
                        puntos++;
                    }
                    else{
                        terrain[persoLign][persoCol] = ' ';
                        persoLign += y;
                        persoCol += x;
                        terrain[persoLign][persoCol] = 'P';
                        terrain[persoLign + y][persoCol + x] = 'O';
                    }

                    //De plus: si le perso se trouve sur une cible
                    if (persoSurCible){
                        terrain[persoLign - y][persoCol - x] = 'x';
                        persoSurCible--;
                    }
                }
                else if (terrain[persoLign + y][persoCol + x] == '0' && !(obstacle(terrain[persoLign + 2*y][persoCol + 2*x]))){
                    // Vers une caisse sur une cible (sans obstacle derrière)
                    if (terrain[persoLign + 2*y][persoCol + 2*x] == 'x'){
                        // S'il y a une cible derrière la caisse
                        terrain[persoLign][persoCol] = ' ';
                        persoLign += y;
                        persoCol += x;
                        terrain[persoLign][persoCol] = 'P';
                        terrain[persoLign + y][persoCol + x] = '0';

                        //De plus: si le perso se trouve sur une cible
                        if (persoSurCible){
                            terrain[persoLign - y][persoCol - x] = 'x';
                            persoSurCible--;
                        }
                        persoSurCible++;
                    }
                    else{
                        terrain[persoLign][persoCol] = ' ';
                        persoLign += y;
                        persoCol += x;
                        terrain[persoLign][persoCol] = 'P';
                        terrain[persoLign + y][persoCol + x] = 'O';
                        puntos--;

                        //De plus: si le perso se trouve sur une cible
                        if (persoSurCible){
                            terrain[persoLign - y][persoCol - x] = 'x';
                            persoSurCible--;
                        }
                        persoSurCible++;
                    }
                }
                else if (terrain[persoLign + y][persoCol + x] == 'x') {
                    // Vers une cible
                    terrain[persoLign][persoCol] = ' ';
                    persoLign += y;
                    persoCol += x;
                    terrain[persoLign][persoCol] = 'P';
                    //De plus: si le perso se trouve sur une cible
                    if (persoSurCible){
                        terrain[persoLign - y][persoCol - x] = 'x';
                        persoSurCible--;
                    }
                    persoSurCible++;
                }
            }
            //Affichage de fin
            int random;
            system("clear");
            printTerrain();
            printf("puntos:%d\n",puntos);
            printf("Incroyable, tu as gagné !\n");
            printf("Appuie sur N'IMPORTE quelle touche puis ENTRER pour retourner au menu\n");
            scanf(" ");
        }
        else if (strcmp(choix, "q") == 0){
            conti=0;
        }
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//STRUCTURE DE DONNEES
//Variables de position du personage
typedef struct perso perso;
struct perso{
int lign;
int col;
short int surCible;
};

//Variables du terrain
typedef struct terrain terrain;
struct terrain{
    char ** data;
    int nbLigns;
    int nbCols;
};

//Variables de la partie
typedef struct partie partie;
struct partie{
    terrain *carte;
    perso *perso;
    int nbCibles;
    int puntos;
    char *nom;
};

//FONCTIONS
void declaTerrain(terrain *t){
    t->data=malloc(t->nbLigns*sizeof(char*));

    //Si erreur allocation
    if (t->data==NULL){
        printf("Erreur: problème lors de l'allocation principale");
        return;
    }
    for (int i=0;i<t->nbLigns;i++){
        t->data[i]=malloc(t->nbCols*sizeof(char));

        //Si erreur allocation
        if (t->data[i]==NULL){
            printf("Erreur: problème lors de la %d-ème allocation secondaire",i);
            for (int j=0;j<i;j++){
                free(t->data[j]);
            }
            free(t->data[i]);
            return;
        }
    }
}
void initTerrainTest(terrain *t){
    for (int i=0;i<t->nbLigns;i++){
        for (int j=0;j<t->nbCols;j++){
            if (i==0 || i==t->nbLigns-1 || j==0 || j==t->nbCols-1){
                t->data[i][j]='#';
            }
            else{
                t->data[i][j]=' ';
            }
        }
    }
    t->data[1][1]='P';
    t->data[2][3]='O';
    t->data[3][5]='x';
}


int obstacle(char a){
    return a=='#' || a=='0' || a=='O';
}

void printTerrain(terrain *t){
    for (int i=0;i<t->nbLigns;i++){
        for (int j=0;j<t->nbCols;j++){
            printf("%c",t->data[i][j]);
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
    printf("\t1. Jouer à la partie de test\n");
    printf("\t2. Jouer au mode histoire\n");
    printf("\t3. Jouer à une partie enregistée dans un fichier .csv\n");
    printf("\tq. Quitter\n");
    for (int i=0;i<80;i++){
        printf("=");
    }
    printf("\n");
}

int partieSokoban(partie *game){
    //Variables de déplacement du personage
    int x;
    int y;
    char input[10];

    //Affichage Interface
    system("clear");
    texte_encadre(game->nom,80);
    printTerrain(game->carte);

    //Entrée utilisateur
    printf("Entrez 'a' pour abandonner.\n");
    printf("Déplacement ? (g/h/d/b): ");
    scanf("%s", input);

    while (strcmp(input, "a") != 0 && game->puntos<game->nbCibles) {
        
        //Valeurs en fonction du déplacement indiqué par l'utilisateur
        if (strcmp(input, "h") == 0) {y=-1;x=0;}
        else if (strcmp(input, "b") == 0) {y=1;x=0;} 
        else if (strcmp(input, "g") == 0) {y=0;x=-1;} 
        else if (strcmp(input, "d") == 0) {y=0;x=1;}
        else {y=0;x=0;}

        // Regles déplacement
        if (game->carte->data[game->perso->lign + y][game->perso->col + x] == ' ') {
            // Vers une case vide
            game->carte->data[game->perso->lign][game->perso->col] = ' ';
            game->perso->lign += y;
            game->perso->col += x;
            game->carte->data[game->perso->lign][game->perso->col] = 'P';

            //De plus: si le perso se trouve sur une cible
            if (game->perso->surCible){
                game->carte->data[game->perso->lign - y][game->perso->col - x] = 'x';
                game->perso->surCible--;
            }
        }
        else if (game->carte->data[game->perso->lign + y][game->perso->col + x] == 'O' && !(obstacle(game->carte->data[game->perso->lign + 2*y][game->perso->col + 2*x]))){
            // Vers une caisse à pousser sans obstacle derrière
            if (game->carte->data[game->perso->lign + 2*y][game->perso->col + 2*x] == 'x'){
                // S'il y a une cible derrière la caisse
                game->carte->data[game->perso->lign][game->perso->col] = ' ';
                game->perso->lign += y;
                game->perso->col += x;
                game->carte->data[game->perso->lign][game->perso->col] = 'P';
                game->carte->data[game->perso->lign + y][game->perso->col + x] = '0';
                game->puntos++;
            }
            else{
                game->carte->data[game->perso->lign][game->perso->col] = ' ';
                game->perso->lign += y;
                game->perso->col += x;
                game->carte->data[game->perso->lign][game->perso->col] = 'P';
                game->carte->data[game->perso->lign + y][game->perso->col + x] = 'O';
            }

            //De plus: si le perso se trouve sur une cible
            if (game->perso->surCible){
                game->carte->data[game->perso->lign - y][game->perso->col - x] = 'x';
                game->perso->surCible--;
            }
        }
        else if (game->carte->data[game->perso->lign + y][game->perso->col + x] == '0' && !(obstacle(game->carte->data[game->perso->lign + 2*y][game->perso->col + 2*x]))){
            // Vers une caisse sur une cible (sans obstacle derrière)
            if (game->carte->data[game->perso->lign + 2*y][game->perso->col + 2*x] == 'x'){
                // S'il y a une cible derrière la caisse
                game->carte->data[game->perso->lign][game->perso->col] = ' ';
                game->perso->lign += y;
                game->perso->col += x;
                game->carte->data[game->perso->lign][game->perso->col] = 'P';
                game->carte->data[game->perso->lign + y][game->perso->col + x] = '0';

                //De plus: si le perso se trouve sur une cible
                if (game->perso->surCible){
                    game->carte->data[game->perso->lign - y][game->perso->col - x] = 'x';
                    game->perso->surCible--;
                }
                game->perso->surCible++;
            }
            else{
                game->carte->data[game->perso->lign][game->perso->col] = ' ';
                game->perso->lign += y;
                game->perso->col += x;
                game->carte->data[game->perso->lign][game->perso->col] = 'P';
                game->carte->data[game->perso->lign + y][game->perso->col + x] = 'O';
                game->puntos--;

                //De plus: si le perso se trouve sur une cible
                if (game->perso->surCible){
                    game->carte->data[game->perso->lign - y][game->perso->col - x] = 'x';
                    game->perso->surCible--;
                }
                game->perso->surCible++;
            }
        }
        else if (game->carte->data[game->perso->lign + y][game->perso->col + x] == 'x') {
            // Vers une cible
            game->carte->data[game->perso->lign][game->perso->col] = ' ';
            game->perso->lign += y;
            game->perso->col += x;
            game->carte->data[game->perso->lign][game->perso->col] = 'P';
            //De plus: si le perso se trouve sur une cible
            if (game->perso->surCible){
                game->carte->data[game->perso->lign - y][game->perso->col - x] = 'x';
                game->perso->surCible--;
            }
            game->perso->surCible++;
        }
        //Affichage Interface
        system("clear");
        texte_encadre(game->nom,80);
        printTerrain(game->carte);

        if(game->puntos < game->nbCibles){
            //Entrée utilisateur
            printf("Entrez 'a' pour abandonner.\n");
            printf("Déplacement ? (g/h/d/b): ");
            scanf("%s", input);
        }
    }
    //Affichage de fin
    if (game->puntos==game->nbCibles){
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
    if (game->puntos==game->nbCibles){
        printf("Incroyable, tu as gagné !\n");
    }
    else{
        printf("Malheureusement, tu as perdu !\n");
    }
    printf("Appuie sur N'IMPORTE quelle touche puis ENTRER pour retourner au menu\n");
    char random[10];
    scanf("%s", random);
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
            //Initialisation de Bob
            perso * bob=malloc(sizeof(bob));
            bob->lign=1;
            bob->col=1;
            bob->surCible=0;

            //Initialisation du terrain
            terrain *t=malloc(sizeof(terrain));
            t->nbLigns=10;
            t->nbCols=10;
            declaTerrain(t);
            initTerrainTest(t);
            
            //Initialisation de la partie
            partie *partieTest=malloc(sizeof(partie));
            partieTest->perso = bob;
            partieTest->carte = t;
            partieTest->nbCibles = 1;
            partieTest->puntos = 0;
            partieTest->nom = "PARTIE TEST";

            partieSokoban(partieTest);
        }
        else if (strcmp(choix, "q") == 0){
            conti=0;
        }
    }
}

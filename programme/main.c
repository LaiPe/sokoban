#include "partie.h"

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

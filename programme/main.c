#include <stdio.h>
#include <string.h>

#define LIGNS 10
#define COLS 10

char terrain[LIGNS][COLS] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#',
    '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#',
    '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

int persoLign = 1;
int persoCol = 1;

void printTerrain() {
    for (int lign = 0; lign < LIGNS; lign++) {
        for (int col = 0; col < COLS; col++) {
            printf("%c", terrain[lign][col]);
        }
        printf("\n");
    }
}

int main() {
    printTerrain();

    char input[10];
    while (1) {
        printf("Déplacement ? (g/h/d/b): ");
        scanf("%s", input);

        if (strcmp(input, "h") == 0) {
            // Déplacement haut
            if (terrain[persoLign - 1][persoCol] != '#') {
                terrain[persoLign][persoCol] = ' ';
                persoLign--;
                terrain[persoLign][persoCol] = 'P';
            }
        } else if (strcmp(input, "b") == 0) {
            // Déplacement bas
            if (terrain[persoLign + 1][persoCol] != '#') {
                terrain[persoLign][persoCol] = ' ';
                persoLign++;
                terrain[persoLign][persoCol] = 'P';
            }
        } else if (strcmp(input, "g") == 0) {
            // Déplacement gauche
            if (terrain[persoLign][persoCol - 1] != '#') {
                terrain[persoLign][persoCol] = ' ';
                persoCol--;
                terrain[persoLign][persoCol] = 'P';
            }
        } else if (strcmp(input, "d") == 0) {
            // Déplacement droit
            if (terrain[persoLign][persoCol + 1] != '#') {
                terrain[persoLign][persoCol] = ' ';
                persoCol++;
                terrain[persoLign][persoCol] = 'P';
            }
        }
        system("clear");
        printTerrain();
    }
}

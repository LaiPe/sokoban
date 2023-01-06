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
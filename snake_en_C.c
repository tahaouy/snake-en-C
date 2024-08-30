#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define LONGUEUR 20
#define LARGEUR 20
#define MAX_TAILLE 10

char tab[LONGUEUR][LARGEUR];
int serpentX[LONGUEUR * LARGEUR], serpentY[LONGUEUR * LARGEUR];
char directionActuelle = 'd';
int modeJeu, tailleSerpent = 1, pointX, pointY;

void remplissage() {
    for (int i = 0; i < LONGUEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            tab[i][j] = (i == 0 || i == LONGUEUR - 1) ? '-' : (j == 0 || j == LARGEUR - 1) ? '|' : ' ';
        }
    }
}

void positiondepart() {
    serpentX[0] = LONGUEUR / 2;
    serpentY[0] = LARGEUR / 2;
    tab[serpentX[0]][serpentY[0]] = 'X';
    pointX = rand() % (LONGUEUR - 2) + 1;
    pointY = rand() % (LARGEUR - 2) + 1;
    tab[pointX][pointY] = '*';
}

int verif(int i, int j) {
    return (i > 0 && i < LONGUEUR - 1 && j > 0 && j < LARGEUR - 1);
}

void mettreAJourPositionSerpent() {
    for (int i = 0; i < LONGUEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (tab[i][j] == 'X' || tab[i][j] == 'o') {
                tab[i][j] = ' ';
            }
        }
    }
    tab[serpentX[0]][serpentY[0]] = 'X';
    for (int i = 1; i < tailleSerpent; i++) {
        tab[serpentX[i]][serpentY[i]] = 'o';
    }
}

void verifierMangerPoint() {
    if (serpentX[0] == pointX && serpentY[0] == pointY) {
        if (tailleSerpent < MAX_TAILLE) tailleSerpent++;
        pointX = rand() % (LONGUEUR - 2) + 1;
        pointY = rand() % (LARGEUR - 2) + 1;
        tab[pointX][pointY] = '*';
    }
}

void deplacerSerpent() {
    for (int i = tailleSerpent - 1; i > 0; i--) {
        serpentX[i] = serpentX[i - 1];
        serpentY[i] = serpentY[i - 1];
    }

    switch (directionActuelle) {
        case 'z': serpentX[0]--; break;
        case 's': serpentX[0]++; break;
        case 'q': serpentY[0]--; break;
        case 'd': serpentY[0]++; break;
    }

    if (modeJeu == 1) {
        if (serpentX[0] <= 0 || serpentX[0] >= LONGUEUR - 1 || serpentY[0] <= 0 || serpentY[0] >= LARGEUR - 1) {
            printf("Game Over! Vous avez touch� un mur.\n");
            exit(0);
        }
    } else {
        if (serpentX[0] <= 0) serpentX[0] = LONGUEUR - 2;
        else if (serpentX[0] >= LONGUEUR - 1) serpentX[0] = 1;
        if (serpentY[0] <= 0) serpentY[0] = LARGEUR - 2;
        else if (serpentY[0] >= LARGEUR - 1) serpentY[0] = 1;
    }

    for (int i = 1; i < tailleSerpent; i++) {
        if (serpentX[0] == serpentX[i] && serpentY[0] == serpentY[i]) {
            printf("Game Over! Vous avez touch� votre propre corps.\n");
            exit(0);
        }
    }

    mettreAJourPositionSerpent();
}

void affichertab() {
	system("cls");
    for (int i = 0; i < LONGUEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
    
}

void mouvementversion1() {
    while (1) {
        if (_kbhit()) {
            char direction = _getch();
            if ((direction == 'z' && directionActuelle != 's') ||
                (direction == 's' && directionActuelle != 'z') ||
                (direction == 'q' && directionActuelle != 'd') ||
                (direction == 'd' && directionActuelle != 'q')) {
                directionActuelle = direction;
            }
        }
        deplacerSerpent();
        verifierMangerPoint();
        affichertab();
        Sleep(30);
    }
}

void menu() {
    printf("Choisissez un mode de jeu:\n1. Mode Normal\n2. Mode T�l�portation\nVotre choix: ");
    scanf("%d", &modeJeu);
    while (modeJeu < 1 || modeJeu > 2) {
        printf("Choix invalide. Veuillez saisir 1 ou 2: ");
        scanf("%d", &modeJeu);
    }
}

int main() {
    srand(time(NULL));
    menu();
    remplissage();
    positiondepart();
    affichertab();
    mouvementversion1();
    return 0;
}


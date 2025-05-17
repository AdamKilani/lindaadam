#ifndef SOLVEUR_KAKURO_H
#define SOLVEUR_KAKURO_H

class Grille;

class SolveurKakuro {
public:
    static bool resoudre(Grille* g, bool visualisation = false);
};

#endif
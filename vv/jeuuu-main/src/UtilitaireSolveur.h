#ifndef UTILITAIRE_SOLVEUR_H
#define UTILITAIRE_SOLVEUR_H

#include <vector>

struct Coord {
    int i;
    int j;
};

class Grille;
class Case;

bool verifierBlocParCombi(std::vector<Case*> bloc, int sommeCible, int i, int j, int val);
void trouverCasesVides(Grille* g, std::vector<Coord>& vides);

#endif
#ifndef GRILLE_H
#define GRILLE_H

#include "Case.h"
#include <vector>

class Grille {
private:
    int lignes, colonnes;
    std::vector<std::vector<Case*>> cases;

public:
    Grille(int l, int c);
    ~Grille();

    void afficherGrille() const;
    void setCase(int i, int j, Case* c);
    void lierBlocs();
    void genererToutesCombinaisons();

    // Ajouts pour le solveur :
    int getLignes() const { return lignes; }
    int getColonnes() const { return colonnes; }
    Case* getCase(int i, int j) const { return cases[i][j]; }
};

#endif

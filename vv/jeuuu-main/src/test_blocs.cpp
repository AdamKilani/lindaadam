#include "SolveurKakuro.h"
#include "Grille.h"
#include "Case.h"
#include "UtilitaireSolveur.h"
#include <iostream>
#include <vector>
#include <set>

// ⚠️ Ne redéfinis PAS Coord ici, il est déjà défini dans UtilitaireSolveur.h
/*
// Récupère toutes les cases vides modifiables
static void trouverCasesVides(Grille* g, std::vector<Coord>& vides) {
    for (int i = 0; i < g->getLignes(); ++i) {
        for (int j = 0; j < g->getColonnes(); ++j) {
            Case* c = g->getCase(i, j);
            if (c && c->estModifiable()) {
                vides.push_back({i, j});
            }
        }
    }
}

// Vérifie si la valeur `val` peut être placée en (i,j)
static bool estPlacementValide(Grille* g, int i, int j, int val) {
    Case* c = g->getCase(i, j);
    if (!c || !c->estModifiable()) return false;

    CaseIndication* horizontal = nullptr;
    CaseIndication* vertical = nullptr;

    // 🔍 Chercher vers la gauche une CaseIndication avec sommeDroite
    for (int jj = j - 1; jj >= 0; --jj) {
        Case* cc = g->getCase(i, jj);
        if (!cc || dynamic_cast<CaseNoire*>(cc)) break;
        if (auto ci = dynamic_cast<CaseIndication*>(cc)) {
            if (ci->getSommeDroite() > 0) {
                horizontal = ci;
                break;
            }
        }
    }

    // 🔍 Chercher vers le haut une CaseIndication avec sommeBas
    for (int ii = i - 1; ii >= 0; --ii) {
        Case* cc = g->getCase(ii, j);
        if (!cc || dynamic_cast<CaseNoire*>(cc)) break;
        if (auto ci = dynamic_cast<CaseIndication*>(cc)) {
            if (ci->getSommeBas() > 0) {
                vertical = ci;
                break;
            }
        }
    }

    bool valide = true;

    if (horizontal) {
        auto cases = horizontal->getCasesHorizontales();
        valide &= verifierBlocParCombi(cases, horizontal->getSommeDroite(), i, j, val);
    }
    if (vertical) {
        auto cases = vertical->getCasesVerticales();
        valide &= verifierBlocParCombi(cases, vertical->getSommeBas(), i, j, val);
    }

    return valide;
}

// Vérifie toute la grille finale
static bool verifierSolutionFinale(Grille* g) {
    for (int i = 0; i < g->getLignes(); ++i) {
        for (int j = 0; j < g->getColonnes(); ++j) {
            Case* c = g->getCase(i, j);
            if (CaseVide* cv = dynamic_cast<CaseVide*>(c)) {
                int val = cv->getValeur();
                if (val == 0 || !estPlacementValide(g, i, j, val)) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Algorithme de backtracking
static bool backtrack(Grille* g, const std::vector<Coord>& vides, int index) {
    if (index == vides.size()) {
        return verifierSolutionFinale(g);
    }

    int i = vides[index].i;
    int j = vides[index].j;
    CaseVide* c = dynamic_cast<CaseVide*>(g->getCase(i, j));
    if (!c) return false;

    for (int val = 1; val <= 9; ++val) {
        if (estPlacementValide(g, i, j, val)) {
            c->setValeur(val);
            if (backtrack(g, vides, index + 1)) return true;
            c->setValeur(0);
        }
    }

    return false;
}

// Point d’entrée du solveur
bool SolveurKakuro::resoudre(Grille* g) {
    std::vector<Coord> vides;
    trouverCasesVides(g, vides);

    std::cout << "🔍 " << vides.size() << " cases à remplir..." << std::endl;

    g->lierBlocs(); // Remplit casesDroite/casesBas dans les indications
    g->genererToutesCombinaisons(); // Pré-calcule toutes les combinaisons valides

    return backtrack(g, vides, 0);
}
*/
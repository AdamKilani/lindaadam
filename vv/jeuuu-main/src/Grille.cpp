#include "Grille.h"
#include <iostream>

Grille::Grille(int l, int c) : lignes(l), colonnes(c) {
    cases.resize(lignes, std::vector<Case*>(colonnes, nullptr));
}

Grille::~Grille() {
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            delete cases[i][j];
        }
    }
}

void Grille::setCase(int i, int j, Case* c) {
    if (cases[i][j]) delete cases[i][j];
    cases[i][j] = c;
}

void Grille::afficherGrille() const {
    std::cout << lignes << " " << colonnes << std::endl;
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            if (cases[i][j])
                cases[i][j]->afficher();
            else
                std::cout << " ";
            std::cout << " "; // <-- AJOUTE cet espace après chaque case
        }
        std::cout << std::endl;
    }
}

void Grille::lierBlocs() {
    for (int i = 0; i < getLignes(); ++i) {
        for (int j = 0; j < getColonnes(); ++j) {
            CaseIndication* ci = dynamic_cast<CaseIndication*>(getCase(i, j));
            if (!ci) continue;

            // Lier les cases à droite (horizontal)
            if (ci->getSommeDroite() > 0) {
                int y = j + 1;
                while (y < getColonnes()) {
                    Case* c = getCase(i, y);
                    if (!c || dynamic_cast<CaseNoire*>(c) || dynamic_cast<CaseIndication*>(c)) break;
                    ci->ajouterCaseHorizontale(c);
                    ++y;
                }
            }

            // Lier les cases en bas (vertical)
            if (ci->getSommeBas() > 0) {
                int x = i + 1;
                while (x < getLignes()) {
                    Case* c = getCase(x, j);
                    if (!c || dynamic_cast<CaseNoire*>(c) || dynamic_cast<CaseIndication*>(c)) break;
                    ci->ajouterCaseVerticale(c);
                    ++x;
                }
            }
        }
    }
}

void Grille::genererToutesCombinaisons() {
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            Case* c = getCase(i, j);
            if (CaseIndication* ci = dynamic_cast<CaseIndication*>(c)) {
                ci->genererCombinaisons();
            }
        }
    }
}





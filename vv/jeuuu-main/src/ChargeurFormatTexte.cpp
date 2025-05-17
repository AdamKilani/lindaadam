#include "ChargeurFormatTexte.h"
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

Grille* ChargeurFormatTexte::chargerDepuisFichier(const std::string& chemin) {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d’ouvrir le fichier " << chemin << std::endl;
        return nullptr;
    }

    int lignes, colonnes;
    fichier >> lignes >> colonnes;
    fichier.ignore(); // ignorer le saut de ligne

    Grille* g = new Grille(lignes, colonnes);

    for (int i = 0; i < lignes; ++i) {
        std::string ligne;
        std::getline(fichier, ligne);
        std::istringstream iss(ligne);
        for (int j = 0; j < colonnes; ++j) {
            std::string caseStr;
            iss >> caseStr;

            if (caseStr == "#") {
                g->setCase(i, j, new CaseNoire());
            } else if (caseStr == "_") {
                g->setCase(i, j, new CaseVide());
            } else if (caseStr.find('/') != std::string::npos) {
                size_t slashPos = caseStr.find('/');
                std::string gauche = caseStr.substr(0, slashPos);
                std::string droite = caseStr.substr(slashPos + 1);
                int d = 0, b = 0;

                if (!gauche.empty()) b = std::stoi(gauche); // b = bas
if (!droite.empty()) d = std::stoi(droite); // d = droite
g->setCase(i, j, new CaseIndication(d, b));

            } else {
                int val = std::stoi(caseStr);
                g->setCase(i, j, new CaseFixe(val));
            }
        }
    }

    return g;
}

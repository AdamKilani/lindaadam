#include "ChargeurInteraction.h"
#include "Case.h"
#include <iostream>
#include <sstream>

Grille* ChargeurInteraction::chargerDepuisConsole() {
    int lignes, colonnes;
    std::cout << "=== Mode manuel ===" << std::endl;
    std::cout << "Entrez la hauteur (lignes) : ";
    std::cin >> lignes;
    std::cout << "Entrez la largeur (colonnes) : ";
    std::cin >> colonnes;
    std::cin.ignore(); // pour ignorer le \n restant

    Grille* g = new Grille(lignes, colonnes);
    std::cout << "Entrez la grille ligne par ligne (comme dans un fichier .kakuro) :" << std::endl;

    for (int i = 0; i < lignes; ++i) {
        std::string ligne;
        std::cout << "Ligne " << (i + 1) << ": ";
        std::getline(std::cin, ligne);
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

                if (!gauche.empty()) d = std::stoi(gauche);
                if (!droite.empty()) b = std::stoi(droite);
                g->setCase(i, j, new CaseIndication(d, b));
            } else {
                int val = std::stoi(caseStr);
                g->setCase(i, j, new CaseFixe(val));
            }
        }
    }

    return g;
}

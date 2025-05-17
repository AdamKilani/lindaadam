#include "ChargeurFormatJSON.h"
#include "Grille.h"
#include "Case.h"
#include "json.hpp"
#include <fstream>
#include <string>
#include <iostream>

using json = nlohmann::json;

Grille* ChargeurFormatJSON::chargerDepuisFichier(const std::string& chemin) {
    std::ifstream in(chemin);
    if (!in.is_open()) {
        std::cerr << "Erreur : impossible d’ouvrir " << chemin << std::endl;
        return nullptr;
    }

    json j;
    in >> j;

    int lignes = j["lignes"];
    int colonnes = j["colonnes"];
    auto g = new Grille(lignes, colonnes);

    for (int i = 0; i < lignes; ++i) {
        for (int jCol = 0; jCol < colonnes; ++jCol) {
            std::string val = j["grille"][i][jCol];

            if (val == "#") {
                g->setCase(i, jCol, new CaseNoire());
            } else if (val == "." || val == "_") {
                g->setCase(i, jCol, new CaseVide());
            } else if (val.find('/') != std::string::npos) {
                int sBas = 0, sDroite = 0;
                size_t pos = val.find('/');
                std::string droite = val.substr(0, pos);
                std::string bas = val.substr(pos + 1);
                sDroite = droite.empty() ? 0 : std::stoi(droite);
                sBas = bas.empty() ? 0 : std::stoi(bas);
                g->setCase(i, jCol, new CaseIndication(sDroite, sBas));
            } else {
                g->setCase(i, jCol, new CaseFixe(std::stoi(val)));
            }
        }
    }

    return g;
}

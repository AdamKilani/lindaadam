#ifndef CHARGEUR_FORMAT_TEXTE_H
#define CHARGEUR_FORMAT_TEXTE_H

#include "Grille.h"
#include <fstream>
#include <sstream>

class ChargeurFormatTexte {
public:
    static Grille* chargerDepuisFichier(const std::string& chemin);
};

#endif

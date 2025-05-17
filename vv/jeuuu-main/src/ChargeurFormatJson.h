#ifndef CHARGEUR_FORMAT_JSON_H
#define CHARGEUR_FORMAT_JSON_H

#include "Grille.h"
#include <string>

class ChargeurFormatJSON {
public:
    static Grille* chargerDepuisFichier(const std::string& chemin);
};

#endif

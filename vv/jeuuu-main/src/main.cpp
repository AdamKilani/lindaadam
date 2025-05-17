#include "ChargeurFormatTexte.h"
#include "ChargeurInteraction.h"
#include "ChargeurFormatJSON.h"
#include "SolveurKakuro.h"
#include "Grille.h"
#include <iostream>

int main() {
    std::cout << "=== Solveur de Kakuro ===" << std::endl;
    std::cout << "Choisissez le mode de chargement de la grille :" << std::endl;
    std::cout << "1. Depuis un fichier texte (.kakuro)" << std::endl;
    std::cout << "2. Depuis l'entrée utilisateur (manuel)" << std::endl;
    std::cout << "3. Depuis un fichier JSON (.json)" << std::endl;

    int choix;
    std::cin >> choix;
    std::cin.ignore();

    Grille* g = nullptr;

    if (choix == 1) {
        std::string chemin;
        std::cout << "Chemin du fichier (ex: grilles/5_4.kakuro) : ";
        std::getline(std::cin, chemin);
        g = ChargeurFormatTexte::chargerDepuisFichier(chemin);
    } else if (choix == 2) {
        g = ChargeurInteraction::chargerDepuisConsole();
    } else if (choix == 3) {
        std::string chemin;
        std::cout << "Chemin du fichier JSON (ex: grilles/5_4.json) : ";
        std::getline(std::cin, chemin);
        g = ChargeurFormatJSON::chargerDepuisFichier(chemin);
    } else {
        std::cout << "❌ Choix invalide." << std::endl;
        return 1;
    }

    if (g) {
        std::cout << "\nGrille initiale :" << std::endl;
        g->afficherGrille();

        std::cout << "\nActiver la visualisation pas-à-pas ? (o/n) ";
        char choixVisu;
        std::cin >> choixVisu;
        std::cin.ignore();

        std::cout << "\nRésolution en cours..." << std::endl;
        if (SolveurKakuro::resoudre(g, choixVisu == 'o' || choixVisu == 'O')) {
            std::cout << "\n✅ Grille résolue avec succès :" << std::endl;
            g->afficherGrille();
        } else {
            std::cout << "\n❌ Aucune solution trouvée." << std::endl;
        }

        delete g;
    }

    return 0;
}
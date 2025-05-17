#include "SolveurKakuro.h"
#include "Grille.h"
#include "Case.h"
#include "UtilitaireSolveur.h"
#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <thread>
#include <stdexcept>

static void afficherEtape(const Grille* g, int i, int j, int val) {
    try {
        #ifdef _WIN32
        if (system("cls") != 0) {
            std::cerr << "Erreur lors du nettoyage de la console\n";
        }
        #else
        if (system("clear") != 0) {
            std::cerr << "Erreur lors du nettoyage de la console\n";
        }
        #endif
        
        if (!g) throw std::invalid_argument("Grille invalide");
        std::cout << "Test valeur " << val << " en position (" << i+1 << "," << j+1 << ")\n";
        g->afficherGrille();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    } catch (const std::exception& e) {
        std::cerr << "Erreur dans afficherEtape: " << e.what() << std::endl;
    }
}

bool estPlacementValide(Grille* g, int i, int j, int val) {
    try {
        if (!g) throw std::invalid_argument("Grille invalide");
        if (val < 1 || val > 9) throw std::out_of_range("Valeur hors limites 1-9");

        Case* c = g->getCase(i, j);
        if (!c || !c->estModifiable()) return false;

        auto verifierBlocCombi = [&](std::vector<Case*> bloc, const std::vector<std::set<int>>& combinaisons) {
            if (bloc.empty() || combinaisons.empty()) return false;

            std::vector<int> valeurs;
            for (Case* caseBloc : bloc) {
                if (!caseBloc) continue;

                if (CaseVide* cv = dynamic_cast<CaseVide*>(caseBloc)) {
                    valeurs.push_back((cv->getValeur() == 0) ? -1 : cv->getValeur());
                } else if (CaseFixe* cf = dynamic_cast<CaseFixe*>(caseBloc)) {
                    valeurs.push_back(cf->getValeur());
                }
            }

            for (size_t k = 0; k < bloc.size(); ++k) {
                if (k >= valeurs.size()) break;
                if (bloc[k] == c) {
                    valeurs[k] = val;
                    break;
                }
            }

            for (const auto& combinaison : combinaisons) {
                if (combinaison.size() != valeurs.size()) continue;
                std::set<int> test;
                bool ok = true;
                for (int v : valeurs) {
                    if (v == -1) continue;
                    if (test.count(v) || !combinaison.count(v)) {
                        ok = false;
                        break;
                    }
                    test.insert(v);
                }
                if (ok) return true;
            }
            return false;
        };

        CaseIndication* horizontal = nullptr;
        CaseIndication* vertical = nullptr;

        // Recherche horizontale
        for (int jj = j - 1; jj >= 0; --jj) {
            Case* left = g->getCase(i, jj);
            if (!left) break;

            if (auto ci = dynamic_cast<CaseIndication*>(left)) {
                if (ci->getSommeDroite() > 0) horizontal = ci;
                break;
            }
            if (dynamic_cast<CaseNoire*>(left)) break;
        }

        // Recherche verticale
        for (int ii = i - 1; ii >= 0; --ii) {
            Case* up = g->getCase(ii, j);
            if (!up) break;

            if (auto ci = dynamic_cast<CaseIndication*>(up)) {
                if (ci->getSommeBas() > 0) vertical = ci;
                break;
            }
            if (dynamic_cast<CaseNoire*>(up)) break;
        }

        bool ok = true;
        if (horizontal) {
            if (horizontal->getCasesHorizontales().empty()) {
                throw std::logic_error("Bloc horizontal vide");
            }
            ok &= verifierBlocCombi(horizontal->getCasesHorizontales(), horizontal->combinaisonsValidées);
        }
        if (vertical) {
            if (vertical->getCasesVerticales().empty()) {
                throw std::logic_error("Bloc vertical vide");
            }
            ok &= verifierBlocCombi(vertical->getCasesVerticales(), vertical->combinaisonsValidées);
        }
        return ok;
    } catch (const std::exception& e) {
        std::cerr << "Erreur dans estPlacementValide: " << e.what() << std::endl;
        return false;
    }
}

static bool verifierSolutionFinale(Grille* g) {
    try {
        if (!g) throw std::invalid_argument("Grille invalide");

        for (int i = 0; i < g->getLignes(); ++i) {
            for (int j = 0; j < g->getColonnes(); ++j) {
                Case* c = g->getCase(i, j);
                if (!c) continue;

                if (CaseVide* cv = dynamic_cast<CaseVide*>(c)) {
                    int val = cv->getValeur();
                    if (val == 0 || !estPlacementValide(g, i, j, val))
                        return false;
                }
            }
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erreur dans verifierSolutionFinale: " << e.what() << std::endl;
        return false;
    }
}

static bool backtrack(Grille* g, const std::vector<Coord>& vides, size_t index, bool visualisation) {
    try {
        if (!g) throw std::invalid_argument("Grille invalide");
        if (index > vides.size()) throw std::out_of_range("Index invalide");

        if (index == vides.size())
            return verifierSolutionFinale(g);

        int i = vides[index].i;
        int j = vides[index].j;
        CaseVide* c = dynamic_cast<CaseVide*>(g->getCase(i, j));
        if (!c) return false;

        for (int val = 1; val <= 9; ++val) {
            if (estPlacementValide(g, i, j, val)) {
                c->setValeur(val);
                if (visualisation) afficherEtape(g, i, j, val);
                if (backtrack(g, vides, index + 1, visualisation)) return true;
                c->setValeur(0);
            }
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Erreur dans backtrack: " << e.what() << std::endl;
        return false;
    }
}

bool SolveurKakuro::resoudre(Grille* g, bool visualisation) {
    try {
        if (!g) throw std::invalid_argument("Grille invalide");

        std::vector<Coord> vides;
        trouverCasesVides(g, vides);
        
        if (vides.empty()) {
            std::cerr << "Aucune case vide trouvée\n";
            return false;
        }

        g->lierBlocs();
        g->genererToutesCombinaisons();
        
        return backtrack(g, vides, 0, visualisation);
    } catch (const std::exception& e) {
        std::cerr << "Erreur dans resoudre: " << e.what() << std::endl;
        return false;
    }
}
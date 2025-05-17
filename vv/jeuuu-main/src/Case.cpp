#include "Case.h"
#include <set>
#include <vector>
#include <functional>
#include <algorithm>

void CaseIndication::genererCombinaisons() {
    auto generer = [&](int sommeCible, const std::vector<Case*>& cases) {
        size_t nbCases = cases.size(); // Changé de int à size_t
        std::vector<std::set<int>> combinaisons;

        std::vector<int> chiffres {1,2,3,4,5,6,7,8,9};
        std::vector<bool> selection(chiffres.size(), false);

        std::function<void(size_t, int, std::set<int>&)> backtrack = [&](size_t index, int sommeActuelle, std::set<int>& courant) {
            if (courant.size() == nbCases) {
                if (sommeActuelle == sommeCible)
                    combinaisons.push_back(courant);
                return;
            }

            for (size_t i = index; i < chiffres.size(); ++i) {
                int val = chiffres[i];
                if (courant.count(val)) continue;
                if (sommeActuelle + val > sommeCible) break;

                courant.insert(val);
                backtrack(i + 1, sommeActuelle + val, courant);
                courant.erase(val);
            }
        };

        std::set<int> enCours;
        backtrack(0, 0, enCours);

        if (cases == casesDroite) combinaisonsValidées = combinaisons;
        else if (cases == casesBas) combinaisonsValidées.insert(combinaisonsValidées.end(), combinaisons.begin(), combinaisons.end());
    };

    if (!casesDroite.empty()) generer(sommeDroite, casesDroite);
    if (!casesBas.empty())    generer(sommeBas, casesBas);
}
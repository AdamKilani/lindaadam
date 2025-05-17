#ifndef CASE_H
#define CASE_H

#include <iostream>
#include <vector>
#include <set>

class Case {
public:
    virtual void afficher() const = 0;
    virtual bool estModifiable() const = 0;
    virtual ~Case() {}
};

// Case noire
class CaseNoire : public Case {
public:
    void afficher() const override {
        std::cout << "#";
    }
    bool estModifiable() const override {
        return false;
    }
};

// Case à remplir (vide)
class CaseVide : public Case {
private:
    int valeur;
public:
    CaseVide() : valeur(0) {}
    void setValeur(int v) { valeur = v; }
    int getValeur() const { return valeur; }

    void afficher() const override {
        if (valeur == 0) std::cout << "_";
        else std::cout << valeur;
    }

    bool estModifiable() const override {
        return true;
    }
};

// Case avec valeur fixe (ex. pour tests)
class CaseFixe : public Case {
private:
    int valeur;
public:
    CaseFixe(int v) : valeur(v) {}
    int getValeur() const { return valeur; }

    void afficher() const override {
        std::cout << valeur;
    }
    bool estModifiable() const override {
        return false;
    }
};

// Case avec indication de somme
class CaseIndication : public Case {
private:
    int sommeDroite;
    int sommeBas;
    std::vector<Case*> casesDroite;
    std::vector<Case*> casesBas;

public:
    CaseIndication(int droite, int bas) : sommeDroite(droite), sommeBas(bas) {}

    int getSommeDroite() const { return sommeDroite; }
    int getSommeBas() const { return sommeBas; }

    void ajouterCaseHorizontale(Case* c) { casesDroite.push_back(c); }
    void ajouterCaseVerticale(Case* c) { casesBas.push_back(c); }

    const std::vector<Case*>& getCasesHorizontales() const { return casesDroite; }
    const std::vector<Case*>& getCasesVerticales() const { return casesBas; }

    void afficher() const override {
        if (sommeDroite > 0 && sommeBas > 0)
            std::cout << sommeDroite << "/" << sommeBas;
        else if (sommeDroite > 0)
            std::cout << sommeDroite << "/";
        else if (sommeBas > 0)
            std::cout << "/" << sommeBas;
        else
            std::cout << "#";
    }

    bool estModifiable() const override {
        return false;
    }

    std::vector<std::set<int>> combinaisonsValidées;
    void genererCombinaisons();
};

#endif

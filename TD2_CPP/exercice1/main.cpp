#include "LinearSearch.h"
#include "JumpSearch.h"
#include "BinarySearch.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

int erreurs = 0;
int tests = 0;

void verifier(bool condition, const char* description)
{
    ++tests;
    std::cout << (condition ? "OK : " : "ECHEC : ") << description << '\n';
    if (!condition)
        ++erreurs;
}

void testerRecherche(SearchingAlgorithm& algo, const std::vector<int>& valeurs,
                     int cible, int indiceAttendu, int comparaisonsAttendues)
{
    long long recherchesAvant = SearchingAlgorithm::getTotalSearch();
    long long comparaisonsAvant = SearchingAlgorithm::getTotalComparisons();
    int resultat = algo.search(valeurs, cible);
    algo.displaySearchResults(std::cout, resultat, cible);
    verifier(resultat == indiceAttendu, "indice ou absence");
    verifier(algo.getNumberComparisons() == comparaisonsAttendues, "comparaisons exactes");
    verifier(SearchingAlgorithm::getTotalSearch() == recherchesAvant + 1,
             "une recherche supplementaire");
    verifier(SearchingAlgorithm::getTotalComparisons() == comparaisonsAvant + comparaisonsAttendues,
             "cumul des comparaisons");
    verifier(std::abs(SearchingAlgorithm::getAverageComparisons()
             - (double) (comparaisonsAvant + comparaisonsAttendues) / (recherchesAvant + 1)) < 1e-9,
             "moyenne globale");
    std::ostringstream sortie;
    algo.displaySearchResults(sortie, resultat, cible);
    verifier(SearchingAlgorithm::getTotalComparisons() == comparaisonsAvant + comparaisonsAttendues
             && SearchingAlgorithm::getTotalSearch() == recherchesAvant + 1,
             "reafficher ne compte pas deux fois");
    verifier(sortie.str().find(resultat == -1 ? "absente" : "indice") != std::string::npos,
             "affichage dans le flux demande");
}

int main()
{
    LinearSearch lineaire;
    JumpSearch saut;
    BinarySearch dichotomique;
    verifier(lineaire.getNumberComparisons() == 0
             && SearchingAlgorithm::getTotalSearch() == 0
             && SearchingAlgorithm::getTotalComparisons() == 0
             && SearchingAlgorithm::getAverageComparisons() == 0, "constructeur et compteurs initiaux");
    std::vector<int> valeurs = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    std::vector<int> vide;
    std::vector<int> unique = {5};
    SearchingAlgorithm* algorithmes[] = {&lineaire, &saut, &dichotomique};
    const char* noms[] = {"LinearSearch", "JumpSearch", "BinarySearch"};
    int cibles[] = {9, 1, 17, 8, 0, 20};
    int indices[] = {4, 0, 8, -1, -1, -1};
    int comparaisons[3][6] = {{5, 1, 9, 9, 9, 9}, {4, 2, 6, 5, 4, 3}, {1, 5, 7, 8, 6, 8}};
    for (int a = 0; a < 3; ++a)
    {
        std::cout << '\n' << noms[a] << '\n';
        for (int i = 0; i < 6; ++i)
            testerRecherche(*algorithmes[a], valeurs, cibles[i], indices[i], comparaisons[a][i]);
        testerRecherche(*algorithmes[a], vide, 5, -1, 0);
        testerRecherche(*algorithmes[a], unique, 5, 0, a == 1 ? 2 : 1);
        testerRecherche(*algorithmes[a], unique, 4, -1, a == 0 ? 1 : 2);
    }
    testerRecherche(lineaire, std::vector<int>{7, 2, 9}, 2, 1, 2);

    long long totalAvant = SearchingAlgorithm::getTotalComparisons();
    long long recherchesAvant = SearchingAlgorithm::getTotalSearch();
    lineaire.search(valeurs, 1);
    lineaire.search(valeurs, 17);
    saut.search(valeurs, 9);
    std::ostringstream sortie;
    saut.displaySearchResults(sortie, 4, 9);
    verifier(SearchingAlgorithm::getTotalSearch() == recherchesAvant + 3
             && SearchingAlgorithm::getTotalComparisons() == totalAvant + 14,
             "plusieurs recherches sans affichage : aucun comptage perdu");
    LinearSearch autreInstance;
    verifier(autreInstance.getNumberComparisons() == 0
             && SearchingAlgorithm::getTotalSearch() == recherchesAvant + 3,
             "nouvelle instance : compteur individuel nul, statistiques conservees");

    bool tousCorrects = true;
    // Tailles variees, blocs incomplets et doublons ; recherche par reference de base.
    for (int taille = 0; taille <= 40; ++taille)
    {
        std::vector<int> tableau;
        for (int i = 0; i < taille; ++i)
            tableau.push_back(i / 2);
        for (int cible = -1; cible <= taille; ++cible)
        {
            bool present = taille > 0 && cible >= 0 && cible <= (taille - 1) / 2;
            for (int a = 0; a < 3; ++a)
            {
                int indice = algorithmes[a]->search(tableau, cible);
                if (present)
                    tousCorrects = tousCorrects && indice >= 0 && indice < taille && tableau[indice] == cible;
                else
                    tousCorrects = tousCorrects && indice == -1;
            }
        }
    }
    verifier(tousCorrects, "2706 recherches supplementaires : tailles 0 a 40 et doublons");
    std::cout << tests << " verifications, " << erreurs << " erreur(s)\n";
    return erreurs == 0 ? 0 : 1;
}

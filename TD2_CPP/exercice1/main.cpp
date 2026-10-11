#include "LinearSearch.h"
#include "JumpSearch.h"
#include "BinarySearch.h"
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> tableau = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    LinearSearch lineaire;
    JumpSearch saut;
    BinarySearch dichotomique;
    int resultat;

    std::cout << "Recherche lineaire\n";
    resultat = lineaire.search(tableau, 9);
    lineaire.displaySearchResults(std::cout, resultat, 9);
    resultat = lineaire.search(tableau, 8);
    lineaire.displaySearchResults(std::cout, resultat, 8);

    std::cout << "\nRecherche par sauts\n";
    resultat = saut.search(tableau, 9);
    saut.displaySearchResults(std::cout, resultat, 9);
    resultat = saut.search(tableau, 8);
    saut.displaySearchResults(std::cout, resultat, 8);

    std::cout << "\nRecherche dichotomique\n";
    resultat = dichotomique.search(tableau, 9);
    dichotomique.displaySearchResults(std::cout, resultat, 9);
    resultat = dichotomique.search(tableau, 8);
    dichotomique.displaySearchResults(std::cout, resultat, 8);

    return 0;
}

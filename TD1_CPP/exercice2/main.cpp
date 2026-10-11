#include "Complex2D.h"
#include <iostream>
#include <stdexcept>

int main()
{
    Complex2D a(3, 4);
    Complex2D b(1, 2);
    Complex2D c;
    Complex2D d(5);
    Complex2D e(a);

    std::cout << "Constructeurs :" << std::endl;
    std::cout << "a = " << a.getReel() << " + " << a.getImaginaire() << "i" << std::endl;
    std::cout << "b = " << b.getReel() << " + " << b.getImaginaire() << "i" << std::endl;
    std::cout << "c = " << c.getReel() << " + " << c.getImaginaire() << "i" << std::endl;
    std::cout << "d = " << d.getReel() << " + " << d.getImaginaire() << "i" << std::endl;
    std::cout << "e = " << e.getReel() << " + " << e.getImaginaire() << "i" << std::endl;

    a.setReel(6);
    a.setImaginaire(8);

    std::cout << "\nApres modification de a :" << std::endl;
    std::cout << "a = " << a.getReel() << " + " << a.getImaginaire() << "i" << std::endl;

    Complex2D somme = a + b;
    Complex2D difference = a - b;
    Complex2D produit = a * b;
    Complex2D quotient = a / b;

    std::cout << "\nOperations :" << std::endl;
    std::cout << "Addition : " << somme.getReel() << " + " << somme.getImaginaire() << "i" << std::endl;
    std::cout << "Soustraction : " << difference.getReel() << " + " << difference.getImaginaire() << "i" << std::endl;
    std::cout << "Multiplication : " << produit.getReel() << " + " << produit.getImaginaire() << "i" << std::endl;
    std::cout << "Division : " << quotient.getReel() << " + " << quotient.getImaginaire() << "i" << std::endl;

    std::cout << "\nComparaisons :" << std::endl;

    if (a > b)
        std::cout << "a est superieur a b" << std::endl;

    if (a < b)
        std::cout << "a est inferieur a b" << std::endl;

    if (a == b)
        std::cout << "a est egal a b" << std::endl;

    if (a != b)
        std::cout << "a est different de b" << std::endl;

    std::cout << "\nModule de a : " << a.module() << std::endl;

    Complex2D conjugue = a.conjugue();
    std::cout << "Conjugue de a : " << conjugue.getReel()
              << " + " << conjugue.getImaginaire() << "i" << std::endl;

    e = b;
    std::cout << "\nApres affectation e = b :" << std::endl;
    std::cout << "e = " << e.getReel() << " + " << e.getImaginaire() << "i" << std::endl;

    try
    {
        Complex2D resultat = a / c;
        std::cout << resultat.getReel() << std::endl;
    }
    catch (const std::domain_error& erreur)
    {
        std::cout << "Erreur : " << erreur.what() << std::endl;
    }

    return 0;
}
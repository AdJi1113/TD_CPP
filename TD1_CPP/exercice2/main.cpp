#include "Complex2D.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

int erreurs = 0;

void verifier(bool condition, const char* description)
{
    std::cout << (condition ? "OK : " : "ECHEC : ") << description << std::endl;
    if (!condition)
        erreurs++;
}

bool proche(double a, double b)
{
    return std::abs(a - b) < 0.000000001;
}

bool vaut(const Complex2D& z, double r, double i)
{
    return proche(z.getReel(), r) && proche(z.getImaginaire(), i);
}

int main()
{
    Complex2D zero;
    Complex2D a(3, 4);
    Complex2D b(1, -2);
    Complex2D commun(2);
    Complex2D copie(a);

    verifier(vaut(zero, 0, 0), "constructeur par defaut");
    verifier(vaut(a, 3, 4), "constructeur a deux valeurs et getters");
    verifier(vaut(commun, 2, 2), "meme valeur pour les deux parties");
    verifier(vaut(copie, 3, 4), "constructeur par copie");
    copie.setReel(6);
    copie.setImaginaire(-7);
    verifier(vaut(copie, 6, -7) && vaut(a, 3, 4), "setters et independance de la copie");

    verifier(vaut(a + b, 4, 2), "addition");
    verifier(vaut(a - b, 2, 6), "soustraction");
    verifier(vaut(a * b, 11, -2), "multiplication");
    verifier(vaut(a / b, -1, 2), "division");
    verifier(vaut(a / a, 1, 0), "division par soi-meme");
    verifier(vaut(zero / a, 0, 0), "numerateur nul");
    verifier(vaut(Complex2D(0, 1) * Complex2D(0, 1), -1, 0), "i au carre = -1");
    verifier(vaut(Complex2D(1, 0) / Complex2D(3, 0), 1.0 / 3.0, 0), "division non entiere");
    verifier(b < a && a > b && !(a < b) && !(b > a), "comparaison des modules");
    Complex2D memeModule(0, 5);
    verifier(!(a < memeModule) && !(a > memeModule), "modules egaux");
    verifier(!(a < a) && !(a > a), "comparaison avec soi-meme");

    copie = a;
    verifier(copie == a && !(copie != a), "affectation et egalite");
    copie = copie;
    verifier(copie == a, "auto-affectation");
    verifier(a != memeModule && !(a == memeModule), "meme module ne signifie pas egalite");
    verifier(proche(a.module(), 5), "module");
    verifier(vaut(a.conjugue(), 3, -4), "conjugue");

    bool erreurDetectee = false;
    try
    {
        Complex2D resultat = a / zero;
        std::cout << resultat.getReel() << std::endl;
    }
    catch (const std::domain_error& erreur)
    {
        erreurDetectee = true;
        std::cout << "Erreur attendue : " << erreur.what() << std::endl;
    }
    verifier(erreurDetectee, "division par zero refusee");
    std::cout << erreurs << " erreur(s)" << std::endl;
    return erreurs == 0 ? 0 : 1;
}

#include "MatrixNumerical.h"
#include <cmath>
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

template<class T, class U>
bool egales(const MatrixBase<T>& a, const MatrixBase<U>& b)
{
    if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        return false;
    for (std::size_t i = 0; i < a.getRows(); ++i)
        for (std::size_t j = 0; j < a.getCols(); ++j)
            if (!(std::abs((double) a.getElement(i, j) - (double) b.getElement(i, j)) < 1e-9))
                return false;
    return true;
}

int main()
{
    MatrixBase<int> vide;
    MatrixBase<int> zeros(2, 3);
    verifier(vide.getRows() == 0 && vide.getCols() == 0, "constructeur par defaut");
    verifier(zeros.getRows() == 2 && zeros.getCols() == 3
             && zeros.getElement(1, 2) == 0, "dimensions et initialisation a zero");
    zeros.addElement(1, 2, 7);
    verifier(zeros.getElement(1, 2) == 7, "addElement et getElement");
    MatrixBase<int> copie(zeros);
    copie.addElement(1, 2, 4);
    verifier(zeros.getElement(1, 2) == 7 && copie.getElement(1, 2) == 4, "copie independante");
    copie = zeros;
    verifier(egales(copie, zeros), "affectation");
    MatrixBase<std::string> mots(1, 2);
    mots.addElement(0, 0, "Bonjour");
    mots.addElement(0, 1, "C++");
    std::ostringstream sortie;
    mots.Display(sortie);
    verifier(sortie.str() == "Bonjour C++\n", "MatrixBase generique et Display");

    MatrixNumerical<int> a(std::vector<std::vector<int> >{{4, 7}, {2, 6}});
    MatrixNumerical<int> b(std::vector<std::vector<int> >{{1, 2}, {3, 4}});
    verifier(egales(a + b, MatrixNumerical<int>(std::vector<std::vector<int> >{{5, 9}, {5, 10}})), "addition");
    verifier(egales(a - b, MatrixNumerical<int>(std::vector<std::vector<int> >{{3, 5}, {-1, 2}})), "soustraction");
    verifier(egales(a * b, MatrixNumerical<int>(std::vector<std::vector<int> >{{25, 36}, {20, 28}})), "multiplication");
    verifier(a.getDeterminant() == 10 && b.getDeterminant() == -2, "determinants 2 x 2");
    MatrixNumerical<double> inverseAttendu(std::vector<std::vector<double> >{{0.6, -0.7}, {-0.2, 0.4}});
    verifier(egales(a.getInverse(), inverseAttendu), "inverse d'une matrice entiere sans troncature");
    MatrixNumerical<double> reel(std::vector<std::vector<double> >{{4, 7}, {2, 6}});
    MatrixNumerical<double> identite = MatrixNumerical<double>::getIdentity(2);
    verifier(egales(reel * reel.getInverse(), identite)
             && egales(reel.getInverse() * reel, identite), "A * inverse(A) et inverse(A) * A");
    verifier(egales(a / a, identite), "division par soi-meme");
    verifier(egales(a / b, MatrixNumerical<double>(std::vector<std::vector<double> >{{2.5, 0.5}, {5, -1}})),
             "division A / B = A * inverse(B), ordre respecte");
    verifier(getCoFactor(a, 0, 1) == -2 && getCoFactor(a, 1, 0) == -7, "signes des cofacteurs");
    MatrixNumerical<int> trois(std::vector<std::vector<int> >{{1, 2, 3}, {0, 1, 4}, {5, 6, 0}});
    verifier(trois.getDeterminant() == 1, "determinant 3 x 3 recursif");
    verifier(egales(trois.getInverse(), MatrixNumerical<int>(std::vector<std::vector<int> >
             {{-24, 18, 5}, {20, -15, -4}, {-5, 4, 1}})), "inverse 3 x 3 par cofacteurs");
    MatrixNumerical<int> quatre(std::vector<std::vector<int> >
             {{2, 1, 0, 0}, {0, 3, 1, 0}, {0, 0, 4, 1}, {0, 0, 0, 5}});
    verifier(quatre.getDeterminant() == 120, "determinant 4 x 4");
    verifier(egales(quatre / quatre, MatrixNumerical<double>::getIdentity(4)), "inverse 4 x 4");
    MatrixNumerical<int> un(std::vector<std::vector<int> >{{4}});
    verifier(un.getDeterminant() == 4 && getCoFactor(un, 0, 0) == 1
             && un.getInverse().getElement(0, 0) == 0.25, "matrice 1 x 1");
    MatrixNumerical<float> flottants(std::vector<std::vector<float> >{{0.5f, 0}, {0, 2}});
    verifier(flottants.getDeterminant() == 1
             && flottants.getInverse().getElement(0, 0) == 2, "type float");
    MatrixNumerical<double> petit(std::vector<std::vector<double> >{{1e-12}});
    verifier(std::abs(petit.getInverse().getElement(0, 0) / 1e12 - 1) < 1e-9,
             "petit determinant non nul accepte");
    MatrixNumerical<int> rectangle(std::vector<std::vector<int> >{{1, 2, 3}, {4, 5, 6}});
    MatrixNumerical<int> colonne(std::vector<std::vector<int> >{{1}, {2}, {3}});
    verifier(egales(rectangle * colonne, MatrixNumerical<int>(std::vector<std::vector<int> >{{14}, {32}})),
             "produit 2 x 3 par 3 x 1");
    verifier(egales(rectangle + rectangle - rectangle, rectangle), "addition et soustraction rectangulaires");
    verifier(egales(rectangle / MatrixNumerical<int>::getIdentity(3), rectangle), "division d'une matrice rectangulaire");
    verifier(egales(MatrixNumerical<int>::getIdentity(3), MatrixNumerical<int>(std::vector<std::vector<int> >
             {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}})), "identite 3 x 3");
    MatrixNumerical<int> videNumerique;
    verifier(videNumerique.getDeterminant() == 1 && (videNumerique + videNumerique).getRows() == 0,
             "convention determinant vide et addition vide");

    // Chaque operation invalide doit lever l'exception prevue.
    bool detectee = false;
    try { rectangle.getDeterminant(); }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "determinant non carre refuse");
    detectee = false;
    try { rectangle.getInverse(); }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "inverse non carre refuse");
    MatrixNumerical<int> singuliere(std::vector<std::vector<int> >{{1, 2}, {2, 4}});
    verifier(singuliere.getDeterminant() == 0, "determinant nul");
    detectee = false;
    try { singuliere.getInverse(); }
    catch (const std::domain_error&) { detectee = true; }
    verifier(detectee, "inverse singulier refuse");
    detectee = false;
    try { a / singuliere; }
    catch (const std::domain_error&) { detectee = true; }
    verifier(detectee, "division par une matrice singuliere refusee");
    detectee = false;
    try { a + rectangle; }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "addition incompatible refusee");
    detectee = false;
    try { a - rectangle; }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "soustraction incompatible refusee");
    detectee = false;
    try { rectangle * a; }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "produit incompatible refuse");
    detectee = false;
    try { rectangle / a; }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "division incompatible refusee");
    detectee = false;
    try { a / rectangle; }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "diviseur non carre refuse");
    detectee = false;
    try { zeros.getElement(2, 0); }
    catch (const std::out_of_range&) { detectee = true; }
    verifier(detectee, "lecture hors limites refusee");
    detectee = false;
    try { zeros.addElement(0, 3, 8); }
    catch (const std::out_of_range&) { detectee = true; }
    verifier(detectee, "ecriture hors limites refusee");
    detectee = false;
    try { MatrixBase<int> irreguliere(std::vector<std::vector<int> >{{1}, {2, 3}}); }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "lignes de longueurs differentes refusees");
    detectee = false;
    try { MatrixNumerical<int>::getIdentity(-1); }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "identite de taille negative refusee");
    detectee = false;
    try { MatrixNumerical<int>::getIdentity(0); }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "identite de taille nulle refusee");
    detectee = false;
    try { videNumerique.getInverse(); }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "inverse vide refuse");
    detectee = false;
    try { getCoFactor(a, 2, 0); }
    catch (const std::out_of_range&) { detectee = true; }
    verifier(detectee, "cofacteur hors limites refuse");
    detectee = false;
    try { getCoFactor(rectangle, 0, 0); }
    catch (const std::invalid_argument&) { detectee = true; }
    verifier(detectee, "cofacteur non carre refuse");

    std::cout << "\nA :\n";
    a.Display();
    std::cout << "Inverse de A :\n";
    a.getInverse().Display();
    std::cout << tests << " verifications, " << erreurs << " erreur(s)\n";
    return erreurs == 0 ? 0 : 1;
}

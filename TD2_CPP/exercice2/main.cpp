#include "MatrixNumerical.h"
#include <iostream>

int main()
{
    MatrixNumerical<double> a(2, 2);
    a.addElement(0, 0, 4);
    a.addElement(0, 1, 7);
    a.addElement(1, 0, 2);
    a.addElement(1, 1, 6);

    MatrixNumerical<double> b(std::vector<std::vector<double> >{{1, 2}, {3, 4}});
    MatrixNumerical<double> vide;
    MatrixNumerical<double> copie(a);

    std::cout << "Matrice vide : " << vide.getRows() << " x " << vide.getCols() << '\n';
    std::cout << "A :\n";
    a.Display();
    std::cout << "Dimensions de A : " << a.getRows() << " x " << a.getCols() << '\n';
    std::cout << "Element A(0, 1) : " << a.getElement(0, 1) << '\n';
    std::cout << "Copie de A :\n";
    copie.Display();
    std::cout << "B :\n";
    b.Display();

    std::cout << "A + B :\n";
    (a + b).Display();
    std::cout << "A - B :\n";
    (a - b).Display();
    std::cout << "A * B :\n";
    (a * b).Display();

    std::cout << "Determinant de A : " << a.getDeterminant() << '\n';
    std::cout << "Cofacteur A(0, 1) : " << getCoFactor(a, 0, 1) << '\n';
    std::cout << "Inverse de A :\n";
    a.getInverse().Display();
    std::cout << "A / B :\n";
    (a / b).Display();
    std::cout << "Identite :\n";
    MatrixNumerical<double>::getIdentity(2).Display();
    std::cout << "A * inverse(A) :\n";
    (a * a.getInverse()).Display();

    return 0;
}

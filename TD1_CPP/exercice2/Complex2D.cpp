#include "Complex2D.h"
#include <cmath>
#include <stdexcept>

Complex2D::Complex2D() : reel(0), imaginaire(0) {}
Complex2D::Complex2D(double r, double i) : reel(r), imaginaire(i) {}
Complex2D::Complex2D(double valeur) : reel(valeur), imaginaire(valeur) {}
Complex2D::Complex2D(const Complex2D& autre)
    : reel(autre.reel), imaginaire(autre.imaginaire) {}

double Complex2D::getReel() const { return reel; }
double Complex2D::getImaginaire() const { return imaginaire; }
void Complex2D::setReel(double r) { reel = r; }
void Complex2D::setImaginaire(double i) { imaginaire = i; }

Complex2D Complex2D::operator+(const Complex2D& autre) const
{
    return Complex2D(reel + autre.reel, imaginaire + autre.imaginaire);
}

Complex2D Complex2D::operator-(const Complex2D& autre) const
{
    return Complex2D(reel - autre.reel, imaginaire - autre.imaginaire);
}

Complex2D Complex2D::operator*(const Complex2D& autre) const
{
    // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    return Complex2D(reel * autre.reel - imaginaire * autre.imaginaire,
                     reel * autre.imaginaire + imaginaire * autre.reel);
}

Complex2D Complex2D::operator/(const Complex2D& autre) const
{
    double denominateur = autre.reel * autre.reel
                        + autre.imaginaire * autre.imaginaire;
    if (denominateur == 0)
        throw std::domain_error("Division par le complexe nul");
    return Complex2D((reel * autre.reel + imaginaire * autre.imaginaire) / denominateur,
                     (imaginaire * autre.reel - reel * autre.imaginaire) / denominateur);
}

bool Complex2D::operator<(const Complex2D& autre) const
{
    return module() < autre.module();
}

bool Complex2D::operator>(const Complex2D& autre) const
{
    return module() > autre.module();
}

Complex2D& Complex2D::operator=(const Complex2D& autre)
{
    reel = autre.reel;
    imaginaire = autre.imaginaire;
    return *this;
}

bool Complex2D::operator==(const Complex2D& autre) const
{
    return reel == autre.reel && imaginaire == autre.imaginaire;
}

bool Complex2D::operator!=(const Complex2D& autre) const
{
    return !(*this == autre);
}

double Complex2D::module() const
{
    return std::sqrt(reel * reel + imaginaire * imaginaire);
}

Complex2D Complex2D::conjugue() const
{
    return Complex2D(reel, -imaginaire);
}

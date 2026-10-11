#ifndef COMPLEX2D_H
#define COMPLEX2D_H

class Complex2D
{
private:
    double reel;
    double imaginaire;
public:
    Complex2D();
    Complex2D(double r, double i);
    Complex2D(double valeur);
    Complex2D(const Complex2D& autre);

    double getReel() const;
    double getImaginaire() const;
    void setReel(double r);
    void setImaginaire(double i);

    Complex2D operator+(const Complex2D& autre) const;
    Complex2D operator-(const Complex2D& autre) const;
    Complex2D operator*(const Complex2D& autre) const;
    Complex2D operator/(const Complex2D& autre) const;
    // Convention du TD : comparaison des modules.
    bool operator<(const Complex2D& autre) const;
    bool operator>(const Complex2D& autre) const;

    // Ajouts proposes pour la derniere question.
    Complex2D& operator=(const Complex2D& autre);
    bool operator==(const Complex2D& autre) const;
    bool operator!=(const Complex2D& autre) const;
    double module() const;
    Complex2D conjugue() const;
};

#endif

#ifndef MATRIX_NUMERICAL_H
#define MATRIX_NUMERICAL_H

#include "MatrixBase.h"

template<class T> class MatrixNumerical;
template<class T>
T getCoFactor(const MatrixNumerical<T>& matrice, std::size_t ligne, std::size_t colonne);

template<class T>
class MatrixNumerical : public MatrixBase<T>
{
public:
    MatrixNumerical();
    MatrixNumerical(std::size_t lignes, std::size_t colonnes);
    MatrixNumerical(const std::vector<std::vector<T> >& valeurs);
    T getDeterminant() const;
    MatrixNumerical operator+(const MatrixNumerical& autre) const;
    MatrixNumerical operator-(const MatrixNumerical& autre) const;
    MatrixNumerical operator*(const MatrixNumerical& autre) const;
    MatrixNumerical<double> getInverse() const;
    MatrixNumerical<double> operator/(const MatrixNumerical& autre) const;
    static MatrixNumerical getIdentity(int taille);
};

template<class T>
MatrixNumerical<T>::MatrixNumerical() : MatrixBase<T>() {}

template<class T>
MatrixNumerical<T>::MatrixNumerical(std::size_t lignes, std::size_t colonnes)
    : MatrixBase<T>(lignes, colonnes) {}

template<class T>
MatrixNumerical<T>::MatrixNumerical(const std::vector<std::vector<T> >& valeurs)
    : MatrixBase<T>(valeurs) {}

template<class T>
T MatrixNumerical<T>::getDeterminant() const
{
    if (this->rows != this->cols)
        throw std::invalid_argument("Le determinant exige une matrice carree");
    if (this->rows == 0)
        return T(1);
    if (this->rows == 1)
        return this->data[0][0];
    if (this->rows == 2)
        return this->data[0][0] * this->data[1][1]
             - this->data[0][1] * this->data[1][0];
    T determinant = T();
    for (std::size_t j = 0; j < this->cols; ++j)
        determinant += this->data[0][j] * getCoFactor(*this, 0, j);
    return determinant;
}

template<class T>
T getCoFactor(const MatrixNumerical<T>& matrice, std::size_t ligne, std::size_t colonne)
{
    if (matrice.getRows() != matrice.getCols())
        throw std::invalid_argument("Le cofacteur exige une matrice carree");
    if (ligne >= matrice.getRows() || colonne >= matrice.getCols())
        throw std::out_of_range("Indice de cofacteur invalide");
    MatrixNumerical<T> mineur(matrice.getRows() - 1, matrice.getCols() - 1);
    std::size_t ligneMineur = 0;
    for (std::size_t i = 0; i < matrice.getRows(); ++i)
    {
        if (i == ligne)
            continue;
        std::size_t colonneMineur = 0;
        for (std::size_t j = 0; j < matrice.getCols(); ++j)
        {
            if (j == colonne)
                continue;
            mineur.addElement(ligneMineur, colonneMineur, matrice.getElement(i, j));
            ++colonneMineur;
        }
        ++ligneMineur;
    }
    T determinant = mineur.getDeterminant();
    if ((ligne + colonne) % 2 == 0)
        return determinant;
    return -determinant;
}

template<class T>
MatrixNumerical<T> MatrixNumerical<T>::operator+(const MatrixNumerical& autre) const
{
    if (this->rows != autre.rows || this->cols != autre.cols)
        throw std::invalid_argument("Addition : dimensions incompatibles");
    MatrixNumerical resultat(this->rows, this->cols);
    for (std::size_t i = 0; i < this->rows; ++i)
        for (std::size_t j = 0; j < this->cols; ++j)
            resultat.data[i][j] = this->data[i][j] + autre.data[i][j];
    return resultat;
}

template<class T>
MatrixNumerical<T> MatrixNumerical<T>::operator-(const MatrixNumerical& autre) const
{
    if (this->rows != autre.rows || this->cols != autre.cols)
        throw std::invalid_argument("Soustraction : dimensions incompatibles");
    MatrixNumerical resultat(this->rows, this->cols);
    for (std::size_t i = 0; i < this->rows; ++i)
        for (std::size_t j = 0; j < this->cols; ++j)
            resultat.data[i][j] = this->data[i][j] - autre.data[i][j];
    return resultat;
}

template<class T>
MatrixNumerical<T> MatrixNumerical<T>::operator*(const MatrixNumerical& autre) const
{
    if (this->cols != autre.rows)
        throw std::invalid_argument("Multiplication : dimensions incompatibles");
    MatrixNumerical resultat(this->rows, autre.cols);
    for (std::size_t i = 0; i < this->rows; ++i)
        for (std::size_t j = 0; j < autre.cols; ++j)
            for (std::size_t k = 0; k < this->cols; ++k)
                resultat.data[i][j] += this->data[i][k] * autre.data[k][j];
    return resultat;
}

template<class T>
MatrixNumerical<double> MatrixNumerical<T>::getInverse() const
{
    if (this->rows != this->cols || this->rows == 0)
        throw std::invalid_argument("L'inverse exige une matrice carree non vide");
    MatrixNumerical<double> matrice(this->rows, this->cols);
    for (std::size_t i = 0; i < this->rows; ++i)
        for (std::size_t j = 0; j < this->cols; ++j)
            matrice.addElement(i, j, (double) this->data[i][j]);
    double determinant = matrice.getDeterminant();
    if (determinant == 0)
        throw std::domain_error("Matrice non inversible : determinant nul");
    MatrixNumerical<double> inverse(this->rows, this->cols);
    for (std::size_t i = 0; i < this->rows; ++i)
        for (std::size_t j = 0; j < this->cols; ++j)
            inverse.addElement(j, i, getCoFactor(matrice, i, j) / determinant);
    return inverse;
}

template<class T>
MatrixNumerical<double> MatrixNumerical<T>::operator/(const MatrixNumerical& autre) const
{
    if (this->cols != autre.rows)
        throw std::invalid_argument("Division : dimensions incompatibles");
    MatrixNumerical<double> inverse = autre.getInverse();
    MatrixNumerical<double> gauche(this->rows, this->cols);
    for (std::size_t i = 0; i < this->rows; ++i)
        for (std::size_t j = 0; j < this->cols; ++j)
            gauche.addElement(i, j, (double) this->data[i][j]);
    return gauche * inverse;
}

template<class T>
MatrixNumerical<T> MatrixNumerical<T>::getIdentity(int taille)
{
    if (taille <= 0)
        throw std::invalid_argument("La taille de l'identite doit etre positive");
    MatrixNumerical identite(taille, taille);
    for (int i = 0; i < taille; ++i)
        identite.data[i][i] = T(1);
    return identite;
}

#endif

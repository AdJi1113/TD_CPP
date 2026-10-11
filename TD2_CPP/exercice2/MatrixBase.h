#ifndef MATRIX_BASE_H
#define MATRIX_BASE_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

template<class T>
class MatrixBase
{
protected:
    std::vector<std::vector<T> > data;
    std::size_t rows;
    std::size_t cols;
public:
    MatrixBase();
    MatrixBase(std::size_t lignes, std::size_t colonnes);
    MatrixBase(const std::vector<std::vector<T> >& valeurs);
    void addElement(std::size_t ligne, std::size_t colonne, const T& valeur);
    T getElement(std::size_t ligne, std::size_t colonne) const;
    std::size_t getRows() const;
    std::size_t getCols() const;
    void Display(std::ostream& os = std::cout) const;
};

template<class T>
MatrixBase<T>::MatrixBase() : rows(0), cols(0) {}

template<class T>
MatrixBase<T>::MatrixBase(std::size_t lignes, std::size_t colonnes)
    : data(lignes, std::vector<T>(colonnes, T())), rows(lignes), cols(colonnes) {}

template<class T>
MatrixBase<T>::MatrixBase(const std::vector<std::vector<T> >& valeurs)
    : data(valeurs), rows(valeurs.size()), cols(valeurs.empty() ? 0 : valeurs[0].size())
{
    for (std::size_t i = 0; i < rows; ++i)
        if (data[i].size() != cols)
            throw std::invalid_argument("Les lignes doivent avoir la meme taille");
}

template<class T>
void MatrixBase<T>::addElement(std::size_t ligne, std::size_t colonne, const T& valeur)
{
    if (ligne >= rows || colonne >= cols)
        throw std::out_of_range("Indice de matrice invalide");
    data[ligne][colonne] = valeur;
}

template<class T>
T MatrixBase<T>::getElement(std::size_t ligne, std::size_t colonne) const
{
    if (ligne >= rows || colonne >= cols)
        throw std::out_of_range("Indice de matrice invalide");
    return data[ligne][colonne];
}

template<class T>
std::size_t MatrixBase<T>::getRows() const { return rows; }

template<class T>
std::size_t MatrixBase<T>::getCols() const { return cols; }

template<class T>
void MatrixBase<T>::Display(std::ostream& os) const
{
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
            os << data[i][j] << (j + 1 == cols ? "" : " ");
        os << '\n';
    }
}

#endif

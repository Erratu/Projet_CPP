#pragma once

#include <initializer_list>
#include <algorithm>
#include <iostream>

/**
 * @brief Classe représentant un vecteur dans un espace de dimension D
 *
 * Cette classe permet de représenter un vecteur dans un espace de dimension D
 * et de réaliser des opérations sur ces vecteurs.
 * @tparam D Dimension de l’espace (2D, 3D…)
 */
template<int D>
class Vecteur {
public:
    double coords[D];

    /**
     * @brief Constructeur par défaut
     * 
     * Initialise tous les coordonnées à 0.0
     */
    Vecteur() {
        for (int i = 0; i < D; ++i)
            coords[i] = 0.0;
    }

    /**
     * @brief Constructeur à partir d'un tableau
     * @param val Tableau de D coordonnées
     */
    Vecteur(const double val[D]) {
        for (int i = 0; i < D; ++i)
            coords[i] = val[i];
    }

    /**
     * @brief Constructeur à partir d'une liste d'initialisation
     * @param vals Liste des valeurs à initialiser
     */
    Vecteur(std::initializer_list<double> vals) {
        int i = 0;
        for (double v : vals) {
            if (i < D) coords[i++] = v;
        }
        for (; i < D; ++i)
            coords[i] = 0.0;
    }

    /**
     * @brief Constructeur de copie
     * @param v Vecteur à copier
     */
    Vecteur(const Vecteur& v) {
        for (int i = 0; i < D; ++i)
            coords[i] = v.coords[i];
    }

    ~Vecteur() = default;

    /**
     * @brief Opérateur d'assignation
     * @param autre Vecteur à assigner
     * @return Référence à ce vecteur
     */
    Vecteur& operator=(const Vecteur& autre) {
        if (this != &autre) {
            for (int i = 0; i < D; ++i)
                coords[i] = autre.coords[i];
        }
        return *this;
    }

    Vecteur& operator+=(const Vecteur& autre) {
        for (int i = 0; i < D; ++i)
            coords[i] += autre.coords[i];
        return *this;
    }

    Vecteur& operator-=(const Vecteur& autre) {
        for (int i = 0; i < D; ++i)
            coords[i] -= autre.coords[i];
        return *this;
    }

    Vecteur& operator*=(double scalaire) {
        for (int i = 0; i < D; ++i)
            coords[i] *= scalaire;
        return *this;
    }

    /**
     * @brief Accès aux coordonnées avec indice
     * @param i Indice de la coordonnée
     * @return Référence à la coordonnée
     */
    double& operator[](int i) { return coords[i]; }
    const double& operator[](int i) const { return coords[i]; }
};

template<int D>
Vecteur<D> operator+(Vecteur<D> v1, const Vecteur<D>& v2) {
    v1 += v2;
    return v1;
}

template<int D>
Vecteur<D> operator-(Vecteur<D> v1, const Vecteur<D>& v2) {
    v1 -= v2;
    return v1;
}

template<int D>
Vecteur<D> operator*(Vecteur<D> v, double scalaire) {
    v *= scalaire;
    return v;
}

template<int D>
Vecteur<D> operator*(double scalaire, Vecteur<D> v) {
    return v * scalaire;
}

template<int D>
std::ostream& operator<<(std::ostream& os, const Vecteur<D>& v) {
    os << "(";
    for (int i = 0; i < D; ++i) {
        os << v.coords[i];
        if (i < D - 1) os << ", ";
    }
    os << ")";
    return os;
}

template<int D>
std::istream& operator>>(std::istream& is, Vecteur<D>& v) {
    for (int i = 0; i < D; ++i)
        is >> v.coords[i];
    return is;
}
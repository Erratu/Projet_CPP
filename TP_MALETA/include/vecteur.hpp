#pragma once

#include <initializer_list>
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
private:
    double coords[D];

public:
    // Constructors and destructor
    Vecteur();
    Vecteur(const double val[D]);
    Vecteur(std::initializer_list<double> vals);
    Vecteur(const Vecteur& v);
    ~Vecteur() = default;

    // Operators 
    Vecteur& operator=(const Vecteur& autre);
    Vecteur& operator+=(const Vecteur& autre);
    Vecteur& operator-=(const Vecteur& autre);
    Vecteur& operator*=(double scalaire);
    Vecteur operator-() const;
    bool operator==(const Vecteur& autre) const;
    bool operator!=(const Vecteur& autre) const;

    // Accessors
    double& operator[](int i) { return coords[i]; }
    const double& operator[](int i) const { return coords[i]; }

    // I/O stream operators
    template<int Dim>
    friend std::ostream& operator<<(std::ostream& os, const Vecteur<Dim>& v);
    
    template<int Dim>
    friend std::istream& operator>>(std::istream& is, Vecteur<Dim>& v);
};

// Binary operators
template<int D> Vecteur<D> operator+(Vecteur<D> v1, const Vecteur<D>& v2);
template<int D> Vecteur<D> operator-(Vecteur<D> v1, const Vecteur<D>& v2);
template<int D> Vecteur<D> operator*(Vecteur<D> v, double scalaire);
template<int D> Vecteur<D> operator*(double scalaire, Vecteur<D> v);

#include "../src/vecteur.tpp"
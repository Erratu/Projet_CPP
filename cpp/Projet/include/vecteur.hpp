#pragma once

#include <initializer_list>
#include <algorithm>
#include <iostream>

template<int D>
class Vecteur {
public:
    double coords[D];

    Vecteur() {
        for (int i = 0; i < D; ++i)
            coords[i] = 0.0;
    }

    Vecteur(const double val[D]) {
        for (int i = 0; i < D; ++i)
            coords[i] = val[i];
    }

    Vecteur(std::initializer_list<double> vals) {
        int i = 0;
        for (double v : vals) {
            if (i < D) coords[i++] = v;
        }
        for (; i < D; ++i)
            coords[i] = 0.0;
    }

    Vecteur(const Vecteur& v) {
        for (int i = 0; i < D; ++i)
            coords[i] = v.coords[i];
    }

    ~Vecteur() = default;

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
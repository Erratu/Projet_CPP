#include "vecteur.hpp"

template <int D>
Vecteur<D>& Vecteur<D>::operator=(const Vecteur<D>& autre) {
    if (this != &autre) {
        for (int i = 0; i < D; ++i) {
            coords[i] = autre.coords[i];
        }
    }
    return *this;
}

template <int D>
Vecteur<D>& Vecteur<D>::operator+=(const Vecteur<D>& autre) {
    for (int i = 0; i < D; ++i) {
        coords[i] += autre.coords[i];
    }
    return *this;
};

template <int D>
Vecteur<D>& Vecteur<D>::operator-=(const Vecteur<D>& autre) {
    for (int i = 0; i < D; ++i) {
        coords[i] -= autre.coords[i];
    }
    return *this;
};

template <int D>
Vecteur<D>& Vecteur<D>::operator*=(double scalaire) {
    for (int i = 0; i < D; ++i) {
        coords[i] *= scalaire;
    }
    return *this;
};

template <int D>
Vecteur<D> operator+(Vecteur<D> v1, const Vecteur<D>& v2) {
    v1 += v2;
    return v1;
};

template <int D>
Vecteur<D> operator-(Vecteur<D> v1, const Vecteur<D>& v2) {
    v1 -= v2;
    return v1;
};

template <int D>
Vecteur<D> operator*(Vecteur<D> v, double scalaire) {
    v *= scalaire;
    return v;
};

template <int D>
Vecteur<D> operator*(double scalaire, const Vecteur<D>& v) {
    return v * scalaire;
};

template <int D>
std::ostream& operator<<(std::ostream& os, const Vecteur<D>& v) {
    os << "(" << v.pos.x << ", " << v.pos.y << ", " << v.pos.z << ")";
    return os;
}

template <int D>
std::istream& operator>>(std::istream& is, Vecteur<D>& v) {
    is >> v.pos.x >> v.pos.y >> v.pos.z;
    return is;
}

template <int D>
void Vecteur<D>::afficher() const
{
    std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
}
#include "vecteur.hpp"
#include <iostream>

Vecteur& operator=(const Vecteur& autre) {
    if (this != &v) {
        x = autre.x;
        y = autre.y;
        z = autre.z;
    }
    return *this;
}

Vecteur operator+=(const Vecteur& autre) {
    x += autre.x;
    y += autre.y;
    z += autre.z;
    return *this;
};

Vecteur operator-=(const Vecteur& autre) {
    x -= autre.x;
    y -= autre.y;
    z -= autre.z;
    return *this;
};

Vecteur operator*=(double scalaire) {
    x *= scalaire;
    y *= scalaire;
    z *= scalaire;
    return *this;
};

friend Vecteur operator+(Vecteur v1, const Vecteur& v2) {
    v1 += v2;
    return v1;
};

friend Vecteur operator-(Vecteur v1, const Vecteur& v2) {
    v1 -= v2;
    return v1;
};

friend Vecteur operator*(Vecteur v, double scalaire) {
    v *= scalaire;
    return v;
};

friend Vecteur operator*(double scalaire, const Vecteur& v) {
    return v * scalaire;
};

friend std::ostream& operator<<(std::ostream& os, const Vecteur& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

friend std::istream& operator<<(std::istream& is, Vecteur& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

void Vecteur::afficher() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}
#include "vecteur.hpp"

Vecteur& Vecteur::operator=(const Vecteur& autre) {
    if (this != &autre) {
        x = autre.x;
        y = autre.y;
        z = autre.z;
    }
    return *this;
}

Vecteur& Vecteur::operator+=(const Vecteur& autre) {
    x += autre.x;
    y += autre.y;
    z += autre.z;
    return *this;
};

Vecteur& Vecteur::operator-=(const Vecteur& autre) {
    x -= autre.x;
    y -= autre.y;
    z -= autre.z;
    return *this;
};

Vecteur& Vecteur::operator*=(double scalaire) {
    x *= scalaire;
    y *= scalaire;
    z *= scalaire;
    return *this;
};

Vecteur operator+(Vecteur v1, const Vecteur& v2) {
    v1 += v2;
    return v1;
};

Vecteur operator-(Vecteur v1, const Vecteur& v2) {
    v1 -= v2;
    return v1;
};

Vecteur operator*(Vecteur v, double scalaire) {
    v *= scalaire;
    return v;
};

Vecteur operator*(double scalaire, const Vecteur& v) {
    return v * scalaire;
};

std::ostream& operator<<(std::ostream& os, const Vecteur& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Vecteur& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

void Vecteur::afficher() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}
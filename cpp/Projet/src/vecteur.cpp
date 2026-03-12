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

friend Vecteur operator+(Vecteur v1, const Vecteur& v2) {
    v1 += v2;
    return v1;
};

Vecteur operator-=(const Vecteur& autre) const {
    x -= autre.x;
    y -= autre.y;
    z -= autre.z;
    return *this;
};

friend Vecteur operator-(Vecteur v1, const Vecteur& v2) {
    v1 -= v2;
    return v1;
};

friend Vecteur operator*(double scalaire, const Vecteur& v) {
    
};

double produitScalaire(const Vecteur& autre) const {
    
};

void Vecteur::afficher() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}
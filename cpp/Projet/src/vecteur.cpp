#include "vecteur.hpp"
#include <iostream>

Vecteur operator+(const Vecteur& v) const {

};
Vecteur operator-(const Vecteur& v) const {
    
};
Vecteur operator*(double scalaire) const {

};

float produitScalaire(const Vecteur& v) const {
    
};

void Vecteur::afficher() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}
#include "vecteur.hpp"
#include <iostream>

int main()
{
    // Test constructeur
    Vecteur v1;
    Vecteur v2(1, 2, 3);
    Vecteur v3(4, 5, 6);

    std::cout << "Vecteur v1 : ";
    v1.afficher();

    std::cout << "Vecteur v2 : ";
    v2.afficher();

    std::cout << "Vecteur v3 : ";
    v3.afficher();

    // Test addition
    Vecteur v4 = v2 + v3;
    std::cout << "v2 + v3 = ";
    v4.afficher();

    // Test soustraction
    Vecteur v5 = v3 - v2;
    std::cout << "v3 - v2 = ";
    v5.afficher();

    // Test multiplication scalaire
    Vecteur v6 = v2 * 2;
    std::cout << "v2 * 2 = ";
    v6.afficher();

    // Test produit scalaire
    // double ps = v2.produitScalaire(v3);
    // std::cout << "Produit scalaire v2.v3 = " << ps << std::endl;

    return 0;
}

//Vecteur v1 : (0, 0, 0)
//Vecteur v2 : (1, 2, 3)
//Vecteur v3 : (4, 5, 6)
//v2 + v3 = (5, 7, 9)
//v3 - v2 = (3, 3, 3)
//v2 * 2 = (2, 4, 6)
//Produit scalaire v2.v3 = 32
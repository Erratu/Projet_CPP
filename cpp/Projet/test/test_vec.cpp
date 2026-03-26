#include "vecteur.hpp"
#include <iostream>

int main()
{
    // Test constructeur
    Vecteur<3> v1;
    Vecteur<3> v2{1, 2, 3};
    Vecteur<3> v3{4, 5, 6};

    std::cout << "Vecteur v1 : ";
    std::cout << v1 << std::endl;

    std::cout << "Vecteur v2 : ";
    std::cout << v2 << std::endl;

    std::cout << "Vecteur v3 : ";
    std::cout << v3 << std::endl;

    // Test addition
    Vecteur<3> v4 = v2 + v3;
    std::cout << "v2 + v3 = ";
    std::cout << v4 << std::endl;

    // Test soustraction
    Vecteur<3> v5 = v3 - v2;
    std::cout << "v3 - v2 = ";
    std::cout << v5 << std::endl;

    // Test multiplication scalaire
    Vecteur<3> v6 = v2 * 2;
    std::cout << "v2 * 2 = ";
    std::cout << v6 << std::endl;

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
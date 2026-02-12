#include "particule.hpp"
#include <iostream>

void Particule::afficher() {
    std::cout << "Particule " << id << ": (" << x << ", " << y << ", " << z << ")\n";
};
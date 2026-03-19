#include "particule.hpp"
#include <iostream>

void Particule::afficher() {
    std::cout << "Particule " << id << ": (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
};
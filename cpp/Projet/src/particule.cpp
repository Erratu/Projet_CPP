#include "particule.hpp"
#include <iostream>

template <int D>
void Particule<D>::afficher() {
    std::cout << "Particule " << id << ": (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
};
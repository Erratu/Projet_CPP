#include "particule.hpp"
#include <iostream>

template<int D>
void Particule<D>::afficher() {
        std::cout << "Particule " << id << ": " << pos << "\n";
}

template class Particule<3>;
template class Particule<2>;
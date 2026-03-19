#include <list>

#include "univers.hpp"

int main() {

    std::list<Particule<2>> particleList;

    // Soleil
    particleList.emplace_back(
        Vecteur<2>(),
        Vecteur<2>(),
        1.0,
        0, "Soleil"
    );

    // Terre
    particleList.emplace_back(
        0.0, 1.0, 0.0,
        -1.0, 0.0, 0.0,
        3.0e-6,
        1, "Terre"
    );

    // Jupiter
    particleList.emplace_back(
        0.0, 5.36, 0.0,
        -0.425, 0.0, 0.0,
        9.55e-4,
        2, "Jupiter"
    );

    // Halley
    particleList.emplace_back(
        34.75, 0.0, 0.0,
        0.0, 0.0296, 0.0,
        1e-14,
        3, "Halley"
    );

    Univers u1{particleList};

    for (auto& p : u1.particules) { 
        p.afficher();
    }

    u1.algoStormerVerlet();

    for (auto& p : u1.particules) { 
        p.afficher();
    }

        return 0;
}
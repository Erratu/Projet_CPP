#include <list>

#include "univers.hpp"

int main() {

    std::list<Particule<2>> particleList;

    // Soleil
    particleList.emplace_back(
        Particule<2>{
        Vecteur<2>{0.0, 0.0},
        Vecteur<2>{0.0, 0.0},
        1.0,
        0, "Soleil"
        }
    );

    // Terre
    particleList.emplace_back(
        Particule<2>{
        Vecteur<2>{0.0, 1.0},
        Vecteur<2>{-1.0, 0.0},
        3.0e-6,
        1, "Terre"
        }
    );

    // Jupiter
    particleList.emplace_back(
        Particule<2>{
        Vecteur<2>{0.0, 5.36},
        Vecteur<2>{-0.425, 0.0},
        9.55e-4,
        2, "Jupiter"
        }
    );

    // Halley
    particleList.emplace_back(
        Particule<2>{
        Vecteur<2>{34.75, 0.0},
        Vecteur<2>{0.0, 0.0296},
        1e-14,
        3, "Halley"
        }
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
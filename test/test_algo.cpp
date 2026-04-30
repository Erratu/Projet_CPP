#include <list>

#include "univers.hpp"

/**
 * @brief Test de simulation du système solaire
 * 
 * Crée un univers 2D contenant le soleil, la terre, jupiter et la comète de halley 
 * avec des positions et vitesses initiales réalistes.
 * Lance une simulation utilisant l'algorithme de Stormer-Verlet.
 * 
 * @return 0 si l'exécution s'est déroulée correctement
 */
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

    Univers u1{particleList, Vecteur<2>{50.0, 50.0}};

    for (auto& p : u1) { 
        p.afficher();
    }

    u1.algoStormerVerlet();

    for (auto& p : u1) { 
        p.afficher();
    }

        return 0;
}
#include <iostream>
#include <random>
#include <chrono>
#include "univers.hpp"

/**
 * @brief Calcule une puissance entière
 * @param base La base
 * @param exp L'exposant
 * @return base^exp
 */
int powInt(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; ++i)
        res *= base;
    return res;
}

/**
 * @brief Tests (notamment de performance) pour la classe Univers et l'algorithme Stormer-Verlet
 * 
 * Crée un univers de 2^3 = 8 particules, affiche leurs propriétés,
 * exécute la simulation de l'algorithme de Stormer-Verlet et affiche
 * le temps d'exécution.
 * 
 * @return 0 si l'exécution s'est déroulée correctement
 */
int main() {
    const int nb_particules = powInt(2, 3); 
    auto start = std::chrono::steady_clock::now();
    Univers<3> u1(nb_particules);

    for (auto& p : u1) { 
        p.afficher();
    } // elapsed time: 0.320668s pour 2^15

    u1.algoStormerVerlet();

    for (auto& p : u1) { 
        p.afficher();
    } // 2^9 : elapsed time: 577.576s trop long, à revoir. gprof

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
#include <iostream>
#include <random>
#include <chrono>
#include "univers.hpp"

int powInt(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; ++i)
        res *= base;
    return res;
}

int main() {
    const int nb_particules = powInt(2, 3); 
    auto start = std::chrono::steady_clock::now();
    Univers<3> u1(nb_particules);

    for (auto& p : u1.particules) { 
        p.afficher();
    } // elapsed time: 0.320668s pour 2^15

    u1.algoStormerVerlet();

    for (auto& p : u1.particules) { 
        p.afficher();
    } // 2^9 : elapsed time: 577.576s trop long, à revoir

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
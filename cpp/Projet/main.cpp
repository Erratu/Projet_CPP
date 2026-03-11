#include <random>
#include <chrono>
#include <iostream>
#include <list>

#include "particule.hpp"

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    //auto start = std::chrono::steady_clock::now();
    
    Univers u1 = new Univers(2);

    for (auto& p : u1.particules) { 
        p.afficher();
    }

    sys_base_test();

    //auto end = std::chrono::steady_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end-start;
    //std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}

void sys_base_test() {
    // Soleil
    particleList.emplace_back(
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
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

    Univers u2 = new Univers(particleList);

    for (auto& p : u2.particules) { 
        p.afficher();
    }

    u2.algoStormerVerlet();

    for (auto& p : u2.particules) { 
        p.afficher();
    }
}
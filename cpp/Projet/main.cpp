#include <random>
#include <chrono>
#include <iostream>
#include <list>

#include "univers.hpp"

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    //auto start = std::chrono::steady_clock::now();
    
    Univers<3> u1{2};

    for (auto& p : u1.particules) { 
        p.afficher();
    }

    //auto end = std::chrono::steady_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end-start;
    //std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}

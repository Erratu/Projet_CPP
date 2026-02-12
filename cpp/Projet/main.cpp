#include <random>
#include <chrono>
#include <iostream>
#include <list>

#include "include/particule.hpp"

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    //auto start = std::chrono::steady_clock::now();
    
    std::list<Particule> particleList;

    for (int i=0; i<2; ++i) {
        particleList.emplace_back(dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), i, "Ab", dist(mt), dist(mt), dist(mt));
    };

    for (auto& p : particleList) { 
        p.afficher();
    }

    //auto end = std::chrono::steady_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end-start;
    //std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
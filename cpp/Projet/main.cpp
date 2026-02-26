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

void StrömerVerlet(std::list<Particule>& particleList, float dt) {
    for (auto& p : particleList) {
        // Mise à jour de la position
        p.x += p.vx * dt + 0.5f * p.forceX / p.masse * dt * dt;
        p.y += p.vy * dt + 0.5f * p.forceY / p.masse * dt * dt;
        p.z += p.vz * dt + 0.5f * p.forceZ / p.masse * dt * dt;

        // Mise à jour de la vitesse
        p.vx += 0.5f * p.forceX / p.masse * dt;
        p.vy += 0.5f * p.forceY / p.masse * dt;
        p.vz += 0.5f * p.forceZ / p.masse * dt;
    }
}
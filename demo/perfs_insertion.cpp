#include <iostream>
#include <chrono>
#include <list>
#include <vector>
#include <cmath>
#include "univers.hpp"

int main() {
    int N = std::pow(2, 5); // 32
    int total_particules = N * N * N; // 32 768 particules
    std::cout << "Test d'insertion de " << total_particules << " particules avec une list et un vector\n";

    // Test avec std::list
    auto start_list = std::chrono::steady_clock::now();
    std::list<Particule<3>> liste;
    for(int i = 0; i < total_particules; ++i) {
        liste.emplace_back(Particule<3>{Vecteur<3>{0,0,0}, Vecteur<3>{0,0,0}, 1.0, i, "P"});
    }
    auto end_list = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff_list = end_list - start_list;
    std::cout << "Temps (std::list) : " << diff_list.count() << " s\n";

    // Test avec std::vector
    auto start_vec = std::chrono::steady_clock::now();
    std::vector<Particule<3>> vecteur;
    vecteur.reserve(total_particules);
    for(int i = 0; i < total_particules; ++i) {
        vecteur.emplace_back(Particule<3>{Vecteur<3>{0,0,0}, Vecteur<3>{0,0,0}, 1.0, i, "P"});
    }
    auto end_vec = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff_vec = end_vec - start_vec;
    std::cout << "Temps (std::vector avec reserve) : " << diff_vec.count() << " s\n";

    std::cout << "Test de performances TP3 Q8\n";
    
    Vecteur<3> dimensions{1.0, 1.0, 1.0}; 
    double r_coupe = 0.1; 

    for (int k = 3; k <= 7; ++k) {
        // Calcul du nombre de particules : (2^k)^3
        int base = std::pow(2, k);
        int nb_particules = base * base * base; 
        
        std::cout << "Génération de " << nb_particules << " particules (k=" << k << ")... " << std::flush;
        
        Univers<3> u(nb_particules, dimensions, r_coupe);
        
        // Mesure du temps pour le calcul des forces
        auto start = std::chrono::steady_clock::now();
        u.algoStormerVerlet(0.0001, 0.0001, 1.0, 1.0, 0.0, 0.0, 0);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        
        std::cout << "Temps de calcul : " << diff.count() << " s\n";
    }

    return 0;
}
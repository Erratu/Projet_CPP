#include <iostream>
#include <list>
#include <vector>

#include "univers.hpp"

Univers<2> create_sys(Vecteur<2> dimensions);

int main() {
    const unsigned int windowWidth = 200;
    const unsigned int windowHeight = 200;
    Vecteur<2> dimensions{static_cast<double>(windowWidth), static_cast<double>(windowHeight)};
    
    Univers<2> u1 = create_sys(dimensions);

    std::cout << "Début de la simulation du système solaire...\n";

    double t_end = 468.5;
    double dt = 0.015;
    int freq_vtk = 50;

    try {
        u1.algoStormerVerlet(t_end, dt, 1.0, 1.0, 0.0, 0.0, freq_vtk, "output_sys_sol");
        std::cout << "Simulation terminée avec succès dans le dossier 'output_sys_sol/' !\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
    }

    return 0;
}

Univers<2> create_sys(Vecteur<2> dimensions) {
    std::list<Particule<2>> particleList;

    // Soleil
    particleList.emplace_back(Particule<2>{Vecteur<2>{30.0, 30.0}, Vecteur<2>{0.0, 0.0}, 1.0, 0, "Soleil"});
    // Terre
    particleList.emplace_back(Particule<2>{Vecteur<2>{30.0, 31.0}, Vecteur<2>{-1.0, 0.0}, 3.0e-6, 1, "Terre"});
    // Jupiter
    particleList.emplace_back(Particule<2>{Vecteur<2>{30.0, 35.36}, Vecteur<2>{-0.425, 0.0}, 9.55e-4, 2, "Jupiter"});
    // Halley
    particleList.emplace_back(Particule<2>{Vecteur<2>{64.75, 30.0}, Vecteur<2>{0.0, 0.0296}, 1e-14, 3, "Halley"});

    return Univers<2>{particleList, dimensions, 100.0}; // r_cut grand pour couvrir le sys solaire
}
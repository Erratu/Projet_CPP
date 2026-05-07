#include <iostream>
#include <list>
#include <vector>

#include "univers.hpp"

int main() {
    const unsigned int windowWidth = 400;
    const unsigned int windowHeight = 300;
    Vecteur<2> dimensions{static_cast<double>(windowWidth), static_cast<double>(windowHeight)};
    
    // Univers avec 100 particules générées aléatoirement
    Univers<2> u1(100, dimensions, 400.0 / 10.0);

    std::cout << "Début de la simulation d'un univers aléatoire...\n";

    double t_end = 50.0; 
    double dt = 0.015;
    int freq_vtk = 20;

    try {
        u1.algoStormerVerlet(t_end, dt, 1.0, 1.0, 0.0, 0.0, freq_vtk, "output_univers");
        std::cout << "Simulation terminée avec succès dans le dossier 'output_univers/' !\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
    }

    return 0;
}
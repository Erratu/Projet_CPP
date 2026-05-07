#include <iostream>
#include <vector>
#include <cmath>

#include "univers.hpp"

Univers<2> create_collision_scene(Vecteur<2> dimensions);

int main() {
    const unsigned int windowWidth = 200; 
    const unsigned int windowHeight = 150;
    Vecteur<2> dimensions{static_cast<double>(windowWidth), static_cast<double>(windowHeight)};
    
    Univers<2> u1 = create_collision_scene(dimensions);

    std::cout << "Début de la simulation de collision...\n";

    double t_end = 19.5;
    double dt = 0.00005;
    double epsilon = 5.0;
    double sigma = 1.0;
    
    int freq_vtk = 100;

    try {
        u1.algoStormerVerlet(t_end, dt, epsilon, sigma, 0.0, 0.0, freq_vtk, "output_collision");
        std::cout << "Simulation terminée avec succès dans le dossier 'output_collision/' !\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
    }

    return 0;
}

Univers<2> create_collision_scene(Vecteur<2> dimensions) {
    std::list<Particule<2>> particles;
    double dist_equilibre = std::pow(2.0, 1.0/6.0); // ~1.122
    int id = 0;

    int cols_bleu = 160;
    int cols_rouge = 40;

    double largeur_bleu = cols_bleu * dist_equilibre;
    double margin_x = (dimensions[0] - largeur_bleu) / 2.0;
    if (margin_x < 0) margin_x = 0; 

    double centre_x = margin_x + (largeur_bleu / 2.0);
    double offset_x_rouge = centre_x - ((cols_rouge * dist_equilibre) / 2.0);
    double offset_y_rouge = 10.0; 

    // Carré rouge
    for (int i = 0; i < cols_rouge; ++i) {
        for (int j = 0; j < 40; ++j) {
            Vecteur<2> pos = {offset_x_rouge + i * dist_equilibre, offset_y_rouge + j * dist_equilibre};
            Vecteur<2> vel = {0.0, 10.0};
            particles.emplace_back(Particule<2>{pos, vel, 1.0, id++, "R"});
        }
    }

    // Rectangle bleu
    double offset_y = 60.0;
    for (int i = 0; i < cols_bleu; ++i) {
        for (int j = 0; j < 40; ++j) {
            Vecteur<2> pos = {margin_x + i * dist_equilibre, offset_y + j * dist_equilibre};
            Vecteur<2> vel = {0.0, 0.0};
            particles.emplace_back(Particule<2>{pos, vel, 1.0, id++, "B"});
        }
    }

    return Univers<2>{particles, dimensions, 2.5};
}
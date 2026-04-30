#pragma once

#include <list>
#include <vector>
#include <array>
#include "particule.hpp"

/**
 * @brief Classe représentant un univers de particules
 * @tparam D Dimension de l’univers (2D, 3D…)
 */
template<int D>
class Univers {
private:
    std::list<Particule<D>> particules;

    double rayon_coupe;
    Vecteur<D> longueurs;
    std::array<int, D> n_cells;
    std::array<int, D> mult_dim;

    struct Cellule {
        std::list<Particule<D>*> particules;     
        std::vector<int> voisines;  
        std::array<int, D> coords;       
    };

    std::vector<Cellule> cellules;

    /**
     * @brief Fonction utilitaire pour générer les particules aléatoirement
     * @param nb_particules Nombre de particules à générer
     * @param l Longueurs de l’univers dans chaque dimension
     * @return Liste de particules générées
     */
    static std::list<Particule<D>> genererParticules(int nb_particules, Vecteur<D> l);

public:
    // Iterators
    auto begin() { return particules.begin(); }
    auto end() { return particules.end(); }
    auto begin() const { return particules.begin(); }
    auto end() const { return particules.end(); }

    // Getters
    size_t nbParticules() const { return particules.size(); }
    int getNCells(int axe) const { return n_cells[axe]; }
    double getRayonCoupe() const { return rayon_coupe; }

    // Constructors
    Univers(int nb_particules, Vecteur<D> l = Vecteur<D>(), double r_coupe = 40.0);
    Univers(std::list<Particule<D>> ps, Vecteur<D> l = Vecteur<D>(), double r_coupe = 40.0);
    Univers(const Univers& autre);

    // Simulation methods
    void calculerForces(double epsilon = 1.0, double sigma = 1.0);
    void algoStormerVerlet(double t_end = 468.5, double dt = 0.015, double epsilon = 1.0, double sigma = 1.0);   
    
    // Grid utility methods
    int getIndexCell(std::array<int, D> coords) const;
    std::array<int, D> getCoordsCell(int index) const;
    void majCells();
    void setupVoisins(int cell_index);
};

#include "../src/univers.tpp"
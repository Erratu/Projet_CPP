#include <list>
#include <random>
#include <array>
#include "particule.hpp"

// essayer vector, plus rapide
// mettre en private et surcharge pour getter/setter ?

template<int D>
class Univers {
public:
    std::list<Particule<D>> particules;

    double rayon_coupe;
    Vecteur<D> longueurs;
    std::array<int, D> n_cells;

    struct Cellule {
        std::list<Particule<D>*> particules;      
        std::list<Cellule*> voisines;          
    };

    std::list<Cellule> cellules;

    void calculerForces();              
    void algoStormerVerlet(double t_end = 468.5, double dt = 0.015);   
    
    Univers(int nb_particules, Vecteur<D> l = Vecteur<D>()) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i=0; i<nb_particules; ++i) {
            Vecteur<D> pos;
            Vecteur<D> vel;
            for (int j = 0; j < D; ++j) {
                pos[j] = dist(mt);
                vel[j] = 0.0;
            }

            particules.emplace_back(Particule{
                pos,
                vel,
                dist(mt), i, "Ab"});
        }

        rayon_coupe = 2.5;
        for (int i = 0; i < D; ++i) {
            longueurs[i] = l[i];
        }
        for (int i = 0; i < D; ++i) {
            n_cells[i] = static_cast<int>(longueurs[i] / rayon_coupe);
        }

        // Assigner les particules aux cellules
        // et construire la liste des cellules voisines
    }

    Univers(std::list<Particule<D>> ps, Vecteur<D> l = Vecteur<D>()) {
        particules = ps;

        rayon_coupe = 2.5;
        for (int i = 0; i < D; ++i) {
            longueurs[i] = l[i];
            n_cells[i] = static_cast<int>(longueurs[i] / rayon_coupe);
        }
    }

    Univers(const Univers& autre) {
        for(const auto& p : autre.particules) {
            particules.emplace_back(p);
        }

        rayon_coupe = autre.rayon_coupe;
        for (int i = 0; i < D; ++i) {
            longueurs[i] = autre.longueurs[i];
            n_cells[i] = autre.n_cells[i];
        }
    }
};
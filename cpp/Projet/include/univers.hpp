#include <list>
#include <random>
#include "particule.hpp"
// essayer vector, plus rapide
// mettre en private et surcharge pour getter/setter
class Univers {
public:
    std::list<Particule> particules;
    int dim; // Dimension de l'espace

    void calculerForces();              
    void algoStormerVerlet(double t_end = 468.5, double dt = 0.015);   
    
    Univers(int nb_particules, int dimension = 3) : dim(dimension) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i=0; i<nb_particules; ++i) {
            particules.emplace_back(Particule{
                dist(mt), dist(mt), dist(mt), 
                dist(mt), dist(mt), dist(mt), 
                dist(mt), i, "Ab"});
        }
    }

    Univers(std::list<Particule> ps) {
        particules = ps;
    }
};
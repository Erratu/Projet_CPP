#include <list>
#include <random>
#include "particule.hpp"
// essayer vector, plus rapide
class Univers {
public:
    std::list<Particule> particules;

    void calculerForces();              
    void algoStormerVerlet(double t_end = 468.5, double dt = 0.015);   
    
    Univers(int nb_particules) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i=0; i<nb_particules; ++i) {
            particules.emplace_back(Particule(
                dist(mt), dist(mt), dist(mt), 
                dist(mt), dist(mt), dist(mt), 
                dist(mt), i, "Ab"));
        }
    }

    Univers(list<Particule> ps) {
        particules = ps
    }
};
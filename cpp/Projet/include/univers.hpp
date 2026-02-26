#include <list>
#include <random>
#include "particule.hpp"

class Univers {
public:
    std::list<Particule> particules;

    void calculerForces();              
    void algoStormerVerlet();   
    
    Univers(int nb_particules) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        for (int i=0; i<nb_particules; ++i) {
            particules.emplace_back(dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), i, "Ab", dist(mt), dist(mt), dist(mt));
        }
    }
};
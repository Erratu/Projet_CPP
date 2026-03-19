#include "vecteur.hpp"

template<int D>
class Particule {
public:

    Vecteur<D> pos;
    Vecteur<D> v;
    Vecteur<D> f;
    double masse; // Masse
    int id; // Identifiant unique
    const char* type; // Catégorie de la particule

    void afficher();
    
    Particule(double x, double y, double z, double vx, 
            double vy, double vz, double masse, 
            int id, const char* type, 
            double forceX=0, double forceY=0, double forceZ=0) : 
        pos(x, y, z), v(vx, vy, vz), f(forceX, forceY, forceZ),
        masse(masse), id(id), type(type) {}

    Particule(Vecteur<D> position, Vecteur<D> vitesse, double masse, 
            int id, const char* type, Vecteur<D> force = Vecteur<D>()) : 
        pos(position), v(vitesse), f(force),
        masse(masse), id(id), type(type) {}
};
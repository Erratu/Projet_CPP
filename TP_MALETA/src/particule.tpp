#include <iostream>

template<int D>
Particule<D>::Particule(Vecteur<D> position, Vecteur<D> vitesse, double masse, 
                        int id, const char* type, Vecteur<D> force) : 
    pos(position), v(vitesse), f(force),
    masse(masse), id(id), type(type) {}

template<int D>
void Particule<D>::afficher() {
    std::cout << "Particule " << id << ": " << pos << "\n";
}

template<int D>
std::ostream& operator<<(std::ostream& os, const Particule<D>& p) {
    os << p.getPos();
    return os;
}

template<int D>
void Particule<D>::updatePosition(double dt) {
    for (int i = 0; i < D; ++i) {
        f_old[i] = f[i];
        pos[i] += dt * (v[i] + 0.5 / masse * f[i] * dt); 
    }
}

template<int D>
void Particule<D>::updateV(double dt) {
    for (int i = 0; i < D; ++i) {
        v[i] += dt * 0.5 / masse * (f[i] + f_old[i]);
    }
}

template<int D>
void Particule<D>::resetForce() {
    f = Vecteur<D>();
}

template<int D>
Vecteur<D> Particule<D>::dist(const Particule<D>& autre) const {
    return autre.pos - pos;
}

template<int D>
void Particule<D>::addForce(const Vecteur<D>& force) {
    f += force;
}
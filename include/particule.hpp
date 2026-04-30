#include "vecteur.hpp"

/**
 * @brief Classe représentant une particule
 *
 * Cette classe contient les propriétés d'une particule et permet
 * de gérer sa position et sa vitesse.
 * @tparam D Dimension de l’univers dans lequel se trouve la particule (2D, 3D…)
 */
template<int D>
class Particule {
private:

    Vecteur<D> pos;
    Vecteur<D> v;
    Vecteur<D> f;
    Vecteur<D> f_old; 
    double masse; // Masse
    int id; // Identifiant unique
    const char* type; // Catégorie de la particule

public:

    /**
     * @brief Constructeur avec vecteurs
     * @param position Vecteur de position
     * @param vitesse Vecteur de vitesse
     * @param masse Masse de la particule
     * @param id Identifiant unique
     * @param type Type de la particule
     * @param force Vecteur de force (par défaut nul)
     */
    Particule(Vecteur<D> position, Vecteur<D> vitesse, double masse, 
            int id, const char* type, Vecteur<D> force = Vecteur<D>());

    /**
     * @brief Affiche les informations de la particule
     * 
     * Affiche l'identifiant et la position de la particule sur la sortie standard.
     */
    void afficher();

    const Vecteur<D>& getPos() const { return pos; }
    void updatePosition(double dt);
    void updateV(double dt);
    void resetForce();
    Vecteur<D> dist(const Particule<D>& autre) const;
    void addForce(const Vecteur<D>& force);
    char getType() const { return type[0]; }
};

template<int D>
std::ostream& operator<<(std::ostream& os, const Particule<D>& p);

#include "../src/particule.tpp"
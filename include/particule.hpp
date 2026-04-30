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
    double masse; // Masse
    int id; // Identifiant unique
    const char* type; // Catégorie de la particule

public:
    
    /**
     * @brief Constructeur avec paramètres individuels
     * @param x Composante x de la position
     * @param y Composante y de la position
     * @param z Composante z de la position
     * @param vx Composante x de la vitesse
     * @param vy Composante y de la vitesse
     * @param vz Composante z de la vitesse
     * @param masse Masse de la particule
     * @param id Identifiant unique
     * @param type Type de la particule
     * @param forceX Composante x de la force (par défaut 0)
     * @param forceY Composante y de la force (par défaut 0)
     * @param forceZ Composante z de la force (par défaut 0)
     */
    Particule(double x, double y, double z, double vx, 
            double vy, double vz, double masse, 
            int id, const char* type, 
            double forceX=0, double forceY=0, double forceZ=0) : 
        pos(x, y, z), v(vx, vy, vz), f(forceX, forceY, forceZ),
        masse(masse), id(id), type(type) {}

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
            int id, const char* type, Vecteur<D> force = Vecteur<D>()) : 
        pos(position), v(vitesse), f(force),
        masse(masse), id(id), type(type) {}

    /**
     * @brief Affiche les informations de la particule
     * 
     * Affiche l'identifiant et la position de la particule sur la sortie standard.
     */
    void afficher();

    /** @brief Retourne l'index de la cellule dans laquelle se trouve la particule
     * @return Index de la cellule
     */
    int getCell(double rayon_coupe, 
                        const std::array<int, D>& n_cells, 
                        const std::array<int, D>& mult_dim) const;
};
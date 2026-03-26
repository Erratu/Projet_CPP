#include <list>
#include <random>
#include <array>
#include "particule.hpp"

// essayer vector, plus rapide
// mettre en private et surcharge pour getter/setter ?

/**
 * @brief Classe représentant un univers de particules
 *
 * Cette classe contient une liste de particules et permet
 * de gérer leurs positions et vitesses.
 * @tparam D Dimension de l’univers (2D, 3D…)
 */
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

    /**
     * @brief Calcule les forces d'interaction entre toutes les paires de particules
     * 
     * Utilise une approche naïve O(n²) pour calculer les forces d'interaction
     * gravitationnelles entre chaque paire de particules.
     */
    void calculerForces();

    /**
     * @brief Simule l'évolution du système en utilisant l'algorithme de Stormer-Verlet
     * @param t_end Temps final de simulation (par défaut 468.5)
     * @param dt Pas de temps (par défaut 0.015)
     * 
     * Enregistre les positions de toutes les particules dans un fichier "positions_astres.txt".
     */
    void algoStormerVerlet(double t_end = 468.5, double dt = 0.015);   
    
    /**
     * @brief Constructeur générateur avec particules aléatoires
     * @param nb_particules Nombre de particules à générer
     * @param l Vecteur des dimensions de l'univers (par défaut vecteur nul)
     * 
     * Génère des particules avec positions et vitesses aléatoires.
     */
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

    /**
     * @brief Constructeur à partir d'une liste de particules
     * @param ps Liste des particules
     * @param l Vecteur des dimensions de l'univers (par défaut vecteur nul)
     */
    Univers(std::list<Particule<D>> ps, Vecteur<D> l = Vecteur<D>()) {
        particules = ps;

        rayon_coupe = 2.5;
        for (int i = 0; i < D; ++i) {
            longueurs[i] = l[i];
            n_cells[i] = static_cast<int>(longueurs[i] / rayon_coupe);
        }
    }

    /**
     * @brief Constructeur de copie
     * @param autre Univers à copier
     */
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
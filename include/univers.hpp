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
     * @brief Fonction utilitaire pour générer la liste aléatoire 
     * avant d'appeler le constructeur principal.
     */
    static std::list<Particule<D>> genererParticules(int nb_particules, Vecteur<D> l) {
        std::list<Particule<D>> ps;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i=0; i<nb_particules; ++i) {
            Vecteur<D> pos, vel;
            for (int j = 0; j < D; ++j) {
                pos[j] = dist(mt) * l[j];
                vel[j] = 0.0;
            }
            ps.emplace_back(Particule<D>{pos, vel, dist(mt), i, "Ab"});
        }
        return ps;
    }

public:

    auto begin() { return particules.begin(); }
    auto end() { return particules.end(); }

    // Version constante pour la sécurité
    auto begin() const { return particules.begin(); }
    auto end() const { return particules.end(); }

    size_t nbParticules() const { 
        return particules.size(); 
    }

    int getNCells(int axe) const { 
        return n_cells[axe]; 
    }

    // Getter pour le rayon de coupe (taille d'une cellule)
    double getRayonCoupe() const { 
        return rayon_coupe; 
    }

    /**
     * @brief Calcule les forces d'interaction entre toutes les paires de particules
     * 
     * Utilise une approche naïve O(n²) pour calculer les forces d'interaction
     * gravitationnelles entre chaque paire de particules.
     */
    void calculerForces(double epsilon = 1.0, double sigma = 1.0);

    /**
     * @brief Simule l'évolution du système en utilisant l'algorithme de Stormer-Verlet
     * @param t_end Temps final de simulation (par défaut 468.5)
     * @param dt Pas de temps (par défaut 0.015)
     * 
     * Enregistre les positions de toutes les particules dans un fichier "positions_astres.txt".
     */
    void algoStormerVerlet(double t_end = 468.5, double dt = 0.015, double epsilon = 1.0, double sigma = 1.0);   
    
    /**
     * @brief Transforme des coordonnées de grille en index linéaire 1D
     * @param coords Tableau contenant l'index de la cellule sur chaque axe [i, j, k...]
     */
    int getIndexCell(std::array<int, D> coords) const {
        int index = 0;
        for (int i = 0; i < D; ++i) {
            index += coords[i] * mult_dim[i];
        }
        return index;
    }

    /**
     * @brief Transforme un index linéaire 1D en coordonnées de grille
     */
    std::array<int, D> getCoordsCell(int index) const {
        std::array<int, D> coords;
        for (int i = D - 1; i >= 0; --i) {
            coords[i] = index / mult_dim[i];
            index %= mult_dim[i];
        }
        return coords;
    }
    
    /** 
     * @brief Met à jour les cellules en fonction des positions actuelles des particules
     */
    void majCells();

    /**
     * @brief Configure les voisins d'une cellule donnée
     * @param cell_index Index de la cellule pour laquelle configurer les voisins
     * 
     * Génère les indices des cellules voisines en utilisant des offsets de -1, 0, +1
     * et vérifie que les voisins ne sortent pas de la grille.
     */
    void setupVoisins(int cell_index);
    // TODO : rendre générique ?

    /**
     * @brief Constructeur générateur avec particules aléatoires
     * @param nb_particules Nombre de particules à générer
     * @param l Vecteur des dimensions de l'univers (par défaut vecteur nul)
     * @param r_coupe Rayon de coupe (par défaut 40.0)
     * 
     * Génère des particules avec positions et vitesses aléatoires.
     */
    Univers(int nb_particules, Vecteur<D> l = Vecteur<D>(), double r_coupe = 40.0) : 
    Univers(genererParticules(nb_particules, l), l, r_coupe) {}

    /**
     * @brief Constructeur à partir d'une liste de particules
     * @param ps Liste des particules
     * @param l Vecteur des dimensions de l'univers (par défaut vecteur nul)
     * @param r_coupe Rayon de coupe (par défaut 40.0)
     */
    Univers(std::list<Particule<D>> ps, Vecteur<D> l = Vecteur<D>(), double r_coupe = 40.0) {
        particules = ps;

        for (int i = 0; i < D; ++i) {
            longueurs[i] = l[i];
        }

        rayon_coupe = r_coupe;

        int tot_n_cells = 1;
        for (int i = 0; i < D; ++i) {
            n_cells[i] = static_cast<int>(longueurs[i] / rayon_coupe);
            if (n_cells[i] < 1) n_cells[i] = 1;
            tot_n_cells *= n_cells[i];
        }
        cellules.resize(tot_n_cells);

        mult_dim[0] = 1;
        for (int i = 0; i < D - 1; ++i) {
            mult_dim[i+1] = mult_dim[i] * n_cells[i];
        }

        for (int i = 0; i < tot_n_cells; ++i) {
            cellules[i].coords = getCoordsCell(i); 
            setupVoisins(i); 
        }

        majCells();
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

    // ajouter l'opérateur d'assignation et le destructeur si nécessaire, 
    // sinon enlever le constructeur de copie #TODO
};
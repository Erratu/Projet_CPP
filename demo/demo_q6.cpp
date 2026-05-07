#include <iostream>
#include <list>
#include <cmath>
#include "univers.hpp"
#include "exceptions.hpp"


int main() {
    Vecteur<2> dimensions{250.0, 180.0}; 
    std::list<Particule<2>> particules;
    
    double dist_eq = 1.122; // Distance d'équilibre pour sigma = 1
    int id = 0;

    // Bloc bleu (N2 = 17227, y en bas)
    int count_bleu = 0;
    for (int y = 1; y < 100 && count_bleu < 17227; ++y) {
        for (int x = 1; x < 222 && count_bleu < 17227; ++x) {
            Vecteur<2> pos{x * dist_eq, y * dist_eq};
            Vecteur<2> vel{0.0, 0.0};
            particules.emplace_back(Particule<2>{pos, vel, 1.0, id++, "B"});
            count_bleu++;
        }
    }

    Vecteur<2> centre_boule{125.0, 150.0}; 
    double rayon_boule = 20.0;
    int count_rouge = 0;

    for (double y = centre_boule[1] - rayon_boule; y <= centre_boule[1] + rayon_boule; y += dist_eq) {
        for (double x = centre_boule[0] - rayon_boule; x <= centre_boule[0] + rayon_boule; x += dist_eq) {
            Vecteur<2> pos{x, y};
            // Condition : ne créer la particule que si elle est dans le cercle
            Vecteur<2> diff = pos - centre_boule;
            if (std::sqrt(diff[0]*diff[0] + diff[1]*diff[1]) <= rayon_boule && count_rouge < 395) {
                Vecteur<2> vel{0.0, -10.0};
                particules.emplace_back(Particule<2>{pos, vel, 1.0, id++, "R"});
                count_rouge++;
            }
        }
    }

    Univers<2> u(particules, dimensions, 2.5);
    u.setConditionLimite(ConditionLimite::REFLEXION_POTENTIEL); // Rebond physique aux parois
    
    // Lancement de la Simulation
    double dt = 0.0005; 
    double t_end = 29.5;
    double G = -12.0; 
    double Ec_cible = 0.005 * (395 + 17227);
    int freq_vtk = 1000; // Exportation VTK toutes les 100 itérations
    const std::string dossier = "output_q6";

    try {
        std::cout << "Début de la simulation. Exportation VTK prévue...\n";
        u.algoStormerVerlet(t_end, dt, 1.0, 1.0, G, Ec_cible, freq_vtk, dossier);
        std::cout << "Simulation terminée avec succès !\n";

    } catch (const SimulationException& e) {
        std::cerr << "\n[ARRET DE LA SIMULATION] " << e.what() << "\n";
        std::cerr << "Veuillez réduire le pas de temps (dt) ou revoir les conditions initiales.\n";
        return 1; 
        
    } catch (const std::exception& e) {
        std::cerr << "\n[ERREUR SYSTEME] " << e.what() << "\n";
        return 2;
    }

    return 0;
}
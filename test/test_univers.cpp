#include <gtest/gtest.h>
#include "univers.hpp"
#include <list>

// Test de la création de l'univers avec génération aléatoire
TEST(UniversTest, CreationEtComptage) {
    const int nb_particules = 15;
    Univers<3> u(nb_particules);
    
    EXPECT_EQ(u.nbParticules(), nb_particules);
    EXPECT_DOUBLE_EQ(u.getRayonCoupe(), 40.0);
}

// Test de la logique de maillage
TEST(UniversTest, GestionGrilleSpatiale) {
    std::list<Particule<2>> particules;
    particules.emplace_back(Particule<2>({10.0, 10.0}, {0.0, 0.0}, 1.0, 1, "Test"));
    
    // Univers 2D avec des dimensions de 100x100 et un rayon de coupe de 10.0
    Univers<2> u(particules, {100.0, 100.0}, 10.0);
    
    std::array<int, 2> coords_cibles = {2, 3};
    int index = u.getIndexCell(coords_cibles);
    
    std::array<int, 2> coords_calculees = u.getCoordsCell(index);
    
    EXPECT_EQ(coords_cibles[0], coords_calculees[0]) << "Erreur d'indexation sur l'axe X";
    EXPECT_EQ(coords_cibles[1], coords_calculees[1]) << "Erreur d'indexation sur l'axe Y";
}

// Test d'intégration global de l'algorithme
TEST(UniversTest, ExecutionSimulation) {
    std::list<Particule<2>> systeme;
    systeme.emplace_back(Particule<2>{Vecteur<2>{0.0, 0.0}, Vecteur<2>{0.0, 0.0}, 1.0, 0, "Soleil"});
    systeme.emplace_back(Particule<2>{Vecteur<2>{0.0, 1.0}, Vecteur<2>{-1.0, 0.0}, 3.0e-6, 1, "Terre"});

    Univers<2> u(systeme, {50.0, 50.0});

    EXPECT_NO_THROW({
        u.algoStormerVerlet(0.05, 0.015);
    });

    Univers<2> u2(2, {10, 10});
    
    EXPECT_NO_THROW({
        u2.algoStormerVerlet(0.1, 0.01);
    });
}
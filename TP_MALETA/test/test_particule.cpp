#include <gtest/gtest.h>
#include "particule.hpp"

// Test de l'initialisation et des getters basiques
TEST(ParticuleTest, InitialisationEtProprietes) {
    Vecteur<2> pos{10.0, 20.0};
    Vecteur<2> vit{1.0, -1.0};
    Particule<2> p(pos, vit, 5.0, 42, "Terre");

    EXPECT_EQ(p.getType(), 'T');
    EXPECT_DOUBLE_EQ(p.getPos()[0], 10.0);
    EXPECT_DOUBLE_EQ(p.getPos()[1], 20.0);
    EXPECT_EQ(p.getId(), 42);
    EXPECT_DOUBLE_EQ(p.getMasse(), 5.0);

    Particule<2> p2({1,1}, {2,2}, 5.5, 1, "Proton");
    EXPECT_EQ(p2.getId(), 1);
    EXPECT_DOUBLE_EQ(p2.getPos()[0], 1.0);
    EXPECT_DOUBLE_EQ(p2.getPos()[1], 1.0);
    EXPECT_DOUBLE_EQ(p2.getVitesse()[0], 2.0);
    EXPECT_DOUBLE_EQ(p2.getVitesse()[1], 2.0);
}

// Test du calcul de distance entre deux particules
TEST(ParticuleTest, CalculDistance) {
    Particule<2> p1({0.0, 0.0}, {0.0, 0.0}, 1.0, 1, "P1");
    Particule<2> p2({3.0, 4.0}, {0.0, 0.0}, 1.0, 2, "P2");
    
    Vecteur<2> distance_vec = p1.dist(p2); 
    
    EXPECT_DOUBLE_EQ(distance_vec[0], 3.0);
    EXPECT_DOUBLE_EQ(distance_vec[1], 4.0);
}

// Test de l'accumulation des forces
TEST(ParticuleTest, GestionDesForces) {
    Vecteur<3> p{0,0,0}, v{0,0,0};
    Particule<3> part(p, v, 1.0, 42, "Test");
    
    // Vérification de la force initiale (via getForce)
    EXPECT_EQ(part.getForce(), (Vecteur<3>{0,0,0}));
    
    // Test de l'accumulation
    part.addForce(Vecteur<3>{5.0, 0.0, 0.0});
    EXPECT_EQ(part.getForce(), (Vecteur<3>{5.0, 0.0, 0.0}));
    
    // Test du reset
    part.resetForce();
    EXPECT_EQ(part.getForce(), (Vecteur<3>{0,0,0}));
}
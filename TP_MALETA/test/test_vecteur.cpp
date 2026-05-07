#include <gtest/gtest.h>
#include "vecteur.hpp"

// Test des différents constructeurs et de l'accès aux coordonnées
TEST(VecteurTest, ConstructeursEtAcces) {
    Vecteur<3> v_defaut;
    EXPECT_DOUBLE_EQ(v_defaut[0], 0.0);
    EXPECT_DOUBLE_EQ(v_defaut[1], 0.0);
    EXPECT_DOUBLE_EQ(v_defaut[2], 0.0);
    
    Vecteur<2> v_init{4.2, -3.1};
    EXPECT_DOUBLE_EQ(v_init[0], 4.2);
    EXPECT_DOUBLE_EQ(v_init[1], -3.1);
}

// Test des opérateurs
TEST(VecteurTest, OperationsArithmetiques) {
    Vecteur<3> v1{1.0, 2.0, 3.0};
    Vecteur<3> v2{4.0, 5.0, 6.0};
    
    // Test de l'addition
    EXPECT_EQ(v1 + v2, (Vecteur<3>{5.0, 7.0, 9.0}));

    // Test de la soustraction
    EXPECT_EQ(v1 - v2, (Vecteur<3>{-3.0, -3.0, -3.0}));
    
    // Test de la multiplication scalaire
    EXPECT_EQ(v1 * 2.0, (Vecteur<3>{2.0, 4.0, 6.0}));

    // Test de la négation
    EXPECT_EQ(-v1, (Vecteur<3>{-1.0, -2.0, -3.0}));
}

TEST(VecteurTest, Comparaison) {
    Vecteur<2> v1{1.2, 3.4};
    Vecteur<2> v2{1.2, 3.4};
    Vecteur<2> v3{0.0, 0.0};
    
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}
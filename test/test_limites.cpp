#include <gtest/gtest.h>
#include "univers.hpp"

// Test de la condition de RÉFLEXION
TEST(ConditionLimiteTest, Reflexion) {
    std::list<Particule<2>> liste;
    // Particule sortie à gauche (x = -1.0) avec vitesse vers la gauche (vx = -2.0)
    liste.emplace_back(Particule<2>{Vecteur<2>{-1.0, 5.0}, Vecteur<2>{-2.0, 0.0}, 1.0, 1, "P"});
    
    Univers<2> u(liste, Vecteur<2>{10.0, 10.0});
    u.setConditionLimite(ConditionLimite::REFLEXION);
    
    auto& p = *u.begin();
    // La méthode renvoie false (pas de destruction)
    bool detruire = u.appliquerConditionsLimites(p);

    EXPECT_FALSE(detruire);
    // Position symétrique : -(-1.0) = 1.0
    EXPECT_DOUBLE_EQ(p.getPos()[0], 1.0);
    // Vitesse inversée : -(-2.0) = 2.0
    EXPECT_DOUBLE_EQ(p.getVitesse()[0], 2.0);
}

// Test de la condition d'ABSORPTION
TEST(ConditionLimiteTest, Absorption) {
    std::list<Particule<2>> liste;
    // Particule sortie par la droite (x = 11.0 > 10.0)
    liste.emplace_back(Particule<2>{Vecteur<2>{11.0, 5.0}, Vecteur<2>{2.0, 0.0}, 1.0, 1, "P"});
    
    Univers<2> u(liste, Vecteur<2>{10.0, 10.0});
    u.setConditionLimite(ConditionLimite::ABSORPTION);
    
    auto& p = *u.begin();
    // La méthode doit renvoyer true car la particule est hors limites
    bool detruire = u.appliquerConditionsLimites(p);

    EXPECT_TRUE(detruire);
}

// Test de la condition PÉRIODIQUE
TEST(ConditionLimiteTest, Periodique) {
    std::list<Particule<2>> liste;
    // Particule sortie par la droite (x = 11.0 pour un domaine de 10.0)
    liste.emplace_back(Particule<2>{Vecteur<2>{11.0, 5.0}, Vecteur<2>{2.0, 3.0}, 1.0, 1, "P"});
    
    Univers<2> u(liste, Vecteur<2>{10.0, 10.0});
    u.setConditionLimite(ConditionLimite::PERIODIQUE);
    
    auto& p = *u.begin();
    bool detruire = u.appliquerConditionsLimites(p);

    EXPECT_FALSE(detruire);
    // Transportée à l'opposé : 11.0 % 10.0 = 1.0
    EXPECT_DOUBLE_EQ(p.getPos()[0], 1.0);
    // Vitesse inchangée
    EXPECT_DOUBLE_EQ(p.getVitesse()[0], 2.0);
}

// Test de la condition de RÉFLEXION PAR POTENTIEL
TEST(ConditionLimiteTest, ReflexionPotentiel) {
    // Vérification de la force répulsive
    std::list<Particule<2>> liste1;
    // On place la particule à x = 0.5 (proche du mur gauche) dès la création
    liste1.emplace_back(Particule<2>{Vecteur<2>{0.5, 5.0}, Vecteur<2>{-1.0, 0.0}, 1.0, 1, "P"});
    
    Univers<2> u1(liste1, Vecteur<2>{10.0, 10.0});
    u1.setConditionLimite(ConditionLimite::REFLEXION_POTENTIEL);
    
    u1.calculerForces(1.0, 1.0); 
    
    auto& p1 = *u1.begin();
    // La force doit être positive (pousse vers la droite)
    EXPECT_GT(p1.getForce()[0], 0.0);

    // Vérification de la sécurité (absorption si mur franchi)
    std::list<Particule<2>> liste2;
    // On place la particule directement à x = -0.1 (hors limite)
    liste2.emplace_back(Particule<2>{Vecteur<2>{-0.1, 5.0}, Vecteur<2>{-1.0, 0.0}, 1.0, 2, "P"});
    
    Univers<2> u2(liste2, Vecteur<2>{10.0, 10.0});
    u2.setConditionLimite(ConditionLimite::REFLEXION_POTENTIEL);
    
    auto& p2 = *u2.begin();
    // appliquerConditionsLimites renvoie true pour une particule hors domaine
    bool detruire = u2.appliquerConditionsLimites(p2);
    
    EXPECT_TRUE(detruire);
}
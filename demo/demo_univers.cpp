#include <random>
#include <chrono>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <vector>

#include "univers.hpp"

/**
 * @brief Visualisation d'un univers de particules
 * 
 * Crée une fenêtre graphique SFML et affiche un système de 100 particules en 2D avec sf::VertexArray.
 * 
 * @return 0 si l'exécution s'est déroulée correctement
 */
int main() {
    sf::RenderTexture rt;
    rt.create(64, 64);
    rt.clear(sf::Color::Transparent);
    sf::CircleShape circle(32);
    circle.setFillColor(sf::Color::White);
    rt.draw(circle);
    rt.display();
    sf::Texture circleTexture = rt.getTexture();
    circleTexture.setSmooth(true);

    const unsigned int windowWidth = 400;
    const unsigned int windowHeight = 300;
    Vecteur<2> dimensions;
    dimensions[0] = static_cast<double>(windowWidth);
    dimensions[1] = static_cast<double>(windowHeight);
    const float particleSize = 2.0f;

    Univers<2> u1(100, dimensions, 400 / 10.0);

    for (auto& p : u1) {
        p.v[0] = (rand() % 100 - 50) / 10.0; // Vitesse en X aléatoire
        p.v[1] = (rand() % 100 - 50) / 10.0; // Vitesse en Y aléatoire
    }

    // Calcul du nombre de lignes nécessaires
    int numLinesX = u1.getNCells(0) + 1; //
    int numLinesY = u1.getNCells(1) + 1; //
    sf::VertexArray grid(sf::Lines, (numLinesX + numLinesY) * 2);

    int lineIdx = 0;

    // Lignes verticales
    for (int i = 0; i < numLinesX; ++i) {
        float x = i * u1.getRayonCoupe(); //
        grid[lineIdx++].position = sf::Vector2f(x, 0);
        grid[lineIdx - 1].color = sf::Color(50, 50, 50); // Gris foncé
        grid[lineIdx++].position = sf::Vector2f(x, windowHeight);
        grid[lineIdx - 1].color = sf::Color(50, 50, 50);
    }

    // Lignes horizontales
    for (int j = 0; j < numLinesY; ++j) {
        float y = j * u1.getRayonCoupe(); //
        grid[lineIdx++].position = sf::Vector2f(0, y);
        grid[lineIdx - 1].color = sf::Color(50, 50, 50);
        grid[lineIdx++].position = sf::Vector2f(windowWidth, y);
        grid[lineIdx - 1].color = sf::Color(50, 50, 50);
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Simulation de Particules Optimisee");
    window.setFramerateLimit(60);
    sf::VertexArray particles(sf::Quads, u1.nbParticules() * 4);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // u1.evoluer()

        u1.algoStormerVerlet(0.015, 0.015);

        int i = 0;
        float halfSize = particleSize / 2.0f;

        for (auto& p : u1) {
            float x = static_cast<float>(p.pos[0]);
            float y = static_cast<float>(p.pos[1]);

            // Définit les 4 coins du carré représentant la particule
            particles[i + 0].position = sf::Vector2f(x - halfSize, y - halfSize);
            particles[i + 1].position = sf::Vector2f(x + halfSize, y - halfSize);
            particles[i + 2].position = sf::Vector2f(x + halfSize, y + halfSize);
            particles[i + 3].position = sf::Vector2f(x - halfSize, y + halfSize);

            particles[i + 0].texCoords = sf::Vector2f(0, 0);
            particles[i + 1].texCoords = sf::Vector2f(64, 0);
            particles[i + 2].texCoords = sf::Vector2f(64, 64);
            particles[i + 3].texCoords = sf::Vector2f(0, 64);

            for(int j=0; j<4; ++j) particles[i + j].color = sf::Color::White;
            i += 4;
        }

        window.clear(sf::Color::Black);
        window.draw(grid);
        window.draw(particles, &circleTexture);
        window.display();
    }

    return 0;
}
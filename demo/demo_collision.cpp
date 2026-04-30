#include <SFML/Graphics.hpp>
#include <vector>

#include "univers.hpp"

Univers<2> create_collision_scene(Vecteur<2> dimensions);

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

    const unsigned int windowWidth = 250;
    const unsigned int windowHeight = 150;
    Vecteur<2> dimensions;
    dimensions[0] = static_cast<double>(windowWidth);
    dimensions[1] = static_cast<double>(windowHeight);
    const float particleSize = 2.0f;

    Univers<2> u1 = create_collision_scene(dimensions);

    // Calcul du nombre de lignes nécessaires
    int numLinesX = u1.getNCells(0) + 1;
    int numLinesY = u1.getNCells(1) + 1;
    sf::VertexArray grid(sf::Lines, (numLinesX + numLinesY) * 2);

    int lineIdx = 0;

    // Lignes verticales
    for (int i = 0; i < numLinesX; ++i) {
        float x = i * u1.getRayonCoupe();
        grid[lineIdx++].position = sf::Vector2f(x, 0);
        grid[lineIdx - 1].color = sf::Color(50, 50, 50); // Gris foncé
        grid[lineIdx++].position = sf::Vector2f(x, windowHeight);
        grid[lineIdx - 1].color = sf::Color(50, 50, 50);
    }

    // Lignes horizontales
    for (int j = 0; j < numLinesY; ++j) {
        float y = j * u1.getRayonCoupe(); 
        grid[lineIdx++].position = sf::Vector2f(0, y);
        grid[lineIdx - 1].color = sf::Color(50, 50, 50);
        grid[lineIdx++].position = sf::Vector2f(windowWidth, y);
        grid[lineIdx - 1].color = sf::Color(50, 50, 50);
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Simulation de Particules Optimisee");
    window.setFramerateLimit(60);
    sf::VertexArray particles(sf::Quads, u1.nbParticules() * 4);
    double temps_total = 0.0;
    double temps_par_frame = 0.01;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (temps_total < 19.5) {
            u1.algoStormerVerlet(temps_par_frame, 0.00005, 5.0, 1.0);
            temps_total += temps_par_frame;
            std::cout << "Temps simulé : " << temps_total << " / 19.5\n"; 
        }

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

            sf::Color color = (p.id < 6400) ? sf::Color::Blue : sf::Color::Red; // N2=6400 [cite: 75]
    
            for(int j=0; j<4; ++j) {
                particles[i + j].color = color;
            }
            i += 4;
        }

        window.clear(sf::Color::Black);
        window.draw(grid);
        window.draw(particles, &circleTexture);
        window.display();
    }

    return 0;
}
Univers<2> create_collision_scene(Vecteur<2> dimensions) {
    std::list<Particule<2>> particles;
    double dist_equilibre = std::pow(2.0, 1.0/6.0);
    int id = 0;

    double offset_y = 20.0;
    // Le rectangle bleu
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 10; ++j) {
            Vecteur<2> pos = {i * dist_equilibre, offset_y + j * dist_equilibre};
            Vecteur<2> vel = {0.0, 0.0}; // Immobile au départ
            particles.emplace_back(Particule<2>{pos, vel, 1.0, id++, "Bleu"});
        }
    }

    // Le carré rouge
    double offset_x = (40 * dist_equilibre) / 2.0 - (10 * dist_equilibre) / 2.0;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            Vecteur<2> pos = {offset_x + i * dist_equilibre, j * dist_equilibre};
            Vecteur<2> vel = {0.0, 10.0}; // Vitesse initiale vers le bas
            particles.emplace_back(Particule<2>{pos, vel, 1.0, id++, "Rouge"});
        }
    }

    return Univers<2>{particles, dimensions, 2.5};
}
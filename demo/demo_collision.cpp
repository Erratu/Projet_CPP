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

    // Ajustement de la taille de la fenêtre pour mieux encadrer la scène
    const unsigned int windowWidth = 200; 
    const unsigned int windowHeight = 150;
    Vecteur<2> dimensions;
    dimensions[0] = static_cast<double>(windowWidth);
    dimensions[1] = static_cast<double>(windowHeight);
    
    // Si la distance d'équilibre de LJ (sigma) est de 1.0, la particule visuelle
    // doit mesurer environ 1.0 de diamètre pour que le contact visuel 
    // corresponde au contact physique.
    const float particleSize = 1.0f; 

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

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Simulation de Particules - Collision");
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
            Vecteur<2> pos = p.getPos();
            float x = static_cast<float>(pos[0]);
            float y = static_cast<float>(pos[1]);

            // Définit les 4 coins du carré représentant la particule
            particles[i + 0].position = sf::Vector2f(x - halfSize, y - halfSize);
            particles[i + 1].position = sf::Vector2f(x + halfSize, y - halfSize);
            particles[i + 2].position = sf::Vector2f(x + halfSize, y + halfSize);
            particles[i + 3].position = sf::Vector2f(x - halfSize, y + halfSize);

            particles[i + 0].texCoords = sf::Vector2f(0, 0);
            particles[i + 1].texCoords = sf::Vector2f(64, 0);
            particles[i + 2].texCoords = sf::Vector2f(64, 64);
            particles[i + 3].texCoords = sf::Vector2f(0, 64);

            sf::Color color = (p.getType() == 'R') ? sf::Color::Red : sf::Color::Blue;

            for(int j=0; j<4; ++j) {
                particles[i + j].color = color;
            }
            i += 4;
        }

        window.clear(sf::Color::Black);
        // window.draw(grid);
        window.draw(particles, &circleTexture);
        window.display();
    }

    return 0;
}

Univers<2> create_collision_scene(Vecteur<2> dimensions) {
    std::list<Particule<2>> particles;
    double dist_equilibre = std::pow(2.0, 1.0/6.0); // ~1.122
    int id = 0;

    int cols_bleu = 160;
    int cols_rouge = 40;

    // Largeur totale occupée par le bloc bleu
    double largeur_bleu = cols_bleu * dist_equilibre;

    // Pour centrer la scène dans la fenêtre, on calcule une petite marge à gauche
    double margin_x = (dimensions[0] - largeur_bleu) / 2.0;
    if (margin_x < 0) margin_x = 0; // Sécurité si la fenêtre est trop petite

    // Le centre X exact du bloc bleu, en tenant compte de la marge
    double centre_x = margin_x + (largeur_bleu / 2.0);

    // L'offset rouge doit commencer à la moitié de la largeur du bloc rouge avant le centre
    double offset_x_rouge = centre_x - ((cols_rouge * dist_equilibre) / 2.0);
    double offset_y_rouge = 10.0; 

    // Le carré rouge (1600 particules)
    for (int i = 0; i < cols_rouge; ++i) {
        for (int j = 0; j < 40; ++j) {
            Vecteur<2> pos = {offset_x_rouge + i * dist_equilibre, offset_y_rouge + j * dist_equilibre};
            Vecteur<2> vel = {0.0, 10.0};
            particles.emplace_back(Particule<2>{pos, vel, 1.0, id++, "R"});
        }
    }

    double offset_y = 60.0;
    // Le rectangle bleu (6400 particules)
    for (int i = 0; i < cols_bleu; ++i) {
        for (int j = 0; j < 40; ++j) {
            Vecteur<2> pos = {margin_x + i * dist_equilibre, offset_y + j * dist_equilibre};
            Vecteur<2> vel = {0.0, 0.0};
            particles.emplace_back(Particule<2>{pos, vel, 1.0, id++, "B"});
        }
    }

    return Univers<2>{particles, dimensions, 2.5};
}
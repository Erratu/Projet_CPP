#include <random>
#include <chrono>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <vector>

#include "univers.hpp"

int main() {
    Univers<2> u1(10);

    sf::RenderWindow window(sf::VideoMode(400, 300), "Particles");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for (auto& p : u1.particules) {
            Vecteur<2>& pos = p.pos;
            sf::CircleShape shape(5);
            shape.setOrigin(5, 5);
            shape.setPosition(pos[0]*400, pos[1]*300);
            shape.setFillColor(sf::Color::White);
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}

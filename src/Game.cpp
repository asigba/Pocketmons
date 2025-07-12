#include "Game.hpp"
#include "Battle.hpp"
#include <SFML/Graphics.hpp>

Game::Game() {

    Player player("Alex");
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(800,600), "Pocketmons");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Green);
        window.display();
    }
}

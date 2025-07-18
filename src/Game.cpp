#include "Game.hpp"
#include "Battle.hpp"
#include "Overworld.hpp"
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode(640, 448), "Pocketmons"), running(true) {
    window.setFramerateLimit(60);
    
    // Create the main player
    mainPlayer = new Player("Alex");
    
    // Give player some Pokemon
    Pokemon pikachu("Pikachu", 5, "Electric");    
    Move thunderbolt("ThunderBolt", "Electric", 10, 70);
    pikachu.addMove(thunderbolt);
    mainPlayer->addPokemon(pikachu);
    
    Pokemon charmander("Charmander", 4, "Fire");
    Move scratch("Scratch", "Normal", 25, 40);
    charmander.addMove(scratch);
    mainPlayer->addPokemon(charmander);
    
    // Create the overworld
    overworld = new Overworld(mainPlayer);
}

Game::~Game() {
    delete mainPlayer;
    delete overworld;
}

void Game::run() {
    while (running && window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            running = false;
            window.close();
        }
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Escape) {
                running = false;
                window.close();
            }
        }
        
        // Let overworld handle movement input
        overworld->handleInput(event);
    }
}

void Game::update() {
    overworld->update();
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    // Render the overworld
    overworld->render(window);
    
    window.display();
}

#include "Game.hpp"
#include "Battle.hpp"
#include <SFML/Graphics.hpp>

Game::Game() {

    Player player("Alex");
    Player enemy("Josh");

    // Creating pokemon
    Pokemon pikachu("Pikachu", 5, "Electric");    
    Pokemon charmander("Charmander", 4, "Fire");
    Pokemon bulbasaur("Bulbasaur", 5, "Grass");    
    Pokemon pidgey("Pidgey", 2, "Flying");  
    Pokemon pichu("Pichu", 3, "Electric");    
    Pokemon squirtle("Squirtle", 4, "Water");     

    // Adding pokemon to each trainer
    player.addPokemon(pikachu);
    player.addPokemon(charmander);
    player.addPokemon(squirtle);
    enemy.addPokemon(pichu);
    enemy.addPokemon(bulbasaur);
    enemy.addPokemon(pidgey);

    //Test Battle
    Battle battle(&player, &enemy);
    battle.startBattle();
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

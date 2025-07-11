#include "Game.hpp"
#include "Battle.hpp"
#include <SFML/Graphics.hpp>

Game::Game() {

    Player player("Alex");
    Player enemy("Josh");

    // Creating pokemon 
    // Pickachu
    Pokemon pikachu("Pikachu", 5, "Electric");    
    Move thunderbolt("ThunderBolt", "Electric", 10, 70);
    Move scratch("Scratch", "Normal", 25, 40);
    Move stomp("Stomp", "Dark", 20, 45);
    Move earthquake("Earthquake", "Ground", 5, 90);
    pikachu.addMove(thunderbolt);

    Pokemon charmander("Charmander", 4, "Fire");
    charmander.addMove(scratch);
    Pokemon bulbasaur("Bulbasaur", 5, "Grass");  
    bulbasaur.addMove(stomp);  
    Pokemon pidgey("Pidgey", 2, "Flying");  
    pidgey.addMove(scratch);
    Pokemon pichu("Pichu", 3, "Electric");    
    pichu.addMove(thunderbolt);
    Pokemon squirtle("Squirtle", 4, "Water"); 
    squirtle.addMove(earthquake);
        

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

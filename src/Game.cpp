#include "Game.hpp"
#include "Overworld.hpp"
#include "Battle.hpp"
#include "Pokemon.hpp"
#include "Move.hpp"
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode(640, 448), "Pocketmons"), running(true){
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
    currentState = OVERWORLD;
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
   
    if(currentState == OVERWORLD) {
        if(overworld->justEncountered) {
            wildPokemon = new Pokemon("Pidgey", 3, "Flying");
            wildPokemon->addMove(Move("Tackle","Normal",35,40));

            // Start a battle
            currentBattle = new Battle(mainPlayer, wildPokemon);
            currentState = BATTLE;
            overworld->justEncountered = false;
        }
    } else if(currentState == BATTLE) {
        if (currentBattle) {
            currentBattle->startBattle();
            delete currentBattle;
            currentBattle = nullptr;
            delete wildPokemon;
            wildPokemon = nullptr;
            currentState = OVERWORLD;
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    // Render the overworld
    if(currentState == OVERWORLD) {
        overworld->render(window);
    } else if (currentState == BATTLE && currentBattle && wildPokemon) {
        sf::Font font;
        font.loadFromFile("assets/arial.ttf");

        //Draw player pokemon info
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setCharacterSize(24);
        playerText.setFillColor(sf::Color::White);
        playerText.setPosition(50,300);
        playerText.setString(
            mainPlayer->getActivePokemon()->getName() + " HP: " +
            std::to_string(mainPlayer->getActivePokemon()->getHP())
        );
        window.draw(playerText);

        // draw wild pokemon info
        sf::Text wildText;
        wildText.setFont(font);
        wildText.setCharacterSize(24);
        wildText.setFillColor(sf::Color::White);
        wildText.setPosition(400,50);
        wildText.setString(
            wildPokemon->getName() + " HP: " +
            std::to_string(wildPokemon->getHP())
        );
        window.draw(wildText);

        // Draw a simple box for moves
        sf::RectangleShape moveBox(sf::Vector2f(700,100));
        moveBox.setFillColor(sf::Color(50,50,50));
        moveBox.setPosition(50,500);
        window.draw(moveBox);

        const auto& moves = mainPlayer->getActivePokemon()->getMoves();
        // Draw move names
        for(size_t i = 0; i < moves.size(); ++i){
            sf::Text moveText;
            moveText.setFont(font);
            moveText.setCharacterSize(20);
            moveText.setFillColor(sf::Color::Yellow);
            moveText.setPosition(70 + i * 180, 520);
            moveText.setString(
                std::to_string(i + 1) + ". " + moves[i].getName()
            );
            
            window.draw(moveText);
        }
    }
    window.display();
}

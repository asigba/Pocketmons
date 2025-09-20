#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Overworld.hpp"
#include "Battle.hpp"

using namespace std;

class Game {
    private:
        sf::RenderWindow window;
        bool running;
        Player* mainPlayer;
        Overworld* overworld;
        enum GameState {OVERWORLD, BATTLE};
        GameState currentState;
        Battle* currentBattle;
        Pokemon* wildPokemon = nullptr;

    public:
        Game();       
        ~Game();
        void run();
        void handleEvents();
        void update();
        void render();
};
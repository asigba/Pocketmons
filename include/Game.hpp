#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Overworld.hpp"

using namespace std;

class Game {
    private:
        sf::RenderWindow window;
        bool running;
        Player* mainPlayer;
        Overworld* overworld;

    public:
        Game();       
        ~Game();
        void run();
        void handleEvents();
        void update();
        void render();
};
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "SpriteSheet.hpp"

using namespace std;

class Overworld {
    private:
        Player* player;
        int playerX, playerY;
        vector<vector<char>> worldMap;
        int mapWidth, mapHeight;
        SpriteSheet* sheet;
        sf::View camera;
        
    public:
        bool justEncountered = false;
        Overworld(Player* mainPlayer);
        ~Overworld();
        void handleInput(sf::Event& event);
        void update();
        void render(sf::RenderWindow& window);
        bool checkEncounter();
        void movePlayer(int deltaX, int deltaY);
        bool canMoveTo(int x, int y);
        void initializeMap();
};
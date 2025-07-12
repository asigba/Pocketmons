#include <iostream>
#include <vector>
#include "Player.hpp"

class Overworld {
    private:
        Player* player
        int playerX, playerY;
        vector<vector<char>> worldMap;
        int mapWidth, mapHeight;
    public:
        Overworld(Player* mainPlayer);
        void handleInput(sf::Event& event);
        void update();
        void render(sf::RenderWindow& window);
        bool checkEncounter();
        void movePlayer(int deltaX, int deltaY);
};
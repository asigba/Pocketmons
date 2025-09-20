#include "Overworld.hpp"
#include <SFML/Graphics.hpp>

using namespace std;


Overworld::Overworld(Player* mainPlayer): player(mainPlayer), playerX(2), playerY(2){
    initializeMap();
}

void Overworld::handleInput(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        switch(event.key.code){
            case(sf::Keyboard::Up):
                movePlayer(0, -1);
                break;
            case(sf::Keyboard::Down):
                movePlayer(0,1);
                break;
            case(sf::Keyboard::Left):
                movePlayer(-1,0);
                break;
            case(sf::Keyboard::Right):
                movePlayer(1,0);
                break;
            default:
                break;
        }

    }
}

void Overworld::update() {

}

void Overworld::render(sf::RenderWindow& window){
    int tileSize = 64;  // Size of each tile in pixels
    
    // Draw the map
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(x * tileSize, y * tileSize);
            
            // Set color based on tile type
            switch (worldMap[y][x]) {
                case '#':  // Wall
                    tile.setFillColor(sf::Color::Black);
                    break;
                case '.':  // Grass
                    tile.setFillColor(sf::Color::Green);
                    break;
                case 'P':  // Pokemon Center
                    tile.setFillColor(sf::Color::Red);
                    break;
                case '~':  // Water
                    tile.setFillColor(sf::Color::Blue);
                    break;
                default:
                    tile.setFillColor(sf::Color::White);
            }
            
            window.draw(tile);
        }
    }
    
    // Draw the player
    sf::CircleShape playerSprite(tileSize / 3);
    playerSprite.setFillColor(sf::Color::Yellow);
    playerSprite.setPosition(playerX * tileSize + tileSize/4, playerY * tileSize + tileSize/4);
    window.draw(playerSprite);
}

bool Overworld::checkEncounter(){
    int randomChance = rand() % 100;

    if (randomChance < 10) {
        cout << "Wild POkemon encountered!!" << "\n";
        return true;
    }

    return false;
}

void Overworld::movePlayer(int deltaX, int deltaY) {
    int newX = playerX + deltaX;
    int newY = playerY + deltaY;

    if(canMoveTo(newX, newY)) {
        playerX = newX;
        playerY = newY;

        if (worldMap[newY][newX] == '.') {
            justEncountered = checkEncounter();
        } else {
            justEncountered = false;
        }
    }
}

void Overworld::initializeMap() {
    worldMap = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#','#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.','#'},
        {'#', '.', 'P', '.', '.', '.', '.', '.', '.','#'},
        {'#', '.', '.', '.', '~', '~', '.', '.', '.','#'},
        {'#', '.', '.', '.', '~', '~', '.', '.', '.','#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.','#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };
    mapHeight = worldMap.size();
    mapWidth = worldMap[0].size();
}

bool Overworld::canMoveTo(int x, int y) {
    if( x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
        return false;
    }

    char tile = worldMap[y][x];
    return (tile == '.' || tile == 'P');
}
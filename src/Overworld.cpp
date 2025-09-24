#include "Overworld.hpp"
#include <fstream>
#include <SFML/Graphics.hpp>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

Overworld::Overworld(Player* mainPlayer): player(mainPlayer), playerX(2), playerY(2){
    sheet = new SpriteSheet("assets/Tilesets/Grass.png", 16, 16); // Grass sprite sheet
    trees = new SpriteSheet("assets/Objects/Basic_Grass_Biom_things.png",32,32); // Tree sprite sheet
    initializeMap();
    camera.setSize(200, 100);
    camera.setCenter(playerX * 16 + 32, playerY * 16 + 32);
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

Overworld::~Overworld() {
    delete sheet;
    delete trees;
}

void Overworld::loadJsonMap(const std::string filename){
    worldMap.clear();
    std::ifstream file(filename);
    json mapData;
    file >> mapData;

    int width = mapData["width"];
    int height = mapData["height"];
    auto& layer = mapData["layers"];
    auto& data = layer[0]["data"]; 

    for (int y = 0; y < height; ++y) {
        std::vector<char> row;
        for (int x = 0; x < width; ++x) {
            int tileId = data[y * width + x];
            row.push_back(mapTileIdToChar(tileId));
        }
        worldMap.push_back(row);
    }

    mapHeight = height;
    mapWidth = width;
}

char Overworld::mapTileIdToChar(int tileId) {
    if (tileId == 0) return ' '; //empty
    if (tileId == 2) return '/'; // grass top edge
    if (tileId == 1) return '<'; // grass top left corner
    if (tileId == 12) return '['; // gass left edge
    if (tileId == 13) return '.'; // grass
    if (tileId == 14) return ']'; // grass right edge
    if (tileId == 24) return '?'; // grass bottom edge
    if (tileId >=78 && tileId < 155) return ','; // tilled dirt
    if (tileId >= 155 && tileId < 159) return '~'; //water
    if (tileId >= 159 && tileId < 194) return 'P'; // House
    if (tileId >= 94) return '#'; // wall
    return ' ';
}

void Overworld::render(sf::RenderWindow& window){
    int tileSize = 16;  // Size of each tile in pixels    

    window.setView(camera);
    
    // Draw the map
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(x * tileSize, y * tileSize);
            
            // Set color based on tile type
            switch (worldMap[y][x]) {
                case '#':  // Tree Wall
                    {
                        sf::Sprite tree = trees->getTile(1,0);
                        tree.setPosition(x * tileSize, y * tileSize);
                        window.draw(tree);                   
                        break;
                    }                    
                case '[':  // Grass
                {
                    sf::Sprite grass = sheet->getTile(0,1);
                    grass.setPosition(x * tileSize, y * tileSize);
                    window.draw(grass);                   
                    break;
                }
                case ']':  // Grass
                {
                    sf::Sprite grass = sheet->getTile(2,1);
                    grass.setPosition(x * tileSize, y * tileSize);
                    window.draw(grass);                   
                    break;
                }
                case '?':  // Grass
                {
                    sf::Sprite grass = sheet->getTile(1,2);
                    grass.setPosition(x * tileSize, y * tileSize);
                    window.draw(grass);                   
                    break;
                }
                case '.':  // Grass
                {
                    sf::Sprite grass = sheet->getTile(1,1);
                    grass.setPosition(x * tileSize, y * tileSize);
                    window.draw(grass);                   
                    break;
                }
                case '<':  // Grass Top left Corner
                {
                    sf::Sprite grass = sheet->getTile(0,0);
                    grass.setPosition(x * tileSize, y * tileSize);
                    window.draw(grass);                   
                    break;
                }
                case '/': // Grass Top Edge
                {
                    sf::Sprite grass1 = sheet->getTile(1,0);
                    grass1.setPosition(x * tileSize, y * tileSize);
                    window.draw(grass1);
                    break;
                }                    
                case ',': // Dirt
                    tile.setFillColor(sf::Color::Cyan);
                    window.draw(tile);
                    break;                    
                case 'P':  // Pokemon Center
                    tile.setFillColor(sf::Color::Red);
                    window.draw(tile); 
                    break;
                case '~':  // Water
                    tile.setFillColor(sf::Color::Blue);
                    window.draw(tile); 
                    break;
                default:
                    tile.setFillColor(sf::Color::White);
                    window.draw(tile); 
            }
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
        camera.setCenter(320,224);
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

        camera.setCenter(playerX * 16 + 32, playerY * 16 + 32);
        
        // Put '.' back into this 
        if (worldMap[newY][newX] == 'X') {
            justEncountered = checkEncounter();
        } else if(worldMap[newY][newX] == 'D'){
            switchMap("assets/Maps/route1.txt", 1, 1);
        } else {
            justEncountered = false;
        }
    }
}

void Overworld::loadMap(const std::string& filename) {
    worldMap.clear();
    std::ifstream file(filename);
    std::string line;
    while(std::getline(file,line)) {
        std::vector<char> row(line.begin(), line.end());
        worldMap.push_back(row);
    }
    mapHeight = worldMap.size();
    mapWidth = worldMap.empty() ? 0 : worldMap[0].size();
}

void Overworld::initializeMap() {
    // loadMap("assets/Maps/town.txt");
    loadJsonMap("assets/Maps/town.tmj");
}

void Overworld::switchMap(const std::string& filename, int newPlayerX, int newPlayerY) {
    loadMap(filename);
    playerX = newPlayerX;
    playerY = newPlayerY;
    camera.setCenter(playerX * 16 + 32, playerY * 16 + 32);
}

bool Overworld::canMoveTo(int x, int y) {
    if( x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
        return false;
    }

    char tile = worldMap[y][x];
    return (tile != '#');
}
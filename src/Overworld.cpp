#include "Overworld.hpp"
#include <fstream>
#include <SFML/Graphics.hpp>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

Overworld::Overworld(Player* mainPlayer): player(mainPlayer), playerX(2), playerY(2){
    sheet = new SpriteSheet("assets/Tilesets/Grass.png", 16, 16); // Grass sprite sheet
    trees = new SpriteSheet("assets/Objects/Basic_Grass_Biom_things.png",32,32); // Tree sprite sheet
    dirt = new SpriteSheet("assets/Tilesets/Tilled_Dirt_v2.png", 16, 16); // Tilled Dirt sheet
    water = new SpriteSheet("assets/Tilesets/Water.png",16,16); // Water sheet
    bush = new SpriteSheet("assets/Objects/Simple_Milk_and_grass_item.png", 16,16);
    houseWalls = new SpriteSheet("assets/Tilesets/Wooden_House_Walls_Tilset.png",16,16);
    houseRoofs = new SpriteSheet("assets/Tilesets/Wooden_House_Roof_Tilset.png",16,16);
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
    delete dirt;
    delete bush;
    delete houseWalls;
    delete houseRoofs;
}

void Overworld::loadJsonMap(const std::string filename){
    worldMap.clear();
    std::ifstream file(filename);
    json mapData;
    file >> mapData;

    int width = mapData["width"];
    int height = mapData["height"];
    auto& layers = mapData["layers"];    
    int numLayers = layers.size();

    for (int l = 0; l < numLayers; ++l) {
        auto& data = layers[l]["data"];
        std::vector<std::vector<int>> layerMap;  
        for (int y = 0; y < height; ++y) {
            std::vector<int> row;
            for (int x = 0; x < width; ++x) {
                int tileId = data[y * width + x];
                row.push_back(tileId);
            }
            layerMap.push_back(row);
            worldMap.push_back(row);
        }
        layeredMap.push_back(layerMap);
    }

    mapHeight = height;
    mapWidth = width;
}

void Overworld::render(sf::RenderWindow& window){
    int tileSize = 16;  // Size of each tile in pixels    

    window.setView(camera);
    
    // Draw the map
    for (size_t l = 0; l < layeredMap.size(); l++) {
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition(x * tileSize, y * tileSize);
                
                // Set color based on tile type
                switch (layeredMap[l][y][x]) {
                    case 0: break;
                    case 190:  // Tree Wall
                        {
                            sf::Sprite tree = trees->getTile(1,0);
                            tree.setPosition(x * tileSize, y * tileSize);
                            window.draw(tree);                   
                            break;
                        }                    
                    case 12:  // Grass
                    {
                        sf::Sprite grass = sheet->getTile(0,1);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 14:  // Grass
                    {
                        sf::Sprite grass = sheet->getTile(2,1);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 24:  // Grass
                    {
                        sf::Sprite grass = sheet->getTile(1,2);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 13:  // Grass
                    {
                        sf::Sprite grass = sheet->getTile(1,1);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 17:  // Grass round corner
                    {
                        sf::Sprite grass = sheet->getTile(5,1);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 18:  // Grass round corner
                    {
                        sf::Sprite grass = sheet->getTile(6,1);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 28:  // Grass round corner
                    {
                        sf::Sprite grass = sheet->getTile(5,2);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 29:  // Grass round corner
                    {
                        sf::Sprite grass = sheet->getTile(6,2);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 1:  // Grass Top left Corner
                    {
                        sf::Sprite grass = sheet->getTile(0,0);
                        grass.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass);                   
                        break;
                    }
                    case 2: // Grass Top Edge
                    {
                        sf::Sprite grass1 = sheet->getTile(1,0);
                        grass1.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass1);
                        break;
                    }
                    case 3: // Corner grass Top Edge
                    {
                        sf::Sprite grass1 = sheet->getTile(2,0);
                        grass1.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass1);
                        break;
                    }
                    case 25: // Corner Grass Top Edge
                    {
                        sf::Sprite grass1 = sheet->getTile(2,2);
                        grass1.setPosition(x * tileSize, y * tileSize);
                        window.draw(grass1);
                        break;
                    }
                    case 90: // Dirt 
                    {
                        sf::Sprite dirt1 = dirt->getTile(1,1);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }                      
                    case 79: // Dirt top edge
                        {
                        sf::Sprite dirt1 = dirt->getTile(1,0);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }
                    case 78: 
                        {
                        sf::Sprite dirt1 = dirt->getTile(0,0);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }
                    case 100: // bottom corner dirt
                        {
                        sf::Sprite dirt1 = dirt->getTile(0,2);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }
                    case 101: // bottom edge dirt
                        {
                        sf::Sprite dirt1 = dirt->getTile(1,2);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }  
                    case 89: // bottom edge dirt
                        {
                        sf::Sprite dirt1 = dirt->getTile(0,1);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }
                    case 91: // right edge dirt
                        {
                        sf::Sprite dirt1 = dirt->getTile(2,1);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }  
                    case 80: // right corner dirt
                        {
                        sf::Sprite dirt1 = dirt->getTile(2,0);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }  
                    case 95: // dirt corner bend 
                        {
                        sf::Sprite dirt1 = dirt->getTile(6,1);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }
                    case 105: // dirt corner bend 
                        {
                        sf::Sprite dirt1 = dirt->getTile(5,2);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }
                    case 106: // dirt corner bend 
                        {
                        sf::Sprite dirt1 = dirt->getTile(6,2);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }
                    case 94: // dirt corner bend 
                        {
                        sf::Sprite dirt1 = dirt->getTile(5,1);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    } 
                    case 102: // dirt corner 
                        {
                        sf::Sprite dirt1 = dirt->getTile(2,2);
                        dirt1.setPosition(x * tileSize, y * tileSize);
                        window.draw(dirt1);
                        break;
                    }                                     
                    case 204:  // Building strucutres
                        {
                            sf::Sprite housewall = houseWalls->getTile(0,2);
                            housewall.setPosition(x * tileSize, y * tileSize);
                            window.draw(housewall);
                            break;
                        }
                    case 205:  // Building strucutres
                        {
                            sf::Sprite housewall = houseWalls->getTile(1,2);
                            housewall.setPosition(x * tileSize, y * tileSize);
                            window.draw(housewall);
                            break;
                        }
                    case 206:  // Building strucutres
                        {
                            sf::Sprite housewall = houseWalls->getTile(2,2);
                            housewall.setPosition(x * tileSize, y * tileSize);
                            window.draw(housewall);
                            break;
                        }
                    case 207:  // Building strucutres
                        {
                            sf::Sprite housewall = houseWalls->getTile(3,2);
                            housewall.setPosition(x * tileSize, y * tileSize);
                            window.draw(housewall);
                            break;
                        }
                    case 155:  // Water
                    {
                        sf::Sprite water1 = water->getTile(0,0);
                        water1.setPosition(x * tileSize, y * tileSize);
                        window.draw(water1);
                        break;
                    } 
                    case 212:  // Bushes for wild pokemon
                    {
                        sf::Sprite bush1 = bush->getTile(3,0);
                        bush1.setPosition(x * tileSize, y * tileSize);
                        window.draw(bush1);
                        break;
                    }   
                    default:
                        tile.setFillColor(sf::Color::White);
                        window.draw(tile); 
                }
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
        
        
        if (layeredMap[1][newY][newX] == 212) {
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
        std::vector<int> row(line.begin(), line.end());
        worldMap.push_back(row);
    }
    mapHeight = worldMap.size();
    mapWidth = worldMap.empty() ? 0 : worldMap[0].size();
}

void Overworld::initializeMap() {
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
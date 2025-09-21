#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(const std::string& filename, int tileWidth, int tileHeight) : tileWidth(tileWidth), tileHeight(tileHeight) {
    texture.loadFromFile(filename);
}

sf::Sprite SpriteSheet::getTile(int col, int row) const {
    sf::Sprite sprite(texture);

    sprite.setTextureRect(sf::IntRect(
        col * tileWidth,
        row * tileHeight,
        tileWidth,
        tileHeight
    ));

    return sprite;
}
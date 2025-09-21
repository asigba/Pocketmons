#pragma once
#include <SFML/Graphics.hpp>

class SpriteSheet {
    private:
        sf::Texture texture;
        int tileWidth, tileHeight;
    public:
        SpriteSheet(const std::string& filename, int tileWidth, int tileHeight);
        sf::Sprite getTile(int col, int row) const;
};
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Game {
    private:
        sf::RenderWindow window;
        int stateVariables;
        bool running;

    public:
        Game();       
        void run();
        void handleEvents();
        void update();
        void render();
};
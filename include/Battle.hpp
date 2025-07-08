#include <iostream>
using namespace std;

class Battle {
    private:
        Pokemon* playerPokemon;
        Pokemon* enemyPokemon;
        bool battleActive;
        int turn;
    public:
        Battle(Pokemon* player, Pokemon* enemy);
        void startBattle();
        void playerTurn();
        void enemyTurn();
        bool isBattleOver();
        void displayBattleStatus();
};
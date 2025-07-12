#include <iostream>
using namespace std;

class Battle {
    private:
        Player* player;
        Player* enemy;
        bool battleActive;
        int turn;

    public:
        Battle(Player* setPlayer, Player* setEnemy);
        void startBattle();
        void playerTurn();
        void enemyTurn();
        bool isBattleOver();
        void displayBattleStatus();
        void switchPokemon();
};
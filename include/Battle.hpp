#pragma once
#include <iostream>
#include "Player.hpp"
using namespace std;

class Battle {
    private:
        Player* player;
        Player* enemy;
        Pokemon* pokemon;
        bool battleActive;
        int turn;

    public:
        Battle(Player* setPlayer, Player* setEnemy);
        Battle(Player* setPlayer, Pokemon* setEnemyPokemon);
        void startBattle();
        void playerTurn();
        void enemyTurn();
        bool isBattleOver();
        void displayBattleStatus();
        void switchPokemon();
};
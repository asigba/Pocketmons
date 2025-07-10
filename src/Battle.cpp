#include "Battle.hpp"
using namespace std;

Battle::Battle(Pokemon* player, Pokemon* enemy) {
    playerPokemon = player;
    enemyPokemon = enemy;
    battleActive = true;
    if (playerPokemon->getSpeed() > enemyPokemon->getSpeed()) {
        turn = 0;
    } else {
        turn = 1;
    }
    
}

bool Battle::isBattleOver() {
    if (!playerPokemon->isAlive() || !enemyPokemon->isAlive()) {
        battleActive = false;
        return true;
    }
    return false;
}

void Battle::playerTurn() {
    cout << "Your Turn. Choose: " << "\n";
    cout << "1. Attack" << "\n";    
    cout << "Enter choice: " << "\n";

    int choice;
    cin >> choice;

    if (choice == 1) {
        int damage = playerPokemon->getAttack() - enemyPokemon->getDefense();
        enemyPokemon->takeDamage(damage);
        cout << playerPokemon->getName() << "  attacks for " << damage << " damage!" << "\n"; 
    }
    
}

void Battle::enemyTurn() {
    cout << "Enemy Turn" << "\n";

    int damage = enemyPokemon->getAttack() - playerPokemon->getDefense();
    playerPokemon->takeDamage(damage);
    cout << enemyPokemon->getName() << "  attacks for " << damage << " damage!" << "\n"; 
 
}

void Battle::displayBattleStatus() {
    cout << playerPokemon->getName() << "'s HP: "<< playerPokemon->getHP() << "\n";
    cout << enemyPokemon->getName() << "'s HP: "<< enemyPokemon->getHP() << "\n";
}

void Battle::startBattle() {
    while(battleActive) {
        displayBattleStatus();
        if(isBattleOver()) {
            break;
        }

        if (turn == 0) {
            playerTurn();
            turn = 1;
        } else {
            enemyTurn();
            turn = 0;
        }

    }

    if(playerPokemon->isAlive()) {
        cout << "You Win" << "\n";
    }
    cout << "Game Over" << "\n";
}
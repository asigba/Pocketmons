#include "Battle.hpp"
using namespace std;

Battle::Battle(Player* setPlayer, Player* setEnemy) {
    player = setPlayer;
    enemy = setEnemy;
    battleActive = true;

    if (player->getActivePokemon()->getSpeed() > enemy->getActivePokemon()->getSpeed()) {
        turn = 0;
    } else {
        turn = 1;
    }
    
}

bool Battle::isBattleOver() {
    if (!player->getActivePokemon()->isAlive() || !enemy->getActivePokemon()->isAlive()) {
        battleActive = false;
        return true;
    }
    return false;
}

void Battle::playerTurn() {
    cout << "Your Turn. Choose: " << "\n";
    cout << "1. Attack" << "\n";  
    cout << "2. Switch" << "\n";  
    cout << "Enter choice: " << "\n";

    int choice;
    cin >> choice;

    if (choice == 1) {
        int damage = player->getActivePokemon()->getAttack() - enemy->getActivePokemon()->getDefense();
        enemy->getActivePokemon()->takeDamage(damage);
        cout << player->getActivePokemon()->getName() << "  attacks for " << damage << " damage!" << "\n"; 
    } else if (choice == 2) {
        int index;
        cout << "Enter index of pokemon(1-6): " << "\n";
        cin >> index;
        player->switchPokemon(index - 1);      
    }
    
}

void Battle::enemyTurn() {
    cout << "Enemy Turn" << "\n";

    int damage = enemy->getActivePokemon()->getAttack() - player->getActivePokemon()->getDefense();
    player->getActivePokemon()->takeDamage(damage);
    cout << enemy->getActivePokemon()->getName() << "  attacks for " << damage << " damage!" << "\n"; 

    if(!enemy->getActivePokemon()->isAlive()) {
        cout << enemy->getActivePokemon()->getName() << " has fainted" << "\n";
        enemy->switchPokemon(enemy->getCurrPokemon() + 1);
    }
 
}

void Battle::displayBattleStatus() {
    cout << player->getActivePokemon()->getName() << "'s HP: "<< player->getActivePokemon()->getHP() << "\n";
    cout << enemy->getActivePokemon()->getName() << "'s HP: "<< enemy->getActivePokemon()->getHP() << "\n";
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

    if(player->getActivePokemon()->isAlive()) {
        cout << "You Win" << "\n";
    }
    cout << "Game Over" << "\n";
}
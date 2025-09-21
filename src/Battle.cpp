#include "Battle.hpp"
using namespace std;

Battle::Battle(Player* setPlayer, Player* setEnemy): player(setPlayer), enemy(setEnemy), battleActive(true) {
    if (player->getActivePokemon()->getSpeed() > enemy->getActivePokemon()->getSpeed()) {
        turn = 0;
    } else {
        turn = 1;
    }
}

Battle::Battle(Player* setPlayer, Pokemon* setEnemyPokemon): player(setPlayer), pokemon(setEnemyPokemon), battleActive(true) {
    if (player->getActivePokemon()->getSpeed() > pokemon->getSpeed()) {
        turn = 0;
    } else {
        turn = 1;
    }
}

bool Battle::isBattleOver() {
    if (!player->hasAlivePokemon()) {
        battleActive = false;
        return true;
    }
    if (enemy) {
        if(!enemy->hasAlivePokemon()){
            battleActive = false;
            return true;
        }
    } else if (pokemon) {
        if(!pokemon->isAlive()) {
            battleActive = false;
            return true;
        }
    }
    return false;
}

void Battle::switchPokemon() {
    int index;
    cout << "Your Team" << "\n";
    player->displayTeam();
    cout << "Enter index of pokemon(1-6): " << "\n";
    cin >> index;
    if ((index - 1) == player->getCurrPokemon()){
            playerTurn();
    }
    player->switchPokemon(index - 1);   
}

void Battle::playerTurn() {
    if(player->getActivePokemon()->isAlive()) {
        cout << "Your Turn. Choose: " << "\n";
        cout << "1. Attack" << "\n";  
        cout << "2. Switch Pokemon" << "\n"; 
        cout << "3. Use Item" << "\n"; 
        cout << "Enter choice: " << "\n";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout<< "Choose your move: " << "\n";
            player->getActivePokemon()->showMoves();
            int move;
            cin >> move;
            
            int damage = player->getActivePokemon()->getMove(move - 1)->getDamage();
            if(enemy) {
                damage -= enemy->getActivePokemon()->getDefense();
                enemy->getActivePokemon()->takeDamage(damage);
                cout << player->getActivePokemon()->getName() << "  attacks for " << damage << " damage!" << "\n"; 
            } else  if(pokemon) {
                damage -= pokemon->getDefense();
                pokemon->takeDamage(damage);
                cout << player->getActivePokemon()->getName() << "  attacks for " << damage << " damage!" << "\n"; 
            }
            
        } else if (choice == 2) {
            switchPokemon(); 
        }
    } else {
        cout << "Switch? " << "\n";
        switchPokemon(); 
    }
}

void Battle::enemyTurn() {
    cout << "Enemy Turn" << "\n";

    if(enemy) {
        int damage = enemy->getActivePokemon()->getMove(0)->getDamage() - player->getActivePokemon()->getDefense();
        player->getActivePokemon()->takeDamage(damage);
        cout << enemy->getActivePokemon()->getName() << "  attacks for " << damage << " damage!" << "\n"; 

        if(!enemy->getActivePokemon()->isAlive()) {
            cout << enemy->getActivePokemon()->getName() << " has fainted" << "\n";
            enemy->switchPokemon(enemy->getCurrPokemon() + 1);
        }
    } else if (pokemon) {
        int damage = pokemon->getMove(0)->getDamage() - player->getActivePokemon()->getDefense();
        player->getActivePokemon()->takeDamage(damage);
        cout << pokemon->getName() << "  attacks for " << damage << " damage!" << "\n"; 

        if(!pokemon->isAlive()) {
            cout << pokemon->getName() << " has fainted" << "\n";
        }
    }   
 
}

void Battle::displayBattleStatus() {
    cout << player->getActivePokemon()->getName() << "'s HP: "<< player->getActivePokemon()->getHP() << "\n";
    if (enemy) {
        cout << enemy->getActivePokemon()->getName() << "'s HP: "<< enemy->getActivePokemon()->getHP() << "\n";
    } else if(pokemon) {
        cout << pokemon->getName() << "'s HP: "<< pokemon->getHP() << "\n";
    }
    
}

void Battle::startBattle() {
    while(battleActive) {
        cout << "Battle Loop running, turn: " << turn << endl;
        displayBattleStatus();
        if(isBattleOver()) {
            cout << "Battle over detected in loop." <<endl;
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

    if(player->hasAlivePokemon()) {
        cout << "Player active Pokemon HP: " << player->getActivePokemon()->getHP() << endl;
        cout << "Wild Pokemon HP: " << pokemon->getHP() << endl;

        cout << "You Win" << "\n";
    }
    cout << "Game Over" << "\n";
}
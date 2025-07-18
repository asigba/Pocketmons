#include <iostream>
#include "Player.hpp"

using namespace std;

Player::Player(string playerName) : name(playerName), activePokemon(0), money(100) {}

void Player::addPokemon(Pokemon newPokemon){
    if(team.size() < 6) {
        team.push_back(newPokemon);
        cout << newPokemon.getName() << " captured" << "\n";
    } else {
        cout << "Team is full!" << "\n";
    }
    
}
void Player::switchPokemon(int index){
    if(index >= 0 && index < (int)team.size()) {
        activePokemon = index;
    }
}
void Player::displayTeam() {
    int count = 0;
    while(count < (int)team.size()) {
        cout << count + 1 << "."<< team[count].getName() << ", HP: " << team[count].getHP() << ", Level: " << team[count].getLevel() << "\n";
        count++;
    }   
}

int Player::getCurrPokemon() {
    return activePokemon;
}

int Player::getTeamSize() {
    return team.size();
}

bool Player::hasAlivePokemon(){
    int count = 0;
    while(count < getTeamSize()) {
        if(team[count].isAlive()) {
            return true;
        }
        count++;
    }
    return false;
}

string Player::getName() {
    return name;
}
Pokemon* Player::getActivePokemon() {
    if(!team.empty() && activePokemon < (int)team.size()) {
        return &team[activePokemon];
    }
    return nullptr;
}
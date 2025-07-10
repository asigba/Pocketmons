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
    activePokemon = index;
}
void Player::displayTeam() {
    int count = 0;
    while(count < team.size()) {
        cout << team[count].getName() << ", HP: " << team[count].getHP() << ", Level: " << team[count].getLevel() << "\n";
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
    if(!team.empty()) {
        return &team[activePokemon];
    }
    return nullptr;
}
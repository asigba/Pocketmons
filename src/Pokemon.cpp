#include "Pokemon.hpp"
#include <iostream>

using namespace std;

Pokemon::Pokemon(string setName, int setLevel, string setType) {
    name = setName;
    level = setLevel;
    type = setType;

    HP = 50 + (level * 2);
    attack = 20 + (level * 2);
    defense = 15 + (level * 2);
    speed = 10 + (level * 3);
}

string Pokemon::getName() {
    return name;
}

int Pokemon::getLevel() {
    return level;
}

int Pokemon::getHP() {
    return HP;
}

int Pokemon::getAttack(){
    return attack;
}
int Pokemon::getDefense(){
    return defense;
}
int Pokemon::getSpeed() {
    return speed;
}
void Pokemon::takeDamage(int damage){
    HP = HP - damage;
}
bool Pokemon::isAlive() {
    if(HP > 0) {
        return true;
    } else {
        return false;
    }
}
void Pokemon::displayInfo() {
    
}
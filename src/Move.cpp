#include "Move.hpp"
#include <iostream>

Move::Move(string setName, string setType, int setUsageLimit, int setDamage): name(setName),type(setType), usageLimit(setUsageLimit), damage(setDamage){
}

string Move::getName() {
    return name;
}
string Move::getType(){
    return type;
}

int Move::getUsageLimit(){
    return usageLimit;
}

int Move::getDamage(){
    return damage;
}
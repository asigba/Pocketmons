#include "Move.hpp";

Move::Move(string setType, int setUsageLimt, int setDamage): type(setType), usageLimit(setUsageLimit), damage(setDamage){
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
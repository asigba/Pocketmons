#include <iostream>
using namespace std;
#include "Move.hpp"

class Pokemon {
    private:
        string name;
        int level;
        int HP;
        int attack;
        int defense;
        int speed;
        string type;
        vector<Move> moves;
    
    public:
        Pokemon(string setName, int setLevel, string setType);
        void showMoves();
        void addMove(Move move);
        int getLevel();
        int getHP();
        int getMaxHp();
        int getAttack();
        int getDefense();
        int getSpeed();
        string getName();
        void takeDamage(int damage);
        bool isAlive();
        void displayInfo();
};
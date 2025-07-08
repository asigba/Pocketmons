#include <iostream>
using namespace std;

class Pokemon {
    private:
        string name;
        int level;
        int HP;
        int attack;
        int defense;
        int speed;
        string type;
    
    public:
        Pokemon(string setName, int setLevel, string setType);
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
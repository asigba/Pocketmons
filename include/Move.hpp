#include <iostream>
using namespace std;

class Move {
    private:
        string name;
        string type;
        int usageLimit;        
        int damage;
    
    public:
        Move(string setName, string setType, int setUsageLimit, int setDamage);
        string getName();
        string getType();
        int getUsageLimit();
        int getDamage();
};
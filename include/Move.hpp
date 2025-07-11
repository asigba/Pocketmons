#include <iostream>
using namespace std;

class Move {
    private:
        string type;
        int usageLimit;        
        int damage;
    
    public:
        Move(string type, int usageLimt, int damage);
        string getType();
        int getUsageLimit();
        int getDamage();
};
#pragma once
#include <iostream>
#include "Pokemon.hpp"
#include <vector>
using namespace std;

class Player {
    private:
        string name;
        vector<Pokemon> team;
        int activePokemon;
        int money;
    
    public:
        Player(string playerName);
        void addPokemon(Pokemon newPokemon);
        void switchPokemon(int index);
        void displayTeam();
        bool hasAlivePokemon();
        int getTeamSize();
        int getCurrPokemon();
        string getName();
        Pokemon* getActivePokemon();
};
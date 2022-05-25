//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_POKEMON_H
#define POKEMON_BATTLE_POKEMON_H

#include "Moves.h"

#include <string>
#include <vector>

using namespace std;

const int NUM_MOVES = 4;

class Pokemon {
private:
    int hp;
    int attack;
    int spAttack;
    int defense;
    int spDefense;
    int speed;
    int accuracy;

    string name;
    vector<Moves> moveSet;
public:
    Pokemon();
    Pokemon(const string& nameToSet, int hpToSet);

    void SetHP(int val);
    void SetAttack(int val);
    void SetSpAttack(int val);
    void SetDefense(int val);
    void SetSpDefense(int val);
    void SetSpeed(int val);
    void SetAccuracy(int val);

    int GetHP() const;
    int GetAttack() const;
    int GetSpAttack() const;
    int GetDefense() const;
    int GetSpDefense() const;
    int GetSpeed() const;
    int GetAccuracy() const;

    void SetName(const string& newName);
    string GetName() const;

    void SetMoves(const Moves& move1, const Moves& move2, const Moves& move3, const Moves& move4);
    vector<Moves> GetMoves() const;
};

#endif //POKEMON_BATTLE_POKEMON_H
//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_POKEMON_H
#define POKEMON_BATTLE_POKEMON_H

#include "Moves.h"

#include <string>

const int NUM_MOVES = 4, NUM_TYPES = 2;

class Pokemon {
private:
    int currentHp, attack, spAttack, defense, spDefense, speed, accuracy,
        maxHp, baseAttack, baseSpAttack, baseDefense, baseSpDefense, baseSpeed;

    std::string name, types[NUM_TYPES], status;
    Moves moveSet[NUM_MOVES];
public:
    Pokemon();
    Pokemon(const std::string& name, const std::string& type, int hp);
    Pokemon(const std::string& name, const std::string& type1, const std::string& type2, int hp);

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

    int GetMaxHP() const;
    int GetBaseAttack() const;
    int GetBaseSpAttack() const;
    int GetBaseDefense() const;
    int GetBaseSpDefense() const;
    int GetBaseSpeed() const;

    void SetBaseStats(int attack, int spAttack, int defense, int spDefense, int speed);

    void SetName(const std::string& newName);
    std::string GetName() const;

    std::string GetType() const;
    std::string GetType(int type) const;

    void SetStatus(const std::string& newStatus);
    std::string GetStatus();

    void SetMoves(const Moves& move1, const Moves& move2, const Moves& move3, const Moves& move4);
    Moves& GetMove(int move);
};

#endif //POKEMON_BATTLE_POKEMON_H
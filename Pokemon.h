//
// Created by miles on 5/5/2022.
//

#pragma once

#include "Moves.h"

const int NUM_MOVES = 4, NUM_TYPES = 2;

class Pokemon {
private:
    int currentHp, attack, spAttack, defense, spDefense, speed, accuracy,
        maxHp, baseAttack, baseSpAttack, baseDefense, baseSpDefense, baseSpeed;
    int level;

    std::string name, types[NUM_TYPES], status;
    Moves moveSet[NUM_MOVES];
public:
    Pokemon();
    Pokemon(const Pokemon& pokemonToCopy);
    Pokemon(const std::string& name, const std::string& type, int level);
    Pokemon(const std::string& name, const std::string& type1, const std::string& type2, int level);

    void setHP(int newHp);
    void setAttack(int newAttack);
    void setSpAttack(int newSpAttack);
    void setDefense(int newDefense);
    void setSpDefense(int newSpDefense);
    void setSpeed(int newSpeed);
    void setAccuracy(int newAccuracy);

    int getHP() const;
    int getAttack() const;
    int getSpAttack() const;
    int getDefense() const;
    int getSpDefense() const;
    int getSpeed() const;
    int getAccuracy() const;

    int getMaxHp() const;
    int getBaseAttack() const;
    int getBaseSpAttack() const;
    int getBaseDefense() const;
    int getBaseSpDefense() const;
    int getBaseSpeed() const;

    void setBaseStats(int hp, int attack, int spAttack, int defense, int spDefense, int speed);

    std::string getName() const;

    std::string getType() const;
    std::string getType(int type) const;

    void setStatus(const std::string& newStatus);
    std::string getStatus();

    void setMoves(const Moves& move1, const Moves& move2, const Moves& move3, const Moves& move4);
    Moves& getMove(int move);

    int getLevel() const;
};
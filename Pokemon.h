//
// Created by miles on 5/5/2022.
//

#pragma once

#include <vector>
#include <array>
#include "Move.h"

class Pokemon {
private:
    enum {MAX_NUM_MOVES = 4, MAX_NUM_TYPES = 2};

    int maxHp;
    int currentHp;
    int attack;
    int spAttack;
    int defense;
    int spDefense;
    int speed;
    int accuracy;

    int baseAttack;
    int baseSpAttack;
    int baseDefense;
    int baseSpDefense;
    int baseSpeed;
    int level;

    std::string name;
    std::string status;
    std::array<std::string, MAX_NUM_TYPES> types;
    std::vector<Move> moveSet;

public:
    Pokemon();
    Pokemon(const Pokemon &);
    Pokemon(const std::string &, const std::string &, int);
    Pokemon(const std::string &, const std::string &, const std::string &, int);

    int numMoves() const;

    void setHP(int);
    void setAttack(int);
    void setSpAttack(int);
    void setDefense(int);
    void setSpDefense(int);
    void setSpeed(int);
    void setAccuracy(int);

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

    void setBaseStats(int, int, int, int, int, int);

    std::string getName() const;

    std::string getType() const;
    std::string getType(int) const;

    void setStatus(const std::string &);
    std::string getStatus() const;

    void setMoves(const std::initializer_list<Move> &);

    int getLevel() const;

    void faint();

    Move& operator[](int);
    const Move& operator[](int) const;

    friend std::ostream& operator<<(std::ostream &, const Pokemon &);
};
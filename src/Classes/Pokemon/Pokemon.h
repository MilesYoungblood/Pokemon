//
// Created by miles on 5/5/2022.
//

#pragma once

#include <vector>
#include <array>
#include "../Move/Move.h"

class Pokemon {
private:
    const static int MAX_NUM_MOVES = 4;
    const static int MAX_NUM_TYPES = 2;

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
    Move* moveSet[Pokemon::MAX_NUM_MOVES];
    std::string types[Pokemon::MAX_NUM_TYPES];
    
    int moveCounter;

public:
    Pokemon();
    Pokemon(const Pokemon &pokemonToCopy);
    Pokemon(const char * name, const char * type, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed);
    Pokemon(const char * name, const char * type1, const char * type2, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed);
    //Pokemon(const char * name, const char * type1, const char * type2, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed, const std::vector<Move*> &moves);
    Pokemon& operator=(const Pokemon& pokemonToCopy);
    ~Pokemon();

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

    std::string getName() const;

    std::string getType(bool type_1) const;

    void setStatus(const char * newStatus);
    std::string getStatus() const;

    void setMoves(const std::initializer_list<Move*> &moves);

    int getLevel() const;

    void faint();
    bool isFainted() const;
    bool isFullHP() const;
    bool isFasterThan(const Pokemon &pokemon) const;
    bool isAfflicted() const;

    Move& operator[](int);
    const Move& operator[](int) const;

    friend std::ostream& operator<<(std::ostream &out, const Pokemon &pokemon);
};
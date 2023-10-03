//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../Entity/Entity.h"
#include "../Move/Move.h"
#include "../Item/Item.h"

class Pokemon : public Entity {
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
    Move* moveSet[Pokemon::MAX_NUM_MOVES];
    Type types[Pokemon::MAX_NUM_TYPES];
    Status status;
    
    int moveCounter;
    void setMoves(const std::vector<Move*> &moves);

public:
    Pokemon(const char * name, Type type, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed, const std::vector<Move*> &moves);
    Pokemon(const char * name, Type type1, Type type2, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed, const std::vector<Move*> &moves);
    Pokemon(const Pokemon &pokemonToCopy) = delete;
    Pokemon& operator=(const Pokemon &rhs) = delete;
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

    Type getType(bool type_1) const;

    void setStatus(Status newStatus);
    Status getStatus() const;

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
//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../Entity/Entity.h"
#include "../Move/Move.h"

enum class Status { NONE, BURN, PARALYSIS, FREEZE, POISON, SLEEP };

enum PokemonID {
    VENASAUR,
    CHARIZARD,
    PIKACHU,
    LUCARIO,
    HYDREIGON,
    GRENINJA
};

class Pokemon : public Entity {
private:
    const static int MAX_NUM_MOVES = 4;
    const static int MAX_NUM_TYPES = 2;

    const char *name;

    int maxHP;
    int currentHP;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;
    int accuracy;
    int evasiveness;

    int baseAttack;
    int baseDefense;
    int baseSpAttack;
    int baseSpDefense;
    int baseSpeed;
    int level;

    int catchRate;

    Move *moveSet[Pokemon::MAX_NUM_MOVES];
    Type types[Pokemon::MAX_NUM_TYPES];
    Status status;
    
    int moveCounter;

    static void raiseStat(int &stat, int amount);
    static void lowerStat(int &stat, int amount);

    static double getStatMod(int stat);

public:
    Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate);
    Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate);
    Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate, const std::initializer_list<Move*> &moves);
    Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate, const std::initializer_list<Move*> &moves);
    Pokemon(const Pokemon &) = delete;
    Pokemon& operator=(const Pokemon &) = delete;
    virtual ~Pokemon();

    virtual PokemonID getID() = 0;

    int numMoves() const;

    void addMove(Move *move);
    void setMoves(const std::initializer_list<Move*> &moves);

    void setHP(int newHP);
    void restoreHP(int newHP);
    void takeDamage(int amount);

    void resetStatMods();

    void raiseAttack(int amount);
    void raiseDefense(int amount);
    void raiseSpAttack(int amount);
    void raiseSpDefense(int amount);
    void raiseSpeed(int amount);
    void raiseAccuracy(int amount);
    void raiseEvasiveness(int amount);

    void lowerAttack(int amount);
    void lowerDefense(int amount);
    void lowerSpAttack(int amount);
    void lowerSpDefense(int amount);
    void lowerSpeed(int amount);
    void lowerAccuracy(int amount);
    void lowerEvasiveness(int amount);

    int getHP() const;
    int getAttack() const;
    int getDefense() const;
    int getSpAttack() const;
    int getSpDefense() const;
    int getSpeed() const;
    int getAccuracy() const;
    int getEvasiveness() const;

    int getMaxHp() const;
    int getBaseAttack() const;
    int getBaseDefense() const;
    int getBaseSpAttack() const;
    int getBaseSpDefense() const;
    int getBaseSpeed() const;

    std::string getName() const;

    Type getType(bool type_1) const;

    void setStatus(Status newStatus);
    Status getStatus() const;
    const char * getStatusAsString();

    int getLevel() const;
    int getCatchRate() const;

    bool isFainted() const;
    bool isFullHP() const;
    bool isFasterThan(const Pokemon &pokemon) const;
    bool isAfflicted() const;
    bool canAttack() const;

    void hpEmptyMessage() const;
    void hpFullMessage() const;

    Move& operator[](int index);
    const Move& operator[](int index) const;

    friend std::ostream& operator<<(std::ostream &out, const Pokemon &pokemon);
};
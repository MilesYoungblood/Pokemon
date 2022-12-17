//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon() {
    maxHp = 300;
    currentHp = 300;
    attack = 1;
    spAttack = 1;
    defense = 1;
    spDefense = 1;
    speed = 1;
    accuracy = 1;

    baseAttack = 100;
    baseSpAttack = 100;
    baseDefense = 100;
    baseSpDefense = 100;
    baseSpeed = 100;

    name = "No name";
    types[0] = "No type";
    types[1] = "No type";
    status = "No status";

    level = 1;
}

Pokemon::Pokemon(const Pokemon &pokemonToCopy) {
    maxHp = pokemonToCopy.maxHp;
    currentHp = pokemonToCopy.currentHp;
    attack = pokemonToCopy.attack;
    spAttack = pokemonToCopy.spAttack;
    defense = pokemonToCopy.defense;
    spDefense = pokemonToCopy.spDefense;
    speed = pokemonToCopy.speed;
    accuracy = pokemonToCopy.accuracy;

    baseAttack = pokemonToCopy.baseAttack;
    baseSpAttack = pokemonToCopy.baseSpAttack;
    baseDefense = pokemonToCopy.baseDefense;
    baseSpDefense = pokemonToCopy.baseSpDefense;
    baseSpeed = pokemonToCopy.baseSpeed;

    name = pokemonToCopy.name;
    types[0] = pokemonToCopy.types[0];
    types[1] = pokemonToCopy.types[1];
    status = pokemonToCopy.status;

    level = pokemonToCopy.level;
}

Pokemon::Pokemon(const std::string &name, const std::string &type, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed) {
    maxHp = hp;
    currentHp = hp;
    attack = 1;
    spAttack = 1;
    defense = 1;
    spDefense = 1;
    speed = 1;
    accuracy = 1;

    baseAttack = bAttack;
    baseSpAttack = bSpAttack;
    baseDefense = bDefense;
    baseSpDefense = bSpDefense;
    baseSpeed = bSpeed;

    this->name = name;
    types[0] = type;
    types[1] = "No type";
    status = "No status";

    this->level = level;
}

Pokemon::Pokemon(const std::string &name, const std::string &type1, const std::string &type2, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed) {
    maxHp = hp;
    currentHp = hp;
    attack = 1;
    spAttack = 1;
    defense = 1;
    spDefense = 1;
    speed = 1;
    accuracy = 1;

    baseAttack = bAttack;
    baseSpAttack = bSpAttack;
    baseDefense = bDefense;
    baseSpDefense = bSpDefense;
    baseSpeed = bSpeed;

    this->name = name;
    types[0] = type1;
    types[1] = type2;
    status = "No status";

    this->level = level;
}

int Pokemon::numMoves() const {
    return static_cast<int>(moveSet.size());
}

void Pokemon::setHP(int newHp) { currentHp = newHp; }
void Pokemon::setAttack(int newAttack) { attack = newAttack; }
void Pokemon::setSpAttack(int newSpAttack) { spAttack = newSpAttack; }
void Pokemon::setDefense(int newDefense) { defense = newDefense; }
void Pokemon::setSpDefense(int newSpDefense) { spDefense = newSpDefense; }
void Pokemon::setSpeed(int newSpeed) { speed = newSpeed; }
void Pokemon::setAccuracy(int newAccuracy) { accuracy = newAccuracy; }

int Pokemon::getMaxHp() const { return maxHp; }
int Pokemon::getHP() const { return currentHp; }
int Pokemon::getAttack() const { return attack; }
int Pokemon::getSpAttack() const { return spAttack; }
int Pokemon::getDefense() const { return defense; }
int Pokemon::getSpDefense() const { return spDefense; }
int Pokemon::getSpeed() const { return speed; }
int Pokemon::getAccuracy() const { return accuracy; }

int Pokemon::getBaseAttack() const { return baseAttack; }
int Pokemon::getBaseSpAttack() const { return baseSpAttack; }
int Pokemon::getBaseDefense() const { return baseDefense; }
int Pokemon::getBaseSpDefense() const { return baseSpDefense; }
int Pokemon::getBaseSpeed() const { return baseSpeed; }

std::string Pokemon::getName() const {
    return name;
}

std::string Pokemon::getType() const {
    return types[0];
}
std::string Pokemon::getType(int type) const {
    return types[type];
}

void Pokemon::setStatus(const std::string &newStatus) {
    status = newStatus;
}
std::string Pokemon::getStatus() const {
    return status;
}

void Pokemon::setMoves(const std::initializer_list<Move> &moves) {
    moveSet.clear();
    for (const auto &move : moves) {
        if (moveSet.size() < MAX_NUM_MOVES) {
            moveSet.push_back(move);
        }
        else {
            return;
        }
    }
}

int Pokemon::getLevel() const {
    return level;
}

void Pokemon::faint() {
    currentHp = 0;
}

Move& Pokemon::operator[](int spot) {
    return moveSet[spot];
}

const Move& Pokemon::operator[](int spot) const {
    return moveSet[spot];
}

std::ostream& operator<<(std::ostream &out, const Pokemon &pokemon) {
    out << pokemon.getName();
    return out;
}
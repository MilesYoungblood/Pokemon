//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon() {
    this->maxHp = 300;
    this->currentHp = 300;
    this->attack = 1;
    this->spAttack = 1;
    this->defense = 1;
    this->spDefense = 1;
    this->speed = 1;
    this->accuracy = 1;

    this->baseAttack = 100;
    this->baseSpAttack = 100;
    this->baseDefense = 100;
    this->baseSpDefense = 100;
    this->baseSpeed = 100;

    this->name = "No name";
    this->types[0] = "No type";
    this->types[1] = "No type";
    this->status = "No status";

    this->level = 1;
    this->moveCounter = 0;
}

Pokemon::Pokemon(const Pokemon &pokemonToCopy) {
    this->maxHp = pokemonToCopy.maxHp;
    this->currentHp = pokemonToCopy.currentHp;
    this->attack = pokemonToCopy.attack;
    this->spAttack = pokemonToCopy.spAttack;
    this->defense = pokemonToCopy.defense;
    this->spDefense = pokemonToCopy.spDefense;
    this->speed = pokemonToCopy.speed;
    this->accuracy = pokemonToCopy.accuracy;

    this->baseAttack = pokemonToCopy.baseAttack;
    this->baseSpAttack = pokemonToCopy.baseSpAttack;
    this->baseDefense = pokemonToCopy.baseDefense;
    this->baseSpDefense = pokemonToCopy.baseSpDefense;
    this->baseSpeed = pokemonToCopy.baseSpeed;

    this->name = pokemonToCopy.name;
    this->types[0] = pokemonToCopy.types[0];
    this->types[1] = pokemonToCopy.types[1];
    this->status = pokemonToCopy.status;

    this->level = pokemonToCopy.level;
    this->moveCounter = 0;
}

Pokemon::Pokemon(const std::string &name, const std::string &type, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed, const std::initializer_list<Move> &move_set) {
    this->maxHp = hp;
    this->currentHp = hp;
    this->attack = 1;
    this->spAttack = 1;
    this->defense = 1;
    this->spDefense = 1;
    this->speed = 1;
    this->accuracy = 1;

    this->baseAttack = bAttack;
    this->baseSpAttack = bSpAttack;
    this->baseDefense = bDefense;
    this->baseSpDefense = bSpDefense;
    this->baseSpeed = bSpeed;

    this->name = name;
    this->types[0] = type;
    this->types[1] = "No type";
    this->status = "No status";

    this->level = level;

    for (Move &move : this->moveSet)
        move = {};

    this->moveCounter = 0;
    for (const Move &move : move_set) {
        if (this->moveCounter == Pokemon::MAX_NUM_MOVES)
            break;

        else {
            this->moveSet[this->moveCounter] = move;
            ++this->moveCounter;
        }
    }
}

Pokemon::Pokemon(const std::string &name, const std::string &type1, const std::string &type2, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed, const std::initializer_list<Move> &move_set) {
    this->maxHp = hp;
    this->currentHp = hp;
    this->attack = 1;
    this->spAttack = 1;
    this->defense = 1;
    this->spDefense = 1;
    this->speed = 1;
    this->accuracy = 1;

    this->baseAttack = bAttack;
    this->baseSpAttack = bSpAttack;
    this->baseDefense = bDefense;
    this->baseSpDefense = bSpDefense;
    this->baseSpeed = bSpeed;

    this->name = name;
    this->types[0] = type1;
    this->types[1] = type2;
    this->status = "No status";

    this->level = level;

    for (Move &move : this->moveSet)
        move = {};

    this->moveCounter = 0;
    for (const Move &move : move_set) {
        if (this->moveCounter == Pokemon::MAX_NUM_MOVES)
            break;

        else {
            this->moveSet[this->moveCounter] = move;
            ++this->moveCounter;
        }
    }
}

Pokemon& Pokemon::operator=(const Pokemon &pokemonToCopy) {
    if (this != &pokemonToCopy) {
        this->maxHp = pokemonToCopy.maxHp;
        this->currentHp = pokemonToCopy.currentHp;
        this->attack = pokemonToCopy.attack;
        this->spAttack = pokemonToCopy.spAttack;
        this->defense = pokemonToCopy.defense;
        this->spDefense = pokemonToCopy.spDefense;
        this->speed = pokemonToCopy.speed;
        this->accuracy = pokemonToCopy.accuracy;

        this->baseAttack = pokemonToCopy.baseAttack;
        this->baseSpAttack = pokemonToCopy.baseSpAttack;
        this->baseDefense = pokemonToCopy.baseDefense;
        this->baseSpDefense = pokemonToCopy.baseSpDefense;
        this->baseSpeed = pokemonToCopy.baseSpeed;

        this->name = pokemonToCopy.name;
        this->types[0] = pokemonToCopy.types[0];
        this->types[1] = pokemonToCopy.types[1];
        this->status = pokemonToCopy.status;

        this->level = pokemonToCopy.level;
        this->moveCounter = pokemonToCopy.moveCounter;
        this->moveSet = pokemonToCopy.moveSet;
    }
    return *this;
}

int Pokemon::numMoves() const { return this->moveCounter; }

void Pokemon::setHP(int newHp) { this->currentHp = newHp; }
void Pokemon::setAttack(int newAttack) { this->attack = newAttack; }
void Pokemon::setSpAttack(int newSpAttack) { this->spAttack = newSpAttack; }
void Pokemon::setDefense(int newDefense) { this->defense = newDefense; }
void Pokemon::setSpDefense(int newSpDefense) { this->spDefense = newSpDefense; }
void Pokemon::setSpeed(int newSpeed) { this->speed = newSpeed; }
void Pokemon::setAccuracy(int newAccuracy) { this->accuracy = newAccuracy; }

int Pokemon::getMaxHp() const { return this->maxHp; }
int Pokemon::getHP() const { return this->currentHp; }
int Pokemon::getAttack() const { return this->attack; }
int Pokemon::getSpAttack() const { return this->spAttack; }
int Pokemon::getDefense() const { return this->defense; }
int Pokemon::getSpDefense() const { return this->spDefense; }
int Pokemon::getSpeed() const { return this->speed; }
int Pokemon::getAccuracy() const { return this->accuracy; }

int Pokemon::getBaseAttack() const { return this->baseAttack; }
int Pokemon::getBaseSpAttack() const { return this->baseSpAttack; }
int Pokemon::getBaseDefense() const { return this->baseDefense; }
int Pokemon::getBaseSpDefense() const { return this->baseSpDefense; }
int Pokemon::getBaseSpeed() const { return this->baseSpeed; }

std::string Pokemon::getName() const { return this->name; }

std::string Pokemon::getType(bool type_1) const { return type_1 ? this->types[0] : this->types[1]; }

void Pokemon::setStatus(const std::string &newStatus) { this->status = newStatus; }
std::string Pokemon::getStatus() const { return this->status; }

void Pokemon::setMoves(const std::initializer_list<Move> &moves) {
    // clear the current move list
    for (Move &move : this->moveSet)
        move = {};

    this->moveCounter = 0;
    for (const Move &move : moves) {
        if (this->moveCounter == Pokemon::MAX_NUM_MOVES)
            break;

        else {
            this->moveSet[this->moveCounter] = move;
            ++this->moveCounter;
        }
    }
}

int Pokemon::getLevel() const { return this->level; }

void Pokemon::faint() { this->currentHp = 0; }

bool Pokemon::isFainted() const { return this->currentHp <= 0; }
bool Pokemon::isFullHP() const { return this->currentHp == this->maxHp; }

bool Pokemon::isFasterThan(const Pokemon &pokemon) const { return this->baseSpeed > pokemon.baseSpeed; }
bool Pokemon::isAfflicted() const { return this->status != "No status"; }

Move& Pokemon::operator[](int spot) { return this->moveSet[spot]; }
const Move& Pokemon::operator[](int spot) const { return this->moveSet[spot]; }

std::ostream& operator<<(std::ostream &out, const Pokemon &pokemon) {
    out << pokemon.getName();
    return out;
}
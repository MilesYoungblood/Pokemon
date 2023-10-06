//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed) : moveSet(), types() {
    this->name = name;
    this->maxHP = hp;
    this->currentHP = hp;
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

    this->types[0] = type;
    this->types[1] = Type::NONE;
    this->status = Status::NONE;

    this->level = level;
    this->moveCounter = 0;
}

Pokemon::Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed, const std::initializer_list<Move*> &moves)
    : Pokemon(name, type, level, hp, bAttack, bSpAttack, bDefense, bSpDefense, bSpeed) {
    this->setMoves(moves);
}

Pokemon::Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed) : moveSet(), types() {
    this->name = name;
    this->maxHP = hp;
    this->currentHP = hp;
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

    this->types[0] = type1;
    this->types[1] = type2;
    this->status = Status::NONE;

    this->level = level;
    this->moveCounter = 0;
}

Pokemon::Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed, const std::initializer_list<Move *> &moves)
    : Pokemon(name, type1, type2, level, hp, bAttack, bSpAttack, bDefense, bSpDefense, bSpeed) {
    this->setMoves(moves);
}

Pokemon::~Pokemon() {
    for (int i = 0; i < this->moveCounter; ++i) {
        if (this->moveSet[i] != nullptr) {
            delete this->moveSet[i];
        }
    }
}

int Pokemon::numMoves() const { return this->moveCounter; }

void Pokemon::addMove(Move *move) {
    if (this->moveCounter == Pokemon::MAX_NUM_MOVES)
        return;

    this->moveSet[this->moveCounter] = move;
    ++this->moveCounter;
}

void Pokemon::setHP(int newHP) {
    this->currentHP = newHP;

    // HP cannot be set lower than 0
    if (this->currentHP < 0) {
        this->currentHP = 0;
    }
    // HP cannot be set higher than max HP
    else if (this->currentHP > this->maxHP) {
        this->currentHP = this->maxHP;
    }
}
void Pokemon::setAttack(int newAttack) { this->attack = newAttack; }
void Pokemon::setSpAttack(int newSpAttack) { this->spAttack = newSpAttack; }
void Pokemon::setDefense(int newDefense) { this->defense = newDefense; }
void Pokemon::setSpDefense(int newSpDefense) { this->spDefense = newSpDefense; }
void Pokemon::setSpeed(int newSpeed) { this->speed = newSpeed; }
void Pokemon::setAccuracy(int newAccuracy) { this->accuracy = newAccuracy; }

int Pokemon::getMaxHp() const { return this->maxHP; }
int Pokemon::getHP() const { return this->currentHP; }
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

void Pokemon::restoreHP(int amount) { this->currentHP += amount; }

std::string Pokemon::getName() const { return this->name; }

Type Pokemon::getType(bool type_1) const { return type_1 ? this->types[0] : this->types[1]; }

void Pokemon::setStatus(Status newStatus) { this->status = newStatus; }
Status Pokemon::getStatus() const { return this->status; }

const char * Pokemon::getStatusAsString() {
    switch (this->status) {
        case Status::PARALYSIS:
            return "paralysis";

        case Status::BURN:
            return "burn";

        case Status::FREEZE:
            return "freezing";

        case Status::POISON:
            return "poisoning";

        case Status::SLEEP:
            return "slumber";

        default:
            throw std::runtime_error("Unexpected error: function getStatusAsString");
    }
}

void Pokemon::setMoves(const std::initializer_list<Move*> &moves) {
    for (Move *move : moves) {
        if (this->moveCounter == Pokemon::MAX_NUM_MOVES)
            break;

        else {
            this->moveSet[this->moveCounter] = move;
            ++this->moveCounter;
        }
    }
}

int Pokemon::getLevel() const { return this->level; }

bool Pokemon::isFainted() const { return this->currentHP == 0; }
bool Pokemon::isFullHP() const { return this->currentHP == this->maxHP; }

bool Pokemon::isFasterThan(const Pokemon &pokemon) const { return this->baseSpeed > pokemon.baseSpeed; }
bool Pokemon::isAfflicted() const { return this->status != Status::NONE; }

void Pokemon::hpEmptyMessage() const {
    printMessage(this->getName() + "'s HP is empty!\n");
}
void Pokemon::hpFullMessage() const {
    printMessage(this->getName() + "'s HP is full!\n");
}

Move& Pokemon::operator[](int index) {
    if (3 < index or index < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return *this->moveSet[index];
}
const Move& Pokemon::operator[](int index) const {
    if (3 < index or index < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return *this->moveSet[index];
}

std::ostream& operator<<(std::ostream &out, const Pokemon &pokemon) {
    out << pokemon.getName();
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Move::action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage) {
    // damage will be negative if the attack misses
    if (damage > 0)
        defendingPokemon.setHP(defendingPokemon.getHP() - damage);

    --this->pp;
}

void Move::actionMessage(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool criticalHit, double typeEff) {
    printMessage(attackingPokemon.getName() + " used " + this->name + "! ");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // damage will be negative if the attack misses
    if (damage > 0) {
        if (typeEff == 0.0) {
            printMessage("It doesn't affect " + defendingPokemon.getName() + "...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else if (typeEff >= 2.0) {
            printMessage(this->getName() + " did " + std::to_string(damage) + " damage! ");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            printMessage("It's super effective!\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (criticalHit) {
                printMessage("A critical hit! ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else if (typeEff <= 0.5) {
            printMessage(this->getName() + " did " + std::to_string(damage) + " damage! ");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            printMessage("It's not very effective...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (criticalHit) {
                printMessage("A critical hit! ");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else {
            printMessage(this->getName() + " did " + std::to_string(damage) + " damage!\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    else {
        printMessage(defendingPokemon.getName() + " avoided the attack!\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout.flush();
}
//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate) : moveSet(), types() {
    this->name = name;
    this->maxHP = hp;
    this->currentHP = hp;
    this->attack = 0;
    this->defense = 0;
    this->spAttack = 0;
    this->spDefense = 0;
    this->speed = 0;
    this->accuracy = 0;
    this->evasiveness = 0;

    this->baseAttack = bAttack;
    this->baseDefense = bDefense;
    this->baseSpAttack = bSpAttack;
    this->baseSpDefense = bSpDefense;
    this->baseSpeed = bSpeed;

    this->catchRate = catchRate;

    this->types[0] = type;
    this->types[1] = Type::NONE;
    this->status = Status::NONE;

    this->level = level;
    this->moveCounter = 0;
}

Pokemon::Pokemon(const char *name, Type type, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate, const std::initializer_list<Move*> &moves)
    : Pokemon(name, type, level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed, catchRate) {
    this->setMoves(moves);
}

Pokemon::Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate) : moveSet(), types() {
    this->name = name;
    this->maxHP = hp;
    this->currentHP = hp;
    this->attack = 0;
    this->spAttack = 0;
    this->defense = 0;
    this->spDefense = 0;
    this->speed = 0;
    this->accuracy = 0;
    this->evasiveness = 0;

    this->baseAttack = bAttack;
    this->baseDefense = bDefense;
    this->baseSpAttack = bSpAttack;
    this->baseSpDefense = bSpDefense;
    this->baseSpeed = bSpeed;

    this->catchRate = catchRate;

    this->types[0] = type1;
    this->types[1] = type2;
    this->status = Status::NONE;

    this->level = level;
    this->moveCounter = 0;
}

Pokemon::Pokemon(const char *name, Type type1, Type type2, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed, int catchRate, const std::initializer_list<Move *> &moves)
    : Pokemon(name, type1, type2, level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed, catchRate) {
    this->setMoves(moves);
}

Pokemon::~Pokemon() {
    for (int i = 0; i < this->moveCounter; ++i) {
        if (this->moveSet[i] != nullptr) {
            std::cout << "\t\tDeleting " << this->name << "'s " << this->moveSet[i]->getName() << '!' << std::endl;
            delete this->moveSet[i];
        }
    }
}

void Pokemon::raiseStat(int &stat, int amount) {
    stat += amount;

    // stat modifier cannot be higher than 6
    if (stat > 6) {
        stat = 6;
    }
}

void Pokemon::lowerStat(int &stat, int amount) {
    stat -= amount;

    // stat modifier cannot be lower than -6
    if (stat < -6) {
        stat = -6;
    }
}

double Pokemon::getStatMod(int stat) {
    switch (stat) {
        case -6:
            return 0.25;
        case -5:
            return 2.0 / 7.0;
        case -4:
            return 2.0 / 6.0;
        case -3:
            return 0.4;
        case -2:
            return 0.5;
        case -1:
            return 2.0 / 3.0;
        case 0:
            return 1.0;
        case 1:
            return 1.5;
        case 2:
            return 2.0;
        case 3:
            return 2.5;
        case 4:
            return 3.0;
        case 5:
            return 3.5;
        case 6:
            return 4.0;
        default:
            throw std::runtime_error("Unexpected error: function getStatMod");
    }
}

int Pokemon::numMoves() const { return this->moveCounter; }

void Pokemon::addMove(Move *move) {
    if (this->moveCounter == Pokemon::MAX_NUM_MOVES)
        return;

    this->moveSet[this->moveCounter] = move;
    ++this->moveCounter;
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

void Pokemon::restoreHP(int amount) {
    this->currentHP += amount;

    if (this->currentHP > this->maxHP) {
        this->currentHP = this->maxHP;
    }
}

void Pokemon::takeDamage(int amount) {
    this->currentHP -= amount;

    if (this->currentHP < 0) {
        this->currentHP = 0;
    }
}

void Pokemon::resetStatMods() {
    this->attack = 0;
    this->spAttack = 0;
    this->defense = 0;
    this->spDefense = 0;
    this->speed = 0;
    this->accuracy = 0;
    this->evasiveness = 0;
}

void Pokemon::raiseAttack(int amount) {
    this->raiseStat(this->attack, amount);
}

void Pokemon::raiseDefense(int amount) {
    this->raiseStat(this->defense, amount);
}

void Pokemon::raiseSpAttack(int amount) {
    this->raiseStat(this->spAttack, amount);
}

void Pokemon::raiseSpDefense(int amount) {
    this->raiseStat(this->spDefense, amount);
}

void Pokemon::raiseSpeed(int amount) {
    this->raiseStat(this->speed, amount);
}

void Pokemon::raiseAccuracy(int amount) {
    this->raiseStat(this->accuracy, amount);
}

void Pokemon::raiseEvasiveness(int amount) {
    this->raiseStat(this->evasiveness, amount);
}

void Pokemon::lowerAttack(int amount) {
    this->lowerStat(this->attack, amount);
}

void Pokemon::lowerDefense(int amount) {
    this->lowerStat(this->defense, amount);
}

void Pokemon::lowerSpAttack(int amount) {
    this->lowerStat(this->spAttack, amount);
}

void Pokemon::lowerSpDefense(int amount) {
    this->lowerStat(this->spDefense, amount);
}

void Pokemon::lowerSpeed(int amount) {
    this->lowerStat(this->speed, amount);
}

void Pokemon::lowerAccuracy(int amount) {
    this->lowerStat(this->accuracy, amount);
}

void Pokemon::lowerEvasiveness(int amount) {
    this->lowerStat(this->evasiveness, amount);
}

int Pokemon::getMaxHp() const { return this->maxHP; }
int Pokemon::getHP() const { return this->currentHP; }
int Pokemon::getAttack() const { return this->attack; }
int Pokemon::getDefense() const { return this->defense; }
int Pokemon::getSpAttack() const { return this->spAttack; }
int Pokemon::getSpDefense() const { return this->spDefense; }
int Pokemon::getSpeed() const { return this->speed; }
int Pokemon::getAccuracy() const { return this->accuracy; }
int Pokemon::getEvasiveness() const { return this->evasiveness; }

int Pokemon::getBaseAttack() const {
    return this->baseAttack * static_cast<int>(lround(getStatMod(this->attack)));
}

int Pokemon::getBaseDefense() const {
    return this->baseDefense * static_cast<int>(lround(getStatMod(this->defense)));
}

int Pokemon::getBaseSpAttack() const {
    return this->baseSpAttack * static_cast<int>(lround(getStatMod(this->spAttack)));
}

int Pokemon::getBaseSpDefense() const {
    return this->baseSpDefense * static_cast<int>(lround(getStatMod(this->spDefense)));
}

int Pokemon::getBaseSpeed() const {
    return this->baseSpeed * static_cast<int>(lround(getStatMod(this->speed)));
}

std::string Pokemon::getName() const { return this->name; }

Type Pokemon::getType(bool type_1) const { return type_1 ? this->types[0] : this->types[1]; }

void Pokemon::setStatus(Status newStatus) {
    this->status = newStatus;

    if (this->status == Status::NONE) {
        if (newStatus == Status::BURN)
            this->attack *= 2;
        else if (newStatus == Status::PARALYSIS)
            this->speed *= 2;
    }

    else if (this->status == Status::BURN)
        this->attack /= 2;

    else if (this->status == Status::PARALYSIS)
        this->speed /= 2;
}
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

int Pokemon::getLevel() const { return this->level; }
int Pokemon::getCatchRate() const { return this->catchRate; }

bool Pokemon::isFainted() const { return this->currentHP == 0; }
bool Pokemon::isFullHP() const { return this->currentHP == this->maxHP; }

bool Pokemon::isFasterThan(const Pokemon &pokemon) const { return this->baseSpeed > pokemon.baseSpeed; }
bool Pokemon::isAfflicted() const { return this->status != Status::NONE; }

bool Pokemon::canAttack() const {
    for (int i = 0; i < this->moveCounter; ++i) {
        if (not this->moveSet[i]) {
            return false;
        }
    }
    return true;
}

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

void Move::action(Pokemon &attackingPokemon, Pokemon &defendingPokemon, int damage, bool &skip) {
    // damage will be negative if the attack misses
    if (damage > 0)
        defendingPokemon.takeDamage(damage);

    --this->pp;
}

void Move::actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, int damage, bool skipTurn, bool criticalHit, double typeEff) {
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
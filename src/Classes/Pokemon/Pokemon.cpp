//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon(const char *name, const Type type, const int level, const int hp, const int bAttack, const int bDefense, const int bSpAttack, const int bSpDefense, const int bSpeed, const int catchRate)
    : name(name), maxHP(hp), currentHP(hp), baseAttack(bAttack), baseDefense(bDefense), baseSpAttack(bSpAttack), baseSpDefense(bSpDefense), baseSpeed(bSpeed), level(level), catchRate(catchRate), types() {
    this->types[0] = type;
    this->types[1] = Type::NONE;
}

Pokemon::Pokemon(const char *name, const Type type, const int level, const int hp, const int bAttack, const int bDefense, const int bSpAttack, const int bSpDefense, const int bSpeed, const int catchRate, const std::initializer_list<Move*> &moves)
    : Pokemon(name, type, level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed, catchRate) {
    this->setMoves(moves);
}

Pokemon::Pokemon(const char *name, const Type type1, const Type type2, const int level, const int hp, const int bAttack, const int bDefense, const int bSpAttack, const int bSpDefense, const int bSpeed, const int catchRate)
    : name(name), maxHP(hp), currentHP(hp), baseAttack(bAttack), baseDefense(bDefense), baseSpAttack(bSpAttack), baseSpDefense(bSpDefense), baseSpeed(bSpeed), level(level), catchRate(catchRate), types() {
    this->types[0] = type1;
    this->types[1] = type2;
}

Pokemon::Pokemon(const char *name, const Type type1, const Type type2, const int level, const int hp, const int bAttack, const int bDefense, const int bSpAttack, const int bSpDefense, const int bSpeed, const int catchRate, const std::initializer_list<Move *> &moves)
    : Pokemon(name, type1, type2, level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed, catchRate) {
    this->setMoves(moves);
}

Pokemon::~Pokemon() {
    for (int i = 0; i < this->moveCounter; ++i) {
        if (this->moveSet[i] != nullptr) {
            std::cout << "\t\tDeleting " << this->name << "'s " << this->moveSet[i]->getName() << "!\n";
            delete this->moveSet[i];
        }
    }
}

void Pokemon::raiseStat(int &stat, const int amount) {
    stat += amount;

    // stat modifier cannot be higher than 6
    if (stat > 6) {
        stat = 6;
    }
}

void Pokemon::lowerStat(int &stat, const int amount) {
    stat -= amount;

    // stat modifier cannot be lower than -6
    if (stat < -6) {
        stat = -6;
    }
}

auto Pokemon::getStatMod(const int stat) -> double {
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

auto Pokemon::numMoves() const -> int { return this->moveCounter; }

void Pokemon::addMove(Move *move) {
    if (this->moveCounter == Pokemon::MAX_NUM_MOVES) {
        return;
    }

    this->moveSet.push_back(move);
    ++this->moveCounter;
}

void Pokemon::deleteMove(const int index) {
    if (index < 0 or this->moveCounter - 1 < index ) {
        return;
    }

    delete this->moveSet[index];
    this->moveSet[index] = nullptr;

    this->moveSet.erase(this->moveSet.begin() + index);
    --this->moveCounter;
}

void Pokemon::setMoves(const std::initializer_list<Move *> &moves) {
    for (Move *move : moves) {
        if (this->moveCounter == Pokemon::MAX_NUM_MOVES) {
            break;
        }

        this->moveSet.push_back(move);
        ++this->moveCounter;

    }
}

void Pokemon::setHP(const int newHP) {
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

void Pokemon::restoreHP(const int amount) {
    this->currentHP += amount;

    if (this->currentHP > this->maxHP) {
        this->currentHP = this->maxHP;
    }
}

void Pokemon::takeDamage(const int amount) {
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

void Pokemon::raiseAttack(const int amount) {
    this->raiseStat(this->attack, amount);
}

void Pokemon::raiseDefense(const int amount) {
    this->raiseStat(this->defense, amount);
}

void Pokemon::raiseSpAttack(const int amount) {
    this->raiseStat(this->spAttack, amount);
}

void Pokemon::raiseSpDefense(const int amount) {
    this->raiseStat(this->spDefense, amount);
}

void Pokemon::raiseSpeed(const int amount) {
    this->raiseStat(this->speed, amount);
}

void Pokemon::raiseAccuracy(const int amount) {
    this->raiseStat(this->accuracy, amount);
}

void Pokemon::raiseEvasiveness(const int amount) {
    this->raiseStat(this->evasiveness, amount);
}

void Pokemon::lowerAttack(const int amount) {
    this->lowerStat(this->attack, amount);
}

void Pokemon::lowerDefense(const int amount) {
    this->lowerStat(this->defense, amount);
}

void Pokemon::lowerSpAttack(const int amount) {
    this->lowerStat(this->spAttack, amount);
}

void Pokemon::lowerSpDefense(const int amount) {
    this->lowerStat(this->spDefense, amount);
}

void Pokemon::lowerSpeed(const int amount) {
    this->lowerStat(this->speed, amount);
}

void Pokemon::lowerAccuracy(const int amount) {
    this->lowerStat(this->accuracy, amount);
}

void Pokemon::lowerEvasiveness(const int amount) {
    this->lowerStat(this->evasiveness, amount);
}

auto Pokemon::getMaxHp() const -> int { return this->maxHP; }
auto Pokemon::getHP() const -> int { return this->currentHP; }
auto Pokemon::getAttack() const -> int { return this->attack; }
auto Pokemon::getDefense() const -> int { return this->defense; }
auto Pokemon::getSpAttack() const -> int { return this->spAttack; }
auto Pokemon::getSpDefense() const -> int { return this->spDefense; }
auto Pokemon::getSpeed() const -> int { return this->speed; }
auto Pokemon::getAccuracy() const -> int { return this->accuracy; }
auto Pokemon::getEvasiveness() const -> int { return this->evasiveness; }

auto Pokemon::getBaseAttack() const -> int {
    return this->baseAttack * static_cast<int>(lround(getStatMod(this->attack)));
}

auto Pokemon::getBaseDefense() const -> int {
    return this->baseDefense * static_cast<int>(lround(getStatMod(this->defense)));
}

auto Pokemon::getBaseSpAttack() const -> int {
    return this->baseSpAttack * static_cast<int>(lround(getStatMod(this->spAttack)));
}

auto Pokemon::getBaseSpDefense() const -> int {
    return this->baseSpDefense * static_cast<int>(lround(getStatMod(this->spDefense)));
}

auto Pokemon::getBaseSpeed() const -> int {
    return this->baseSpeed * static_cast<int>(lround(getStatMod(this->speed)));
}

auto Pokemon::getName() const -> std::string { return this->name; }

auto Pokemon::getType(const bool type_1) const -> Type { return type_1 ? this->types[0] : this->types[1]; }

void Pokemon::setStatus(const Status newStatus) {
    this->status = newStatus;

    if (this->status == Status::NONE) {
        if (newStatus == Status::BURN) {
            this->attack *= 2;
        }
        else if (newStatus == Status::PARALYSIS) {
            this->speed *= 2;
        }
    }
    else if (this->status == Status::BURN) {
        this->attack /= 2;
    }
    else if (this->status == Status::PARALYSIS) {
        this->speed /= 2;
    }
}
auto Pokemon::getStatus() const -> Status { return this->status; }

auto Pokemon::getStatusAsString() const -> const char * {
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

auto Pokemon::getLevel() const -> int { return this->level; }
auto Pokemon::getCatchRate() const -> int { return this->catchRate; }

auto Pokemon::isFainted() const -> bool { return this->currentHP == 0; }
auto Pokemon::isFullHP() const -> bool { return this->currentHP == this->maxHP; }

auto Pokemon::isFasterThan(const Pokemon &pokemon) const -> bool { return this->baseSpeed > pokemon.baseSpeed; }
auto Pokemon::isAfflicted() const -> bool { return this->status != Status::NONE; }

auto Pokemon::canAttack() const -> bool {
    for (int i = 0; i < this->moveCounter; ++i) {
        if (this->moveSet[i] == nullptr) {
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

auto Pokemon::operator[](const int index) -> Move& {
    return *this->moveSet[index];
}
auto Pokemon::operator[](const int index) const -> const Move& {
    return *this->moveSet[index];
}

auto operator<<(std::ostream &out, const Pokemon &pokemon) -> std::ostream& {
    out << pokemon.name;
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Move::action(Pokemon & /*attackingPokemon*/, Pokemon &defendingPokemon, int damage, bool & /*skip*/) {
    // damage will be negative if the attack misses
    if (damage > 0) {
        defendingPokemon.takeDamage(damage);
    }

    --this->pp;
}

void Move::actionMessage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const int damage, const bool  /*skipTurn*/, const bool criticalHit, const double typeEff) {
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

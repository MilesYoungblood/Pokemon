//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon(Pokemon::Id id) : id(id) {
    if (Pokemon::dataFunction == nullptr) {
        throw std::runtime_error("Initialization function is null");
    }

    const Pokemon::Data data = Pokemon::dataFunction(this->id);

    this->setName(data.name.data());

    this->maxHp = data.baseHp;
    this->currentHp = data.baseHp;

    this->baseStats.insert(std::make_pair(Pokemon::Stat::ATTACK, data.baseAttack));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::DEFENSE, data.baseDefense));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SP_ATTACK, data.baseSpAttack));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SP_DEFENSE, data.baseSpDefense));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SPEED, data.baseSpeed));

    this->statModifiers.insert(std::make_pair(Pokemon::Stat::ATTACK, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::DEFENSE, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SP_ATTACK, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SP_DEFENSE, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SPEED, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::ACCURACY, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::EVASIVENESS, 0));

    this->level = data.baseLevel;
}

Pokemon::Pokemon(Pokemon::Id id, int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Entity(0, 0), id(id), maxHp(hp), currentHp(hp), level(level) {
    this->baseStats.insert(std::make_pair(Pokemon::Stat::ATTACK, bAttack));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::DEFENSE, bDefense));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SP_ATTACK, bSpAttack));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SP_DEFENSE, bSpDefense));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SPEED, bSpeed));

    this->statModifiers.insert(std::make_pair(Pokemon::Stat::ATTACK, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::DEFENSE, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SP_ATTACK, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SP_DEFENSE, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SPEED, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::ACCURACY, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::EVASIVENESS, 0));
}

Pokemon::Pokemon(Pokemon &&toMove) noexcept
        : id(toMove.id), maxHp(toMove.maxHp), currentHp(toMove.currentHp), statModifiers(std::move(toMove.statModifiers)),
          baseStats(std::move(toMove.baseStats)), level(toMove.level), moveSet(std::move(toMove.moveSet)), status(toMove.status) {}

Pokemon &Pokemon::operator=(Pokemon &&rhs) noexcept {
    this->id = rhs.id;
    this->maxHp = rhs.maxHp;
    this->currentHp = rhs.currentHp;
    this->statModifiers = std::move(rhs.statModifiers);
    this->baseStats = std::move(rhs.baseStats);
    this->level = rhs.level;
    this->moveSet = std::move(rhs.moveSet);
    this->status = rhs.status;

    return *this;
}

void Pokemon::initData(Pokemon::Data (*instructions)(Pokemon::Id id)) {
    static bool initialized = false;

    if (initialized) {
        return;
    }

    Pokemon::dataFunction = instructions;
    initialized = true;
}

Type Pokemon::getType(bool type1) const {
    return type1 ? Pokemon::dataFunction(this->id).type1 : Pokemon::dataFunction(this->id).type2;
}

int Pokemon::numMoves() const {
    return static_cast<int>(this->moveSet.size());
}

void Pokemon::addMove(std::unique_ptr<Move> toAdd) {
    if (this->moveSet.size() == Pokemon::MAX_NUM_MOVES) {
        return;
    }

    this->moveSet.push_back(std::move(toAdd));
}

void Pokemon::deleteMove(const int index) {
    try {
        this->moveSet.erase(this->moveSet.begin() + index);
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error deleting move: ") + e.what() + '\n');
    }
}

void Pokemon::restoreHp(const int amount) {
    this->currentHp = std::min(this->currentHp + amount, this->maxHp);
}

void Pokemon::takeDamage(const int amount) {
    this->currentHp = std::max(this->currentHp - amount, 0);
}

int Pokemon::getHp() const {
    return this->currentHp;
}

int Pokemon::getMaxHp() const {
    return this->maxHp;
}

void Pokemon::initStatMods() {
    this->statModifiers[Pokemon::Stat::ATTACK] = 0;
    this->statModifiers[Pokemon::Stat::DEFENSE] = 0;
    this->statModifiers[Pokemon::Stat::SP_ATTACK] = 0;
    this->statModifiers[Pokemon::Stat::SP_DEFENSE] = 0;
    this->statModifiers[Pokemon::Stat::SPEED] = 0;
    this->statModifiers[Pokemon::Stat::ACCURACY] = 0;
    this->statModifiers[Pokemon::Stat::EVASIVENESS] = 0;
}

void Pokemon::raiseStatMod(Pokemon::Stat stat, int amount) {
    this->statModifiers.at(stat) = std::min(this->statModifiers.at(stat) + amount, 6);
}

void Pokemon::lowerStatMod(Pokemon::Stat stat, int amount) {
    this->statModifiers.at(stat) = std::max(this->statModifiers.at(stat) - amount, -6);
}

double Pokemon::getStat(const Pokemon::Stat stat) const {
    switch (this->statModifiers.at(stat)) {
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

int Pokemon::getStatMod(const Pokemon::Stat stat) const {
    try {
        return this->statModifiers.at(stat);
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error accessing Pokemon stat: ") + e.what() + '\n');
    }
}

int Pokemon::getBaseStat(Pokemon::Stat stat) const {
    try {
        return static_cast<int>(std::round(this->baseStats.at(stat) * this->getStat(stat)));
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error accessing Pokemon stat: ") + e.what() + ' ' +
                                 std::to_string(static_cast<int>(stat)) + '\n');
    }
}

void Pokemon::setStatus(const Status newStatus) {
    this->status = newStatus;

    if (this->status == Status::NONE) {
        if (newStatus == Status::BURN) {
            this->baseStats[Pokemon::Stat::ATTACK] *= 2;
        }
        else if (newStatus == Status::PARALYSIS) {
            this->baseStats[Pokemon::Stat::SPEED] *= 2;
        }
    }
    else if (this->status == Status::BURN) {
        this->baseStats[Pokemon::Stat::ATTACK] /= 2;
    }
    else if (this->status == Status::PARALYSIS) {
        this->baseStats[Pokemon::Stat::SPEED] /= 2;
    }
}

Status Pokemon::getStatus() const {
    return this->status;
}

const char *Pokemon::getStatusAsString() const {
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

void Pokemon::levelUp() {
    ++this->level;
}

int Pokemon::getLevel() const {
    return this->level;
}

int Pokemon::getCatchRate() const {
    return Pokemon::dataFunction(this->id).catchRate;
}

Pokemon::Id Pokemon::getId() const {
    return this->id;
}

bool Pokemon::isFainted() const {
    return this->currentHp == 0;
}

bool Pokemon::isFullHp() const {
    return this->currentHp == this->maxHp;
}

bool Pokemon::isFasterThan(const Pokemon &pokemon) const {
    return this->baseStats.at(Pokemon::Stat::SPEED) > pokemon.baseStats.at(Pokemon::Stat::SPEED);
}

bool Pokemon::isAfflicted() const {
    return this->status != Status::NONE;
}

bool Pokemon::canAttack() const {
    return std::ranges::all_of(this->moveSet.begin(), this->moveSet.end(),[](const std::unique_ptr<Move> &move) -> bool { return not move.operator bool(); });
}

void Pokemon::hpEmptyMessage() const {
    printMessage(this->getName() + "'s HP is empty!\n");
}

void Pokemon::hpFullMessage() const {
    printMessage(this->getName() + "'s HP is full!\n");
}

Move &Pokemon::operator[](const int index) {
    try {
        return *this->moveSet.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing move-set: ") + e.what() + '\n');
    }
}

const Move &Pokemon::operator[](const int index) const {
    try {
        return *this->moveSet.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing move-set: ") + e.what() + '\n');
    }
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
    printMessage(attackingPokemon.getName() + " used " + this->getName() + "! ");
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

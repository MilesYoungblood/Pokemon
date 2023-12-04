//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon(Ability::Id aId, int level, int hp, double attack, double defense, double spAttack, double spDefense,
                 double speed) : maxHp(hp), currentHp(hp), level(level), gender(Pokemon::Gender::GENDERLESS) {
    try {
        this->ability = abilityMap.at(aId)();
    }
    catch (const std::exception &e) {
        std::clog << "Error adding Ability: " << e.what() << '\n';
        this->ability = nullptr;
    }

    this->baseStats.insert(std::make_pair(Pokemon::Stat::ATTACK, attack));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::DEFENSE, defense));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SP_ATTACK, spAttack));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SP_DEFENSE, spDefense));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SPEED, speed));

    this->statModifiers.insert(std::make_pair(Pokemon::Stat::ATTACK, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::DEFENSE, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SP_ATTACK, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SP_DEFENSE, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SPEED, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::ACCURACY, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::EVASIVENESS, 0));
}

Pokemon::Pokemon(Ability::Id ability, double pMale, int level, int hp, double attack, double defense, double spAttack,
                 double spDefense, double speed)
        : maxHp(hp), currentHp(hp), level(level),
          gender(binomial(pMale) ? Pokemon::Gender::MALE : Pokemon::Gender::FEMALE) {
    try {
        this->ability = abilityMap.at(ability)();
    }
    catch (const std::exception &e) {
        std::clog << "Error adding Ability: " << e.what() << '\n';
        this->ability = nullptr;
    }

    this->baseStats.insert(std::make_pair(Pokemon::Stat::ATTACK, attack));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::DEFENSE, defense));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SP_ATTACK, spAttack));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SP_DEFENSE, spDefense));
    this->baseStats.insert(std::make_pair(Pokemon::Stat::SPEED, speed));

    this->statModifiers.insert(std::make_pair(Pokemon::Stat::ATTACK, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::DEFENSE, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SP_ATTACK, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SP_DEFENSE, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::SPEED, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::ACCURACY, 0));
    this->statModifiers.insert(std::make_pair(Pokemon::Stat::EVASIVENESS, 0));
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

void Pokemon::tryActivateAbility(int battleFlag, Pokemon &opponent, bool isAttacking) {
    // only activate the ability of the battle battleFlag and corresponding ability battleFlag match
    if (this->ability->getFlag() == battleFlag) {
        if (isAttacking) {
            this->ability->action(*this, opponent);
        }
        else {
            this->ability->action(opponent, *this);
        }
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

double Pokemon::getBaseStat(Pokemon::Stat stat) const {
    try {
        return std::round(this->baseStats.at(stat) * this->getStat(stat));
    }
    catch (const std::exception &e) {
        std::clog << "Error accessing Pokemon stat: " << e.what() << static_cast<int>(stat) << '\n';
        std::terminate();
    }
}

void Pokemon::setStatus(const Status newStatus) {
    this->status = newStatus;

    if (this->status == Status::NONE) {
        if (newStatus == Status::BURN) {
            this->baseStats[Pokemon::Stat::ATTACK] *= 2.0;
        }
        else if (newStatus == Status::PARALYSIS) {
            this->baseStats[Pokemon::Stat::SPEED] *= 2.0;
        }
    }
    else if (this->status == Status::BURN) {
        this->baseStats[Pokemon::Stat::ATTACK] /= 2.0;
    }
    else if (this->status == Status::PARALYSIS) {
        this->baseStats[Pokemon::Stat::SPEED] /= 2.0;
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

void Pokemon::setGender(Pokemon::Gender newGender) {
    this->gender = newGender;
}

Pokemon::Gender Pokemon::getGender() const {
    return this->gender;
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
    return std::ranges::all_of(this->moveSet.begin(), this->moveSet.end(),
                               [](const std::unique_ptr<Move> &move) -> bool { return not *move; });
}

std::string Pokemon::hpEmptyMessage() const {
    return this->getName() + "'s HP is empty!";
}

std::string Pokemon::hpFullMessage() const {
    return this->getName() + "'s HP is full!";
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

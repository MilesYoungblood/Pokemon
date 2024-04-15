//
// Created by miles on 5/5/2022.
//

#include "../../../../../../Functions/GeneralFunctions.h"
#include "../../../../../Singleton/DerivedClasses/Pokedex/Pokedex.h"
#include "Pokemon.h"

Pokemon::Pokemon(const std::string &id) : Character(id, id), baseStats(), statModifiers({ 0, 0, 0, 0, 0, 0, 0 }) {
    if (const double ratio = Pokedex::getInstance().getGenderRatio(id); ratio == -1) {
        this->gender = "Genderless";
    }
    else {
        this->gender = binomial(ratio) ? "Male" : "Female";
    }

    this->hp = Project::Resource(Pokedex::getInstance().getBaseStat(id, 0), this->hp.getCurrent());
    this->level = Pokedex::getInstance().getBaseLevel(id);

    for (int i = 0; i < this->baseStats.size(); ++i) {
        this->baseStats.at(i) = Pokedex::getInstance().getBaseStat(id, i + 1);
    }
}

Pokemon::Pokemon(std::string id, std::string name, std::string gender, std::string ability, const int level,
                 const int hp, const int attack, const int defense, const int spAttack, const int spDefense, const int speed)
        : Character(std::move(name), std::move(id)), hp(hp, hp), baseStats({ attack, defense, spAttack, spDefense, speed }), statModifiers({ 0, 0, 0, 0, 0, 0, 0 }), level(level),
          ability(std::move(ability)), gender(std::move(gender)) {}

int Pokemon::numMoves() const {
    return static_cast<int>(this->moveSet.size());
}

void Pokemon::addMove(const std::string &id) {
    if (this->moveSet.size() == MAX_NUM_MOVES) {
        return;
    }
    this->moveSet.push_back(std::move(moveMap.at(id)()));
}

void Pokemon::deleteMove(const int index) {
    try {
        this->moveSet.erase(this->moveSet.begin() + index);
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error deleting move: ") + e.what() + '\n');
    }
}

Project::Resource &Pokemon::getHp() {
    return this->hp;
}

Project::Resource Pokemon::getHp() const {
    return this->hp;
}

void Pokemon::initStatMods() {
    this->statModifiers[static_cast<std::size_t>(Stat::ATTACK)] = 0;
    this->statModifiers[static_cast<std::size_t>(Stat::DEFENSE)] = 0;
    this->statModifiers[static_cast<std::size_t>(Stat::SP_ATTACK)] = 0;
    this->statModifiers[static_cast<std::size_t>(Stat::SP_DEFENSE)] = 0;
    this->statModifiers[static_cast<std::size_t>(Stat::SPEED)] = 0;
    this->statModifiers[static_cast<std::size_t>(Stat::ACCURACY)] = 0;
    this->statModifiers[static_cast<std::size_t>(Stat::EVASIVENESS)] = 0;
}

void Pokemon::raiseStatMod(Stat stat, const int amount) {
    this->statModifiers.at(static_cast<std::size_t>(stat)) = std::min(
            this->statModifiers.at(static_cast<std::size_t>(stat)) + amount, 6);
}

void Pokemon::lowerStatMod(Stat stat, const int amount) {
    this->statModifiers.at(static_cast<std::size_t>(stat)) = std::max(
            this->statModifiers.at(static_cast<std::size_t>(stat)) - amount, -6);
}

double Pokemon::getStat(Stat stat) const {
    switch (this->statModifiers.at(static_cast<std::size_t>(stat))) {
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

int Pokemon::getStatMod(Stat stat) const {
    try {
        return this->statModifiers.at(static_cast<std::size_t>(stat));
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error accessing Pokemon stat: ") + e.what() + '\n');
    }
}

double Pokemon::getBaseStat(Stat stat) const {
    try {
        return std::round(this->baseStats.at(static_cast<std::size_t>(stat)) * this->getStat(stat));
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error accessing stat: ") + e.what() + '\n');
    }
}

void Pokemon::setStatus(const StatusCondition newStatus) {
    if (this->status == StatusCondition::NONE) {
        if (newStatus == StatusCondition::BURN) {
            this->baseStats[static_cast<std::size_t>(Stat::ATTACK)] *= 2.0;
        }
        else if (newStatus == StatusCondition::PARALYSIS) {
            this->baseStats[static_cast<std::size_t>(Stat::SPEED)] *= 2.0;
        }
    }
    else if (this->status == StatusCondition::BURN) {
        this->baseStats[static_cast<std::size_t>(Stat::ATTACK)] /= 2.0;
    }
    else if (this->status == StatusCondition::PARALYSIS) {
        this->baseStats[static_cast<std::size_t>(Stat::SPEED)] /= 2.0;
    }

    this->status = newStatus;
}

StatusCondition Pokemon::getStatus() const {
    return this->status;
}

void Pokemon::levelUp() {
    this->level = std::min(this->level + 1, 100);
}

int Pokemon::getLevel() const {
    return this->level;
}

std::string Pokemon::getGender() const {
    return this->gender;
}

std::string Pokemon::getAbility() const {
    return this->ability;
}

std::string Pokemon::getSpecies() const {
    return Pokedex::getInstance().getSpecies(this->getId());
}

Type Pokemon::getType1() const {
    return Pokedex::getInstance().getType1(this->getId());
}

Type Pokemon::getType2() const {
    return Pokedex::getInstance().getType2(this->getId());
}

double Pokemon::getHeight() const {
    return Pokedex::getInstance().getHeight(this->getId());
}

double Pokemon::getWeight() const {
    return Pokedex::getInstance().getWeight(this->getId());
}

int Pokemon::getCatchRate() const {
    return Pokedex::getInstance().getCatchRate(this->getId());
}

bool Pokemon::isFasterThan(const Pokemon &pokemon) const {
    return this->baseStats.at(static_cast<std::size_t>(Stat::SPEED)) >
           pokemon.baseStats.at(static_cast<std::size_t>(Stat::SPEED));
}

bool Pokemon::rivalsInSpeed(const Pokemon &pokemon) const {
    return this->baseStats.at(static_cast<std::size_t>(Stat::SPEED)) ==
           pokemon.baseStats.at(static_cast<std::size_t>(Stat::SPEED));
}

bool Pokemon::isAfflicted() const {
    return this->status != StatusCondition::NONE;
}

bool Pokemon::canAttack() const {
    return std::ranges::any_of(this->moveSet.begin(), this->moveSet.end(),
                               [](const std::unique_ptr<Move> &move) -> bool { return move->canUse(); });
}

std::string Pokemon::hpEmptyMessage() const {
    return this->getName() + "'s HP is empty!";
}

std::string Pokemon::hpFullMessage() const {
    return this->getName() + "'s HP is full!";
}

Move &Pokemon::operator[](const int index) const {
    try {
        return *this->moveSet.at(index);
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range(std::string("Error accessing move-set: ") + e.what() + '\n');
    }
}

std::vector<std::unique_ptr<Move>>::iterator Pokemon::begin() {
    return this->moveSet.begin();
}

std::vector<std::unique_ptr<Move>>::const_iterator Pokemon::begin() const {
    return this->moveSet.cbegin();
}

std::vector<std::unique_ptr<Move>>::iterator Pokemon::end() {
    return this->moveSet.end();
}

std::vector<std::unique_ptr<Move>>::const_iterator Pokemon::end() const {
    return this->moveSet.cend();
}

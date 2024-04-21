//
// Created by miles on 5/5/2022.
//

#include "../../../../utility/Functions/GeneralFunctions.h"
#include "../../../Singleton/Cache/Pokedex/Pokedex.h"
#include "Pokemon.h"

const std::unordered_map<std::string, std::pair<std::string, std::string>> Pokemon::natures{
    std::make_pair("Adamant", std::make_pair("Attack", "Sp. Attack")),
    std::make_pair("Bashful", std::make_pair("Sp. Attack", "Sp. Attack")),
    std::make_pair("Bold", std::make_pair("Defense", "Attack")),
    std::make_pair("Brave", std::make_pair("Attack", "Speed")),
    std::make_pair("Calm", std::make_pair("Sp. Defense", "Attack")),
    std::make_pair("Careful", std::make_pair("Sp. Defense", "Sp. Attack")),
    std::make_pair("Docile", std::make_pair("Defense", "Defense")),
    std::make_pair("Gentle", std::make_pair("Sp. Defense", "Defense")),
    std::make_pair("Hardy", std::make_pair("Attack", "Attack")),
    std::make_pair("Hasty", std::make_pair("Speed", "Defense")),
    std::make_pair("Impish", std::make_pair("Defense", "Sp. Attack")),
    std::make_pair("Jolly", std::make_pair("Speed", "Sp. Attack")),
    std::make_pair("Lax", std::make_pair("Defense", "Sp. Defense")),
    std::make_pair("Lonely", std::make_pair("Attack", "Defense")),
    std::make_pair("Mild", std::make_pair("Sp. Attack", "Defense")),
    std::make_pair("Modest", std::make_pair("Sp. Attack", "Attack")),
    std::make_pair("Naive", std::make_pair("Speed", "Sp. Defense")),
    std::make_pair("Naughty", std::make_pair("Attack", "Sp. Defense")),
    std::make_pair("Quiet", std::make_pair("Sp. Attack", "Speed")),
    std::make_pair("Quirky", std::make_pair("Sp. Defense", "Sp. Defense")),
    std::make_pair("Rash", std::make_pair("Sp. Attack", "Sp. Defense")),
    std::make_pair("Relaxed", std::make_pair("Defense", "Speed")),
    std::make_pair("Sassy", std::make_pair("Sp. Defense", "Speed")),
    std::make_pair("Serious", std::make_pair("Speed", "Speed")),
    std::make_pair("Timid", std::make_pair("Speed", "Attack"))
};

Pokemon::Pokemon(const char *id) : Character(id, id) {
    if (const double ratio = Pokedex::getInstance()->getGenderRatio(id); ratio == -1) {
        this->gender = "Genderless";
    }
    else {
        this->gender = binomial(ratio) ? "Male" : "Female";
    }

    {
        const int random = generateInteger(1, static_cast<int>(natures.size()));
        int i = 0;
        for (const auto &nature: natures | std::views::keys) {
            if (i == random) {
                break;
            }
            this->nature = nature;
            ++i;
        }
    }

    this->hp = Component::Resource(Pokedex::getInstance()->getBaseStat(id, "HP"), this->hp.getCurrent());
    this->level = Pokedex::getInstance()->getBaseLevel(id);

    for (const auto &stat : std::array<const char *, 5>({ "Attack", "Defense", "Sp. Attack", "Sp. Defense", "Speed" })) {
        this->baseStats[stat] = Pokedex::getInstance()->getBaseStat(id, stat);
    }
}

Pokemon::Pokemon(const char *id, const char *name, std::string gender, std::string ability, const int level,
                 const int hp, const int attack, const int defense, const int spAttack, const int spDefense, const int speed)
        : Character(id, name), hp(hp, hp), level(level),
          ability(std::move(ability)), gender(std::move(gender)) {
    this->baseStats["HP"] = hp;
    this->baseStats["Attack"] = attack;
    this->baseStats["Defense"] = defense;
    this->baseStats["Sp. Attack"] = spAttack;
    this->baseStats["Sp. Defense"] = spDefense;
    this->baseStats["Speed"] = speed;
}

int Pokemon::numMoves() const {
    return static_cast<int>(this->moveSet.size());
}

void Pokemon::learnMove(const std::string &id) {
    if (this->moveSet.size() == MAX_NUM_MOVES) {
        return;
    }
    this->moveSet.push_back(std::move(moveMap.at(id)()));
}

void Pokemon::forgetMove(const int index) {
    try {
        this->moveSet.erase(this->moveSet.begin() + index);
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error deleting move: ") + e.what() + '\n');
    }
}

Component::Resource &Pokemon::getHp() {
    return this->hp;
}

Component::Resource Pokemon::getHp() const {
    return this->hp;
}

double Pokemon::getBaseStat(const std::string &x) const {
    try {
        return this->baseStats.at(x);
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error accessing stat: ") + e.what() + '\n');
    }
}

void Pokemon::setStatus(const StatusCondition x) {
    this->status = x;
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
    return Pokedex::getInstance()->getSpecies(this->getId());
}

Type Pokemon::getType1() const {
    return Pokedex::getInstance()->getType1(this->getId());
}

Type Pokemon::getType2() const {
    return Pokedex::getInstance()->getType2(this->getId());
}

double Pokemon::getHeight() const {
    return Pokedex::getInstance()->getHeight(this->getId());
}

double Pokemon::getWeight() const {
    return Pokedex::getInstance()->getWeight(this->getId());
}

int Pokemon::getCatchRate() const {
    return Pokedex::getInstance()->getCatchRate(this->getId());
}

bool Pokemon::isFasterThan(const Pokemon &pokemon) const {
    const double speedMod1 = this->status == StatusCondition::PARALYSIS ? 0.5 : 1.0;
    const double speedMod2 = pokemon.status == StatusCondition::PARALYSIS ? 0.5 : 1.0;

    return this->baseStats.at("Speed") * speedMod1 > pokemon.baseStats.at("Speed") * speedMod2;
}

bool Pokemon::rivalsInSpeed(const Pokemon &pokemon) const {
    const double speedMod1 = this->status == StatusCondition::PARALYSIS ? 0.5 : 1.0;
    const double speedMod2 = pokemon.status == StatusCondition::PARALYSIS ? 0.5 : 1.0;

    return this->baseStats.at("Speed") * speedMod1 == pokemon.baseStats.at("Speed") * speedMod2;
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

std::string Pokemon::initMessage() const {
    return "A wild " + this->getId() + " appeared!";
}

Pokemon *Pokemon::getAttacker() {
    return this;
}

const Pokemon *Pokemon::getAttacker() const {
    return this;
}

bool Pokemon::canFight() const {
    return not this->hp.empty();
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

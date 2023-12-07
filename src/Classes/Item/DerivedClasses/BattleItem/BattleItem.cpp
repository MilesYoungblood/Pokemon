//
// Created by Miles Youngblood on 12/1/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem(int quantity) : Item(quantity) {}

void BattleItem::boost(Pokemon &pokemon, int amount, bool &limit) const {
    if (pokemon.getStatMod(this->getStat()) < 6) {
        pokemon.raiseStatMod(this->getStat(), amount);
        limit = true;
    }
}

std::string BattleItem::boostMessage(const Pokemon &pokemon, int amount, bool limit) const {
    const char *(*getStatAsString)(Pokemon::Stat) = [](Pokemon::Stat stat) -> const char * {
        switch (stat) {
            case Pokemon::Stat::ATTACK:
                return "attack";
            case Pokemon::Stat::DEFENSE:
                return "defense";
            case Pokemon::Stat::SP_ATTACK:
                return "special attack";
            case Pokemon::Stat::SP_DEFENSE:
                return "special defense";
            case Pokemon::Stat::SPEED:
                return "speed";
            case Pokemon::Stat::ACCURACY:
                return "accuracy";
            default:
                throw std::runtime_error("Unexpected error: function boostMessage");
        }
    };

    std::string message{ pokemon.getName() + "'s " + getStatAsString(this->getStat()) };
    if (not limit) {
        message.append(" rose");
        if (amount == 2) {
            message.append(" sharply");
        }
        else if (amount > 2) {
            message.append(" drastically");
        }
        message += '!';
    }
    else {
        message.append(" cant go any higher!");
    }

    return message;
}

Item::Class BattleItem::getClass() const {
    return Item::Class::BATTLE;
}

//
// Created by Miles Youngblood on 12/1/2023.
//

#include "BattleItem.h"

BattleItem::BattleItem(const char *id, const int quantity) : Item(id, quantity) {}

void BattleItem::boost(Pokemon &pokemon, const int amount, bool &limit) const {

}

std::string BattleItem::boostMessage(const Pokemon &pokemon, const int amount, const bool limit) const {
    std::string message{ pokemon.getName() + "'s " + this->getStat() };
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

std::size_t BattleItem::getClass() const {
    return typeid(BattleItem).hash_code();
}

std::string BattleItem::getStat() const {
    return "";
}

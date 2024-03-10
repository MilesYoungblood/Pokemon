//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem(int quantity) : Item(quantity) {}

Item::Class StatusItem::getClass() const {
    return Item::Class::STATUS;
}

void StatusItem::restore(Pokemon &pokemon) const {
    if (this->getStatus() == pokemon.getStatus()) {
        pokemon.setStatus(StatusCondition::NONE);
    }
}

std::string StatusItem::restoreMessage(const Pokemon &pokemon) const {
    if (pokemon.getStatus() == StatusCondition::NONE) {
        return pokemon.getName() + " recovered from " + statusToString(pokemon.getStatus()) + '!';
    }
    else {
        return "But it failed!";
    }
}

//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem(const char *id, const int quantity) : Item(id, quantity) {}

std::size_t StatusItem::getClass() const {
    return typeid(StatusItem).hash_code();
}

void StatusItem::restore(Pokemon &pokemon) const {
    if (this->getStatus() == pokemon.getStatus()) {
        pokemon.setStatus(StatusCondition::NONE);
    }
}

std::string StatusItem::restoreMessage(const Pokemon &pokemon) {
    if (pokemon.getStatus() == StatusCondition::NONE) {
        return pokemon.getName() + " recovered from " + statusToString(pokemon.getStatus()) + '!';
    }
    return "But it failed!";
}

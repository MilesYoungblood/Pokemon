//
// Created by Miles on 18/05/2023.
//

#include "RestoreItem.h"

RestoreItem::RestoreItem(const char *id, const int quantity) : Item(id, quantity){}

std::size_t RestoreItem::getClass() const {
    return typeid(RestoreItem).hash_code();
}

void RestoreItem::restore(Pokemon &pokemon) const {
    if (this->isHp()) {
        pokemon.getHp().raise(this->getAmount());
    }
}

void RestoreItem::restore(Move &move) const {
    if (not this->isHp()) {
        move.getPp().raise(this->getAmount());
    }
}

std::string RestoreItem::restoreMessage(const Pokemon &pokemon) const {
    return pokemon.getName() + " recovered " + std::to_string(this->getAmount()) + " HP!";
}

std::string RestoreItem::restoreMessage(const Move &move) const {
    return move.getName() + "recovered " + std::to_string(this->getAmount()) + " PP!";
}

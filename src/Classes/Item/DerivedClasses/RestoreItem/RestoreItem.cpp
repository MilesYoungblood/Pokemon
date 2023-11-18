//
// Created by Miles on 18/05/2023.
//

#include "RestoreItem.h"

RestoreItem::RestoreItem(const int quantity) : Item(quantity) {}

Item::Class RestoreItem::getClass() const {
    return Item::Class::RESTORE;
}

void RestoreItem::restore(Pokemon &pokemon) const {
    if (this->isHp()) {
        pokemon.restoreHP(this->getAmount());
    }
}

void RestoreItem::restore(Move &move) const {
    if (not this->isHp()) {
        //FIXME implement restorePP function in move
        move.setPP(move.getPP() + this->getAmount());
    }
}

void RestoreItem::restoreMessage(const Pokemon &pokemon) const {
    printMessage(pokemon.getName() + " recovered " + std::to_string(this->getAmount()) + " HP!\n");
}

void RestoreItem::restoreMessage(const Move &move) const {
    printMessage(move.getName() + " recovered " + std::to_string(this->getAmount()) + " PP!\n");
}

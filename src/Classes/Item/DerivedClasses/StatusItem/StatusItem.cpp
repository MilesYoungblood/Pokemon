//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem(StatusItem::Id id, int quantity) : Item(quantity), id(id) {}

StatusItem::Id StatusItem::getId() const {
    return this->id;
}

Item::Class StatusItem::getClass() const {
    return Item::Class::STATUS;
}

void StatusItem::restore(Pokemon &pokemon) const {
    if (this->getStatus() == pokemon.getStatus()) {
        pokemon.setStatus(Status::NONE);
    }
}

void StatusItem::restoreMessage(const Pokemon &pokemon) {
    if (pokemon.getStatus() == Status::NONE) {
        printMessage(pokemon.getName() + " recovered from " + pokemon.getStatusAsString() + "!\n");
    }
    else {
        printMessage("But it failed!\n");
    }
}

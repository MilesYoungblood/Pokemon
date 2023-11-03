//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem(const int quantity) : Item(quantity) {}

ItemType StatusItem::getType() const { return ItemType::STATUS; }

void StatusItem::restore(Pokemon &pokemon) {
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

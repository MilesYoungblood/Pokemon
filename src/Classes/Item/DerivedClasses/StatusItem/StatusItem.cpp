//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem(const char *name, const int quantity, const Status status) : Item(name, quantity), status(status) {}

Status StatusItem::getStatus() const { return this->status; }

ItemType StatusItem::getType() const { return ItemType::STATUS; }

void StatusItem::restore(Pokemon &pokemon) {
    if (this->status == pokemon.getStatus()) {
        pokemon.setStatus(Status::NONE);
    }
}

void StatusItem::restore(Move &move) {}

void StatusItem::restoreMessage(const Pokemon &pokemon) {
    if (pokemon.getStatus() == Status::NONE) {
        printMessage(pokemon.getName() + " recovered from " + pokemon.getStatusAsString() + "!\n");
    }
    else {
        printMessage("But it failed!\n");
    }
}

void StatusItem::restoreMessage(const Move &move) {}

bool StatusItem::catchPokemon(const Pokemon & /*pokemon*/, std::array<bool, 4> & /*attempts*/) { return false; }

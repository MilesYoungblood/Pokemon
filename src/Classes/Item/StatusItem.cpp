//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem(const char *name, int quantity, Status status) : Item(name, quantity) { this->status = status; }

Status StatusItem::getStatus() const { return this->status; }

void StatusItem::restore(Pokemon &pokemon) {
    if (this->status == pokemon.getStatus()) {
        pokemon.setStatus(Status::NONE);
    }
}

void StatusItem::restore(Move &move) {}

void StatusItem::restoreMessage(Pokemon &pokemon) {
    if (pokemon.getStatus() == Status::NONE)
        printMessage(pokemon.getName() + " recovered from " + pokemon.getStatusAsString() + "!\n");
    else
        printMessage("But it failed!\n");
}

void StatusItem::restoreMessage(Move &move) {}

bool StatusItem::catchPokemon(const Pokemon &pokemon, bool attempts[]) { return false; }

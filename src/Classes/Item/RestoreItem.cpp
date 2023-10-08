//
// Created by Miles on 18/05/2023.
//

#include "RestoreItem.h"

RestoreItem::RestoreItem(const char *name, int quantity, int amount, RestoreType restoreType) : Item(name, quantity){
    this->amount = amount;
    this->restoreType = restoreType;
}

int RestoreItem::getAmount() const { return this->amount; }

RestoreType RestoreItem::getRestoreType() const { return this->restoreType; }

void RestoreItem::restore(Pokemon &pokemon) {
    if (this->restoreType == RestoreType::HP) {
        pokemon.restoreHP(this->amount);
    }
}

void RestoreItem::restore(Move &move) {
    if (this->restoreType == RestoreType::PP) {
        //FIXME implement restorePP function in move
        move.setPP(move.getPP() + this->amount);
    }
}

void RestoreItem::restoreMessage(Pokemon &pokemon) {
    printMessage(pokemon.getName() + " recovered " + std::to_string(this->amount) + " HP!\n");
}

void RestoreItem::restoreMessage(Move &move) {
    printMessage(move.getName() + " recovered " + std::to_string(this->amount) + " PP!\n");
}

bool RestoreItem::catchPokemon(const Pokemon &pokemon, bool attempts[]) { return false; }

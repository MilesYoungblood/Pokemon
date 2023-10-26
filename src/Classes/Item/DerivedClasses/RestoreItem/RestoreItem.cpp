//
// Created by Miles on 18/05/2023.
//

#include "RestoreItem.h"

RestoreItem::RestoreItem(const char *name, const int quantity, const int amount, const RestoreType restoreType) : Item(name, quantity), amount(amount), restoreType(restoreType) {}

int RestoreItem::getAmount() const { return this->amount; }

RestoreType RestoreItem::getRestoreType() const { return this->restoreType; }

ItemType RestoreItem::getType() const { return ItemType::RESTORE; }

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

void RestoreItem::restoreMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + " recovered " + std::to_string(this->amount) + " HP!\n");
}

void RestoreItem::restoreMessage(const Move &move) {
    printMessage(move.getName() + " recovered " + std::to_string(this->amount) + " PP!\n");
}

bool RestoreItem::catchPokemon(const Pokemon & /*pokemon*/, std::array<bool, 4> & /*attempts*/) { return false; }

//
// Created by Miles on 18/05/2023.
//

#include "RestoreItem.h"

RestoreItem::RestoreItem(RestoreItem::Id id, int quantity) : Item(quantity), id(id) {
    if (RestoreItem::nameFunction == nullptr or RestoreItem::amountFunction == nullptr or
        RestoreItem::isHpFunction == nullptr) {
        throw std::runtime_error("Tried constructing a Restore Item without initializing class\n");
    }
}

void RestoreItem::initName(std::string (*instructions)(RestoreItem::Id)) {
    RestoreItem::nameFunction = instructions;
}

void RestoreItem::initAmount(int (*instructions)(RestoreItem::Id)) {
    RestoreItem::amountFunction = instructions;
}

void RestoreItem::initHp(bool (*instructions)(RestoreItem::Id)) {
    RestoreItem::isHpFunction = instructions;
}

std::string RestoreItem::getName() const {
    return RestoreItem::nameFunction(this->id);
}

int RestoreItem::getAmount() const {
    return RestoreItem::amountFunction(this->id);
}

bool RestoreItem::isHp() const {
    return RestoreItem::isHpFunction(this->id);
}

RestoreItem::Id RestoreItem::getId() const {
    return this->id;
}

Item::Class RestoreItem::getClass() const {
    return Item::Class::RESTORE;
}

void RestoreItem::restore(Pokemon &pokemon) const {
    if (this->isHp()) {
        pokemon.restoreHp(this->getAmount());
    }
}

void RestoreItem::restore(Move &move) const {
    if (not this->isHp()) {
        move.restore(this->getAmount());
    }
}

void RestoreItem::restoreMessage(const Pokemon &pokemon) const {
    printMessage(pokemon.getName() + " recovered " + std::to_string(this->getAmount()) + " HP!\n");
}

void RestoreItem::restoreMessage(const Move &move) const {
    printMessage(move.getName() + " recovered " + std::to_string(this->getAmount()) + " PP!\n");
}

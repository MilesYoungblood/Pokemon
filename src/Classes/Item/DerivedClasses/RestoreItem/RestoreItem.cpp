//
// Created by Miles on 18/05/2023.
//

#include "RestoreItem.h"

RestoreItem::RestoreItem(RestoreItem::Id id, int quantity) : Item(quantity), id(id) {
    if (RestoreItem::dataFunction == nullptr) {
        throw std::runtime_error("Tried constructing a Restore Item without initializing class\n");
    }
}

void RestoreItem::init(RestoreItem::Data (*instructions)(RestoreItem::Id)) {
    RestoreItem::dataFunction = instructions;
}

std::string RestoreItem::getName() const {
    return std::string(RestoreItem::dataFunction(this->id).name);
}

int RestoreItem::getAmount() const {
    return RestoreItem::dataFunction(this->id).amount;
}

bool RestoreItem::isHp() const {
    return RestoreItem::dataFunction(this->id).isHp;
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

std::string RestoreItem::restoreMessage(const Pokemon &pokemon) const {
    return pokemon.getName() + " recovered " + std::to_string(this->getAmount()) + " HP!";
}

std::string RestoreItem::restoreMessage(const Move &move) const {
    return move.getName() + "recovered " + std::to_string(this->getAmount()) + " PP!";
}

//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem(StatusItem::Id id, int quantity) : Item(quantity), id(id) {
    if (StatusItem::dataFunction == nullptr) {
        throw std::runtime_error("Tried to construct a Status Item without initializing class\n");
    }
}

void StatusItem::init(StatusItem::Data (*instructions)(StatusItem::Id)) {
    StatusItem::dataFunction = instructions;
}

std::string StatusItem::getName() const {
    return std::string(StatusItem::dataFunction(this->id).name);
}

Status StatusItem::getStatus() const {
    return StatusItem::dataFunction(this->id).status;
}

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

std::string StatusItem::restoreMessage(const Pokemon &pokemon) const {
    if (pokemon.getStatus() == Status::NONE) {
        return pokemon.getName() + " recovered from " + pokemon.getStatusAsString() + '!';
    }
    else {
        return "But it failed!";
    }
}

//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem(StatusItem::Id id, int quantity) : Item(quantity), id(id) {
    if (StatusItem::nameFunction == nullptr or StatusItem::statusFunction == nullptr) {
        throw std::runtime_error("Tried to construct a Status Item without initializing class\n");
    }
}

void StatusItem::initName(std::string (*instructions)(StatusItem::Id)) {
    StatusItem::nameFunction = instructions;
}

void StatusItem::initStatus(Status (*instructions)(StatusItem::Id)) {
    StatusItem::statusFunction = instructions;
}

std::string StatusItem::getName() const {
    return StatusItem::nameFunction(this->id);
}

Status StatusItem::getStatus() const {
    return StatusItem::statusFunction(this->id);
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

void StatusItem::restoreMessage(const Pokemon &pokemon) {
    if (pokemon.getStatus() == Status::NONE) {
        printMessage(pokemon.getName() + " recovered from " + pokemon.getStatusAsString() + "!\n");
    }
    else {
        printMessage("But it failed!\n");
    }
}

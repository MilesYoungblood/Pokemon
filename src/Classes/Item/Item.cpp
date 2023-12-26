//
// Created by miles on 5/25/2022.
//

#include "Item.h"

Item::Item(int n) : quantity(n) {}

Item::Item(const Item &toCopy) = default;

int Item::getQuantity() const {
    return this->quantity;
}

void Item::add(const int n) {
    this->quantity += n;
}

void Item::use() {
    if (this->quantity > 0) {
        --this->quantity;
    }
}

std::string Item::useMessage() const {
    std::string message{ "You used a" };

    if (isVowel(this->getName()[0])) {
        message += 'n';
    }

    message.append(' ' + this->getName() + '!');
    return message;
}

std::string Item::noEffectMessage(const Pokemon &pokemon) const {
    return this->getName() + " had no effect on " + pokemon.getName() + ".\n";
}

Item::operator bool() const {
    return this->quantity > 0;
}

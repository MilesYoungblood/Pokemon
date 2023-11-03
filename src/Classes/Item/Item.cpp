//
// Created by miles on 5/25/2022.
//

#include "Item.h"

Item::Item(const int n) : quantity(n) {}

int Item::getQuantity() const {
    return this->quantity;
}

void Item::use() {
    if (this->quantity > 0) {
        --this->quantity;
    }
}

void Item::useMessage() {
    printMessage("You used a");

    if (isVowel(this->getName()[0])) {
        printMessage('n');
    }

    printMessage(' ' + this->getName() + "! ");
}

void Item::add() {
    ++this->quantity;
}

Item::operator bool() const {
    return this->quantity > 0;
}

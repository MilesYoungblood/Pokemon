//
// Created by miles on 5/25/2022.
//

#include "Item.h"

Item::Item() {
    this->name = "N/A";
    this->quantity = 0;
}

Item::Item(const char *name, const int n) {
    this->name = name;
    this->quantity = n;
}

void Item::setQuantity(const int n) { this->quantity = n; }
int Item::getQuantity() const { return this->quantity; }

void Item::use() {
    if (this->quantity > 0) {
        --this->quantity;
    }
}

void Item::useMessage() {
    printMessage("You used a");

    if (isVowel(this->name[0]))
        printMessage('n');

    printMessage(' ' + this->getName() + "! ");
}

int Item::getAmount() const {
    return 0;
}
RestoreType Item::getRestoreType() const {
    return RestoreType::NONE;
}
Status Item::getStatus() const {
    return Status::NONE;
}
Stat Item::getStat() const {
    return Stat::NONE;
}

std::string Item::getName() const { return this->name; }

std::ostream& operator<<(std::ostream &out, const Item &rhs) {
    out << rhs.name;
    return out;
}

Item::operator bool() const {
    return this->quantity > 0;
}

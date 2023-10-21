//
// Created by miles on 5/25/2022.
//

#include "Item.h"

Item::Item(const char *name, const int n) : name(name), quantity(n) {}

void Item::setQuantity(const int n) { this->quantity = n; }
auto Item::getQuantity() const -> int { return this->quantity; }

void Item::use() {
    if (this->quantity > 0) {
        --this->quantity;
    }
}

void Item::useMessage() {
    printMessage("You used a");

    if (isVowel(this->name[0])) {
        printMessage('n');
    }

    printMessage(' ' + this->getName() + "! ");
}

auto Item::getAmount() const -> int {
    return 0;
}

auto Item::getRestoreType() const -> RestoreType {
    return RestoreType::NONE;
}

auto Item::getStatus() const -> Status {
    return Status::NONE;
}

auto Item::getStat() const -> Stat {
    return Stat::NONE;
}

auto Item::getName() const -> std::string { return this->name; }

auto operator<<(std::ostream &out, const Item &rhs) -> std::ostream& {
    out << rhs.name;
    return out;
}

Item::operator bool() const {
    return this->quantity > 0;
}

//
// Created by miles on 5/25/2022.
//

#include "Item.h"

Item::Item() {
    this->quantity = 0;
    this->name = "No name";
}

Item::Item(const Item& copy) {
    this->quantity = copy.quantity;
    this->name = copy.name;
}

Item::Item(int n, const char * name) {
    this->quantity = n;
    this->name = name;
}

void Item::setQuantity(int n) { this->quantity = n; }
int Item::getQuantity() const { return this->quantity; }

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


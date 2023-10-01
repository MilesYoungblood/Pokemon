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

Item::Item(int quantity, const char * name) {
    this->quantity = quantity;
    this->name = name;
}

void Item::setQuantity(int newQuantity) { this->quantity = newQuantity; }
int Item::getQuantity() const { return this->quantity; }

std::string Item::getName() const { return this->name; }

bool Item::canUse() const {
    return this->quantity > 0;
}

std::ostream& operator<<(std::ostream &out, const Item &rhs) {
    out << rhs.name;
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


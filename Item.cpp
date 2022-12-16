//
// Created by miles on 5/25/2022.
//

#include "Item.h"

Item::Item() {
    quantity = 0;
    name = "No name";
}

Item::Item(const Item& copy) {
    this->quantity = copy.quantity;
    this->name = copy.name;
}

Item::Item(int quantity, const std::string& name) {
    this->quantity = quantity;
    this->name = name;
}

void Item::setQuantity(int newQuantity) {
    quantity = newQuantity;
}
int Item::getQuantity() const {
    return quantity;
}

std::string Item::getName() const {
    return name;
}

std::ostream& operator<<(std::ostream &out, const Item &rhs) {
    out << rhs.name;
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestoreItems::RestoreItems() : Item() {
    amount = 0;
    restoreType = "No restore type";
}
RestoreItems::RestoreItems(int quantity, int amount, const std::string& name, const std::string& restoreType) : Item(quantity, name){
    this->amount = amount;
    this->restoreType = restoreType;
}

int RestoreItems::getAmount() const {
    return amount;
}

std::string RestoreItems::getRestoreType() const {
    return restoreType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StatusItems::StatusItems() : Item() {
    restoreType = "No restore type";
}
StatusItems::StatusItems(const StatusItems &copy) = default;
StatusItems::StatusItems(int quantity, const std::string& name, const std::string& restoreType) : Item(quantity, name) {
    this->restoreType = restoreType;
}

std::string StatusItems::getRestoreType() const {
    return restoreType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PokeBalls::PokeBalls() : Item() {
    catchRate = 0.00;
}
PokeBalls::PokeBalls(int quantity, float catchRate, const std::string &name) : Item(quantity, name) {
    this->catchRate = catchRate;
}

float PokeBalls::getCatchRate() const {
    return catchRate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BattleItems::BattleItems() : Item() {
    stat = "No stat";
}
BattleItems::BattleItems(int quantity, const std::string &name, const std::string &stat) : Item(quantity, name) {
    this->stat = stat;
}

std::string BattleItems::getStat() const {
    return stat;
}
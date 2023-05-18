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

Item::Item(int quantity, const std::string& name) {
    this->quantity = quantity;
    this->name = name;
}

void Item::setQuantity(int newQuantity) { this->quantity = newQuantity; }
int Item::getQuantity() const { return this->quantity; }

std::string Item::getName() const { return this->name; }

std::ostream& operator<<(std::ostream &out, const Item &rhs) {
    out << rhs.name;
    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestoreItems::RestoreItems() : Item() {
    this->amount = 0;
    this->restoreType = "No restore type";
}
RestoreItems::RestoreItems(int quantity, int amount, const std::string& name, const std::string& restoreType) : Item(quantity, name){
    this->amount = amount;
    this->restoreType = restoreType;
}

int RestoreItems::getAmount() const { return this->amount; }

std::string RestoreItems::getRestoreType() const { return this->restoreType; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StatusItems::StatusItems() : Item() { this->restoreType = "No restore type"; }
StatusItems::StatusItems(const StatusItems &copy) = default;
StatusItems::StatusItems(int quantity, const std::string& name, const std::string& restoreType) : Item(quantity, name) { this->restoreType = restoreType; }

std::string StatusItems::getRestoreType() const { return this->restoreType; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PokeBalls::PokeBalls() : Item() { this->catchRate = 0.00f; }
PokeBalls::PokeBalls(int quantity, float catchRate, const std::string &name) : Item(quantity, name) { this->catchRate = catchRate; }

float PokeBalls::getCatchRate() const { return this->catchRate; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BattleItems::BattleItems() : Item() { this->stat = "No stat"; }
BattleItems::BattleItems(int quantity, const std::string &name, const std::string &stat) : Item(quantity, name) { this->stat = stat; }

std::string BattleItems::getStat() const { return this->stat; }
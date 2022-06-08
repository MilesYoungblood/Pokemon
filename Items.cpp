//
// Created by miles on 5/25/2022.
//

#include "Items.h"

Items::Items() {
    quantity = 0;
    name = "No name";
}

Items::Items(const Items& copy) {
    this->quantity = copy.quantity;
    this->name = copy.name;
}

Items::Items(int quantity, const std::string& name) {
    this->quantity = quantity;
    this->name = name;
}

void Items::setQuantity(int newQuantity) {
    quantity = newQuantity;
}
int Items::getQuantity() const {
    return quantity;
}

std::string Items::getName() const {
    return name;
}

void Items::useItem(Items& itemToUse) {
    itemToUse.setQuantity(itemToUse.getQuantity() - 1);
}

void Items::useItemMessage() {
    std::cout << "You used " << this->name << "! ";
    sleep(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestoreItems::RestoreItems() : Items() {
    amount = 0;
    restoreType = "No restore type";
}
RestoreItems::RestoreItems(int quantity, int amount, const std::string& name, const std::string& restoreType) : Items(quantity, name){
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

StatusItems::StatusItems() : Items() {
    restoreType = "No restore type";
}
StatusItems::StatusItems(const StatusItems &copy) = default;
StatusItems::StatusItems(int quantity, const std::string& name, const std::string& restoreType) : Items(quantity, name) {
    this->restoreType = restoreType;
}

std::string StatusItems::getRestoreType() const {
    return restoreType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PokeBalls::PokeBalls() : Items() {
    catchRate = 0.00;
}
PokeBalls::PokeBalls(int quantity, double catchRate, const std::string &name) : Items(quantity, name) {
    this->catchRate = catchRate;
}

double PokeBalls::getCatchRate() const {
    return catchRate;
}

void PokeBalls::useItemMessage() {
    std::cout << "You threw a " << this->getName() << '!' << std::endl;
    sleep(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BattleItems::BattleItems() : Items() {
    stat = "No stat";
}
BattleItems::BattleItems(int quantity, const std::string &name, const std::string &stat) : Items(quantity, name) {
    this->stat = stat;
}

std::string BattleItems::getStat() const {
    return stat;
}
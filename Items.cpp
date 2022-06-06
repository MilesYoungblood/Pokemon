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

void Items::SetQuantity(int newQuantity) {
    quantity = newQuantity;
}
int Items::GetQuantity() const {
    return quantity;
}

std::string Items::GetName() const {
    return name;
}

void Items::UseItem(Items& itemToUse) {
    itemToUse.SetQuantity(itemToUse.GetQuantity() - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestoreItems::RestoreItems() : Items() {
    amount = 0;
    rType = "No restore type";
}
RestoreItems::RestoreItems(int quantity, int amount, const std::string& name, const std::string& rType) : Items(quantity, name){
    this->amount = amount;
    this->rType = rType;
}

int RestoreItems::GetAmount() const {
    return amount;
}

std::string RestoreItems::GetRType() const {
    return rType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StatusItems::StatusItems() : Items() {
    rType = "No restore type";
}
StatusItems::StatusItems(const StatusItems &copy) = default;
StatusItems::StatusItems(int quantity, const std::string& name, const std::string& rType) : Items(quantity, name) {
    this->rType = rType;
}

std::string StatusItems::GetRType() const {
    return rType;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PokeBalls::PokeBalls() : Items() {
    catchRate = 0.00;
}
PokeBalls::PokeBalls(int quantity, double catchRate, const std::string &name) : Items(quantity, name) {
    this->catchRate = catchRate;
}

double PokeBalls::GetCatchRate() const {
    return catchRate;
}
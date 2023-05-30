//
// Created by Miles on 18/05/2023.
//

#include "RestoreItem.h"

RestoreItem::RestoreItem() : Item() {
    this->amount = 0;
    this->restoreType = "No restore type";
}
RestoreItem::RestoreItem(int quantity, int amount, const std::string& name, const std::string& restoreType) : Item(quantity, name){
    this->amount = amount;
    this->restoreType = restoreType;
}

int RestoreItem::getAmount() const { return this->amount; }

std::string RestoreItem::getRestoreType() const { return this->restoreType; }
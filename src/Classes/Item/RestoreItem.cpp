//
// Created by Miles on 18/05/2023.
//

#include "RestoreItem.h"

RestoreItem::RestoreItem() : Item() {
    this->amount = 0;
    this->restoreType = RestoreType::NONE;
}
RestoreItem::RestoreItem(int quantity, int amount, const char * name, RestoreType restoreType) : Item(quantity, name){
    this->amount = amount;
    this->restoreType = restoreType;
}

int RestoreItem::getAmount() const { return this->amount; }

RestoreType RestoreItem::getRestoreType() const { return this->restoreType; }
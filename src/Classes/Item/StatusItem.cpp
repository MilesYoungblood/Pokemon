//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem() : Item() { this->restoreType = "No restore type"; }
StatusItem::StatusItem(const StatusItem &copy) = default;
StatusItem::StatusItem(int quantity, const std::string& name, const std::string& restoreType) : Item(quantity, name) { this->restoreType = restoreType; }

std::string StatusItem::getRestoreType() const { return this->restoreType; }
//
// Created by Miles on 18/05/2023.
//

#include "StatusItem.h"

StatusItem::StatusItem() : Item() { this->status = Status::NONE; }
StatusItem::StatusItem(const StatusItem &copy) = default;
StatusItem::StatusItem(int quantity, const char * name, Status status) : Item(quantity, name) { this->status = status; }

Status StatusItem::getStatus() const { return this->status; }
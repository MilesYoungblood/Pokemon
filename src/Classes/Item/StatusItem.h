//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class StatusItem : public Item {
private:
    Status status;

public:
    StatusItem();
    StatusItem(const StatusItem &copy);
    StatusItem(int quantity, const char * name, Status status);

    Status getStatus() const override;
};
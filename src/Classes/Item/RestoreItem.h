//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class RestoreItem : public Item {
private:
    int amount;
    std::string restoreType;

public:
    RestoreItem();
    RestoreItem(int quantity, int amount, const char * name, const char * restoreType);

    int getAmount() const;
    std::string getRestoreType() const;
};
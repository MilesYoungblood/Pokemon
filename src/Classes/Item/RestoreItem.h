//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class RestoreItem : public Item {
private:
    int amount;
    RestoreType restoreType;

public:
    RestoreItem();
    RestoreItem(int n, int amount, const char * name, RestoreType restoreType);

    int getAmount() const override;
    RestoreType getRestoreType() const override;
};
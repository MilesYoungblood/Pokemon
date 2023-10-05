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
    RestoreItem(const char *name, int quantity, int amount, RestoreType restoreType);

    int getAmount() const override;
    RestoreType getRestoreType() const override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(Pokemon &pokemon) override;
    void restoreMessage(Move &move) override;
};
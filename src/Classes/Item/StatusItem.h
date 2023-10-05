//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class StatusItem : public Item {
private:
    Status status;

public:
    StatusItem(const char *name, int quantity, Status status);

    Status getStatus() const override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(Pokemon &pokemon) override;
    void restoreMessage(Move &move) override;
};
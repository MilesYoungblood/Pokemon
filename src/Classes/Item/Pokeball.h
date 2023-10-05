//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "Item.h"

class PokeBall : public Item {
protected:
    double catchRate;
    PokeBall(const char *name, int quantity, double catchRate);

public:
    explicit PokeBall(int n);

    void useMessage() override;

    void restore(Pokemon &pokemon) override;
    void restore(Move &move) override;
    void restoreMessage(Pokemon &pokemon) override;
    void restoreMessage(Move &move) override;

    __attribute__((unused)) double getCatchRate() const;
};
//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include "../../GameComponent.h"

class ResourceComponent : public GameComponent {
private:
    int currentAmount;
    int maxAmount;
    const int TRUE_MAX_AMOUNT;

public:
    ResourceComponent(int amount, int max);

    void increment(int amount);

    void decrement(int amount);

    [[nodiscard]] int getCurrentAmount() const;

    [[nodiscard]] int getMaxAmount() const;

    void increaseMax(int amount);

    void restore();
};

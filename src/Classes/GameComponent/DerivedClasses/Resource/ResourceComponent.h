//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include "../../GameComponent.h"
#include <algorithm>

class ResourceComponent : public GameComponent {
private:
    int currentAmount{ 0 };
    int maxAmount{ 0 };

public:
    explicit ResourceComponent(int amount) : currentAmount(amount), maxAmount(amount) {}

    void increment(int amount) {
        this->currentAmount = std::min(this->currentAmount + amount, this->maxAmount);
    }

    void decrement(int amount) {
        this->currentAmount = std::max(this->currentAmount - amount, 0);
    }

    [[nodiscard]] int getCurrentAmount() const {
        return this->currentAmount;
    }

    [[nodiscard]] int getMaxAmount() const {
        return this->maxAmount;
    }

    void increaseMax(int amount) {
        this->maxAmount += amount;
    }

    void restore() {
        this->currentAmount = this->maxAmount;
    }
};

//
// Created by Miles Youngblood on 12/3/2023.
//

#include "ResourceComponent.h"

ResourceComponent::ResourceComponent(int amount, int max) : currentAmount(amount), maxAmount(amount), TRUE_MAX_AMOUNT(max) {}

void ResourceComponent::increment(int amount) {
    this->currentAmount = std::min(this->currentAmount + amount, this->maxAmount);
}

void ResourceComponent::decrement(int amount) {
    this->currentAmount = std::max(this->currentAmount - amount, 0);
}

int ResourceComponent::getCurrentAmount() const {
    return this->currentAmount;
}

int ResourceComponent::getMaxAmount() const {
    return this->maxAmount;
}

void ResourceComponent::increaseMax(int amount) {
    this->maxAmount = std::min(this->maxAmount + amount, this->TRUE_MAX_AMOUNT);
}

void ResourceComponent::restore() {
    this->currentAmount = this->maxAmount;
}

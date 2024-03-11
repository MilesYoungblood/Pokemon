//
// Created by Miles Youngblood on 12/6/2023.
//

#include "IceHeal.h"

IceHeal::IceHeal(int n) : StatusItem(n) {}

std::string IceHeal::getName() const {
    return "Ice Heal";
}

std::string IceHeal::getEffect() const {
    return "A spray-type medicine. It defrosts a Pokemon that has been frozen solid.";
}

StatusCondition IceHeal::getStatus() const {
    return StatusCondition::FREEZE;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Ice Heal"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<IceHeal>(n); };
    });
}

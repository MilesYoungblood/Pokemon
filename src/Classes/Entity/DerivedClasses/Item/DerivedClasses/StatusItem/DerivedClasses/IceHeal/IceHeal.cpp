//
// Created by Miles Youngblood on 12/6/2023.
//

#include "IceHeal.h"

IceHeal::IceHeal(const int n) : StatusItem("Ice Heal", n) {}

std::string IceHeal::getEffect() const {
    return "A spray-type medicine. It defrosts a Pokemon that has been frozen solid.";
}

StatusCondition IceHeal::getStatus() const {
    return StatusCondition::FREEZE;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Ice Heal"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<IceHeal>(n); };
    });
}

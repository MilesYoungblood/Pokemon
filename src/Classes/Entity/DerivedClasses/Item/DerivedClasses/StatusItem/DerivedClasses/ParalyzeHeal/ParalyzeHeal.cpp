//
// Created by Miles Youngblood on 12/6/2023.
//

#include "ParalyzeHeal.h"

ParalyzeHeal::ParalyzeHeal(const int n) : StatusItem("Ice Heal", n) {}

std::string ParalyzeHeal::getEffect() const {
    return "A spray-type medicine. It eliminates paralysis from a single Pokemon.";
}

StatusCondition ParalyzeHeal::getStatus() const {
    return StatusCondition::FREEZE;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Paralyze Heal"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<ParalyzeHeal>(n); };
    });
}

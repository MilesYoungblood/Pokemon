//
// Created by Miles Youngblood on 12/6/2023.
//

#include "BurnHeal.h"

BurnHeal::BurnHeal(int n) : StatusItem(n) {}

std::string BurnHeal::getName() const {
    return "Burn Heal";
}

std::string BurnHeal::getEffect() const {
    return "A spray-type medicine. It heals a single Pokemon that is suffering from a burn.";
}

StatusCondition BurnHeal::getStatus() const {
    return StatusCondition::BURN;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(statusItemMutex);
        statusItems["Burn Heal"] = [](int n) -> std::unique_ptr<StatusItem> { return std::make_unique<BurnHeal>(n); };
    });
}

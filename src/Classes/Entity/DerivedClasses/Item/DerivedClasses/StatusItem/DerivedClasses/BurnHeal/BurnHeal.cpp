//
// Created by Miles Youngblood on 12/6/2023.
//

#include "BurnHeal.h"

BurnHeal::BurnHeal(const int n) : StatusItem("Burn Heal", n) {}

std::string BurnHeal::getEffect() const {
    return "A spray-type medicine. It heals a single Pokemon that is suffering from a burn.";
}

StatusCondition BurnHeal::getStatus() const {
    return StatusCondition::BURN;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Burn Heal"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<BurnHeal>(n); };
    });
}

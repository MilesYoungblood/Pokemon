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

StatusItem::Id BurnHeal::getId() const {
    return StatusItem::Id::BURN_HEAL;
}

namespace {
    AutoThread init([] -> void {
        statusItems.insert(std::make_pair(StatusItem::Id::BURN_HEAL, [](int n) -> std::unique_ptr<StatusItem> {
            return std::make_unique<BurnHeal>(n);
        }));
    });
}

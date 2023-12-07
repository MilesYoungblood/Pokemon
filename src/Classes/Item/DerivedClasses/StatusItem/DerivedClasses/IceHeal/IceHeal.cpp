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

StatusItem::Id IceHeal::getId() const {
    return StatusItem::Id::ICE_HEAL;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(statusItemMutex);
        statusItems.insert(std::make_pair(StatusItem::Id::ICE_HEAL, [](int n) -> std::unique_ptr<StatusItem> {
            return std::make_unique<IceHeal>(n);
        }));
    });
}

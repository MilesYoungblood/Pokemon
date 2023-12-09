//
// Created by Miles Youngblood on 12/6/2023.
//

#include "ParalyzeHeal.h"

ParalyzeHeal::ParalyzeHeal(int n) : StatusItem(n) {}

std::string ParalyzeHeal::getName() const {
    return "Ice Heal";
}

std::string ParalyzeHeal::getEffect() const {
    return "A spray-type medicine. It eliminates paralysis from a single Pokemon.";
}

StatusCondition ParalyzeHeal::getStatus() const {
    return StatusCondition::FREEZE;
}

StatusItem::Id ParalyzeHeal::getId() const {
    return StatusItem::Id::PARALYZE_HEAL;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(statusItemMutex);
        statusItems.insert(std::make_pair(StatusItem::Id::PARALYZE_HEAL, [](int n) -> std::unique_ptr<StatusItem> {
            return std::make_unique<ParalyzeHeal>(n);
        }));
    });
}

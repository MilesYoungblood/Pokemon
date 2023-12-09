//
// Created by Miles Youngblood on 12/6/2023.
//

#include "Antidote.h"

Antidote::Antidote(int n) : StatusItem(n) {}

std::string Antidote::getName() const {
    return "Antidote";
}

std::string Antidote::getEffect() const {
    return "A spray-type medicine. It lifts the effect of poison from one Pokemon.";
}

StatusCondition Antidote::getStatus() const {
    return StatusCondition::POISON;
}

StatusItem::Id Antidote::getId() const {
    return StatusItem::Id::ANTIDOTE;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(statusItemMutex);
        statusItems.insert(std::make_pair(StatusItem::Id::ANTIDOTE, [](int n) -> std::unique_ptr<StatusItem> {
            return std::make_unique<Antidote>(n);
        }));
    });
}

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

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(statusItemMutex);
        statusItems["Antidote"] = [](int n) -> std::unique_ptr<StatusItem> { return std::make_unique<Antidote>(n); };
    });
}

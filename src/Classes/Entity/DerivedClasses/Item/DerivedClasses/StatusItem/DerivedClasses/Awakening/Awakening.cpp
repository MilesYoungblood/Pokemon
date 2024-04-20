//
// Created by Miles Youngblood on 12/6/2023.
//

#include "Awakening.h"

Awakening::Awakening(const int n) : StatusItem("Awakening", n) {}

std::string Awakening::getEffect() const {
    return "A spray-type medicine. It awakens a Pokemon from the clutches of sleep.";
}

StatusCondition Awakening::getStatus() const {
    return StatusCondition::SLEEP;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Awakening"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<Awakening>(n); };
    });
}

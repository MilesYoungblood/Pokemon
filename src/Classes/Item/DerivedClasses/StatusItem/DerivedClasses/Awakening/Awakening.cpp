//
// Created by Miles Youngblood on 12/6/2023.
//

#include "Awakening.h"

Awakening::Awakening(int n) : StatusItem(n) {}

std::string Awakening::getName() const {
    return "Awakening";
}

std::string Awakening::getEffect() const {
    return "A spray-type medicine. It awakens a Pokemon from the clutches of sleep.";
}

StatusCondition Awakening::getStatus() const {
    return StatusCondition::SLEEP;
}

StatusItem::Id Awakening::getId() const {
    return StatusItem::Id::AWAKENING;
}

namespace {
    AutoThread init([] -> void {
        statusItems.insert(std::make_pair(StatusItem::Id::AWAKENING, [](int n) -> std::unique_ptr<StatusItem> {
            return std::make_unique<Awakening>(n);
        }));
    });
}

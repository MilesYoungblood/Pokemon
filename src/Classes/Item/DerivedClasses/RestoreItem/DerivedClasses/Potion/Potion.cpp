//
// Created by Miles Youngblood on 12/6/2023.
//

#include "Potion.h"

Potion::Potion(int n) : RestoreItem(n) {}

std::string Potion::getName() const {
    return "Potion";
}

std::string Potion::getEffect() const {
    return "A spray-type medicine for wounds. It restores the HP of one Pokemon by just 20 points.";
}

int Potion::getAmount() const {
    return 20;
}

bool Potion::isHp() const {
    return true;
}

RestoreItem::Id Potion::getId() const {
    return RestoreItem::Id::POTION;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(restoreItemMutex);
        restoreItems.insert(std::make_pair(RestoreItem::Id::POTION, [](int n) -> std::unique_ptr<RestoreItem> {
            return std::make_unique<Potion>(n);
        }));
    });
}

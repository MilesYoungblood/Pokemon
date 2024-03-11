//
// Created by Miles Youngblood on 12/6/2023.
//

#include "SuperPotion.h"

SuperPotion::SuperPotion(int n) : RestoreItem(n) {}

std::string SuperPotion::getName() const {
    return "Super Potion";
}

std::string SuperPotion::getEffect() const {
    return "A spray-type medicine for wounds. It restores the HP of one Pokemon by 50 points.";
}

int SuperPotion::getAmount() const {
    return 50;
}

bool SuperPotion::isHp() const {
    return true;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(restoreItemMutex);
        restoreItems["Super Potion"] = [](int n) -> std::unique_ptr<RestoreItem> { return std::make_unique<SuperPotion>(n); };
    });
}

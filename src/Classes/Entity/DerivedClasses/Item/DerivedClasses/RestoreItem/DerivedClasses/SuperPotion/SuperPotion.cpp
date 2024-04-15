//
// Created by Miles Youngblood on 12/6/2023.
//

#include "SuperPotion.h"

SuperPotion::SuperPotion(const int n) : RestoreItem(n) {}

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
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Super Potion"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<SuperPotion>(n); };
    });
}

//
// Created by Miles Youngblood on 12/6/2023.
//

#include "HyperPotion.h"

HyperPotion::HyperPotion(const int n) : RestoreItem(n) {}

std::string HyperPotion::getName() const {
    return "Hyper Potion";
}

std::string HyperPotion::getEffect() const {
    return "A spray-type medicine for wounds. It restores the HP of one Pokemon by 200 points.";
}

int HyperPotion::getAmount() const {
    return 200;
}

bool HyperPotion::isHp() const {
    return true;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Hyper Potion"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<HyperPotion>(n); };
    });
}

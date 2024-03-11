//
// Created by Miles Youngblood on 12/6/2023.
//

#include "MaxPotion.h"

MaxPotion::MaxPotion(int n) : RestoreItem(n) {}

std::string MaxPotion::getName() const {
    return "Max Potion";
}

std::string MaxPotion::getEffect() const {
    return "A spray-type medicine for wounds. It completely restores the HP of a single Pokemon.";
}

int MaxPotion::getAmount() const {
    return std::numeric_limits<int>::max() / 2;
}

bool MaxPotion::isHp() const {
    return true;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(restoreItemMutex);
        restoreItems["Max Potion"] = [](int n) -> std::unique_ptr<RestoreItem> { return std::make_unique<MaxPotion>(n); };
    });
}

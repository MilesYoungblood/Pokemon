//
// Created by Miles Youngblood on 12/6/2023.
//

#include "MaxPotion.h"

MaxPotion::MaxPotion(const int n) : RestoreItem(n) {}

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
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Max Potion"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<MaxPotion>(n); };
    });
}

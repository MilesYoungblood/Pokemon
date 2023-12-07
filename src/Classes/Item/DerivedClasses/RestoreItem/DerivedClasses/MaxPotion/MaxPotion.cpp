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

RestoreItem::Id MaxPotion::getId() const {
    return RestoreItem::Id::MAX_POTION;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(restoreItemMutex);
        restoreItems.insert(std::make_pair(RestoreItem::Id::MAX_POTION, [](int n) -> std::unique_ptr<RestoreItem> {
            return std::make_unique<MaxPotion>(n);
        }));
    });
}

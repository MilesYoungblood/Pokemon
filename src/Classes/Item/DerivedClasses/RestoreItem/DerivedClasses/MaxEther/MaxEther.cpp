//
// Created by Miles Youngblood on 12/6/2023.
//

#include "MaxEther.h"

MaxEther::MaxEther(int n) : RestoreItem(n) {}

std::string MaxEther::getName() const {
    return "MaxEther";
}

std::string MaxEther::getEffect() const {
    return "Restores 20 HP.";
}

int MaxEther::getAmount() const {
    return std::numeric_limits<int>::max() / 2;
}

bool MaxEther::isHp() const {
    return false;
}

RestoreItem::Id MaxEther::getId() const {
    return RestoreItem::Id::MAX_ETHER;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(restoreItemMutex);
        restoreItems.insert(std::make_pair(RestoreItem::Id::MAX_ETHER, [](int n) -> std::unique_ptr<RestoreItem> {
            return std::make_unique<MaxEther>(n);
        }));
    });
}

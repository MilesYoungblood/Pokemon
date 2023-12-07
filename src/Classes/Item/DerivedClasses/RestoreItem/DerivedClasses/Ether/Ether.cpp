//
// Created by Miles Youngblood on 12/6/2023.
//

#include "Ether.h"

Ether::Ether(int n) : RestoreItem(n) {}

std::string Ether::getName() const {
    return "Ether";
}

std::string Ether::getEffect() const {
    return "Restores 10 PP.";
}

int Ether::getAmount() const {
    return 10;
}

bool Ether::isHp() const {
    return false;
}

RestoreItem::Id Ether::getId() const {
    return RestoreItem::Id::ETHER;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(restoreItemMutex);
        restoreItems.insert(std::make_pair(RestoreItem::Id::ETHER, [](int n) -> std::unique_ptr<RestoreItem> {
            return std::make_unique<Ether>(n);
        }));
    });
}

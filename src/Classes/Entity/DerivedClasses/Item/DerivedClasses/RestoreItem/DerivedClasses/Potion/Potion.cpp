//
// Created by Miles Youngblood on 12/6/2023.
//

#include "Potion.h"

Potion::Potion(const int n) : RestoreItem("Potion", n) {}

std::string Potion::getEffect() const {
    return "A spray-type medicine for wounds. It restores the HP of one Pokemon by just 20 points.";
}

int Potion::getAmount() const {
    return 20;
}

bool Potion::isHp() const {
    return true;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Potion"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<Potion>(n); };
    });
}

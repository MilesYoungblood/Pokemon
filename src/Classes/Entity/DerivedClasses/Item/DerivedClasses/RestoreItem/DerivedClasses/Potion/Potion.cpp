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

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Potion"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<Potion>(n); };
    });
}

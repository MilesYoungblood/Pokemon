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

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Ether"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<Ether>(n); };
    });
}

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

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Max Ether"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<MaxEther>(n); };
    });
}

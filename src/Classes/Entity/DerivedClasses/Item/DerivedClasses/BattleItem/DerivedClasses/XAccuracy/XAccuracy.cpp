//
// Created by Miles Youngblood on 12/6/2023.
//

#include "XAccuracy.h"

XAccuracy::XAccuracy(int n) : BattleItem(n) {}

std::string XAccuracy::getName() const {
    return "X Accuracy";
}

std::string XAccuracy::getEffect() const {
    return "An item that raises the Accuracy stat of a Pokemon in battle. It wears off if the Pokemon is withdrawn.";
}

Pokemon::Stat XAccuracy::getStat() const {
    return Pokemon::Stat::ACCURACY;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["X Accuracy"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<XAccuracy>(n); };
    });
}

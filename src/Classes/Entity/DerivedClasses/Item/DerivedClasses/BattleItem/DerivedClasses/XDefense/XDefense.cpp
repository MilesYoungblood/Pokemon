//
// Created by Miles Youngblood on 12/5/2023.
//

#include "XDefense.h"

XDefense::XDefense(int n) : BattleItem(n) {}

std::string XDefense::getName() const {
    return "X Defense";
}

std::string XDefense::getEffect() const {
    return "An item that raises the Defense stat of a Pokemon in battle. It wears off if the Pokemon is withdrawn.";
}

Pokemon::Stat XDefense::getStat() const {
    return Pokemon::Stat::DEFENSE;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["X Defense"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<XDefense>(n); };
    });
}

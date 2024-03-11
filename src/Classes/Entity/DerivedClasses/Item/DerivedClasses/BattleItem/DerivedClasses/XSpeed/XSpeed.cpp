//
// Created by Miles Youngblood on 12/6/2023.
//

#include "XSpeed.h"

XSpeed::XSpeed(int n) : BattleItem(n) {}

std::string XSpeed::getName() const {
    return "X Speed";
}

std::string XSpeed::getEffect() const {
    return "An item that raises the Speed stat of a Pokemon in battle. It wears off if the Pokemon is withdrawn.";
}

Pokemon::Stat XSpeed::getStat() const {
    return Pokemon::Stat::SPEED;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["X Speed"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<XSpeed>(n); };
    });
}

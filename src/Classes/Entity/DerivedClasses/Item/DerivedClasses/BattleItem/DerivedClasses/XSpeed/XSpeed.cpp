//
// Created by Miles Youngblood on 12/6/2023.
//

#include "XSpeed.h"

XSpeed::XSpeed(const int n) : BattleItem(n) {}

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
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["X Speed"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<XSpeed>(n); };
    });
}

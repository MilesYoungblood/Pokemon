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

BattleItem::Id XSpeed::getId() const {
    return BattleItem::Id::X_SPEED;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(battleItemMutex);
        battleItems.insert(std::make_pair(BattleItem::Id::X_SPEED, [](int n) -> std::unique_ptr<BattleItem> {
            return std::make_unique<XSpeed>(n);
        }));
    });
}

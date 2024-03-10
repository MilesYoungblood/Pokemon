//
// Created by Miles Youngblood on 12/5/2023.
//

#include "XAttack.h"

XAttack::XAttack(int n) : BattleItem(n) {}

std::string XAttack::getName() const {
    return "X Attack";
}

std::string XAttack::getEffect() const {
    return "An item that raises the Attack stat of a Pokemon in battle. It wears off if the Pokemon is withdrawn.";
}

Pokemon::Stat XAttack::getStat() const {
    return Pokemon::Stat::ATTACK;
}

BattleItem::Id XAttack::getId() const {
    return BattleItem::Id::X_ATTACK;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(battleItemMutex);
        battleItems.insert(std::make_pair(BattleItem::Id::X_ATTACK, [](int n) -> std::unique_ptr<BattleItem> {
            return std::make_unique<XAttack>(n);
        }));
    });
}

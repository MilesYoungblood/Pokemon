//
// Created by Miles Youngblood on 12/5/2023.
//

#include "XSpAttack.h"

XSpAttack::XSpAttack(int n) : BattleItem(n) {}

std::string XSpAttack::getName() const {
    return "X Sp. Attack";
}

std::string XSpAttack::getEffect() const {
    return "An item that raises the Sp. Atk stat of a Pokemon in battle. It wears off if the Pokemon is withdrawn.";
}

Pokemon::Stat XSpAttack::getStat() const {
    return Pokemon::Stat::SP_ATTACK;
}

BattleItem::Id XSpAttack::getId() const {
    return BattleItem::Id::X_SP_ATTACK;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(battleItemMutex);
        battleItems.insert(std::make_pair(BattleItem::Id::X_SP_ATTACK, [](int n) -> std::unique_ptr<BattleItem> {
            return std::make_unique<XSpAttack>(n);
        }));
    });
}

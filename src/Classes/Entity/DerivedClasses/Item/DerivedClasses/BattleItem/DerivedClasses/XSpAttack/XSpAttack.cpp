//
// Created by Miles Youngblood on 12/5/2023.
//

#include "XSpAttack.h"

XSpAttack::XSpAttack(const int n) : BattleItem(n) {}

std::string XSpAttack::getName() const {
    return "X Sp. Attack";
}

std::string XSpAttack::getEffect() const {
    return "An item that raises the Sp. Atk stat of a Pokemon in battle. It wears off if the Pokemon is withdrawn.";
}

Pokemon::Stat XSpAttack::getStat() const {
    return Pokemon::Stat::SP_ATTACK;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["X Sp. Attack"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<XSpAttack>(n); };
    });
}

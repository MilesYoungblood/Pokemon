//
// Created by Miles Youngblood on 12/5/2023.
//

#include "XSpDefense.h"

XSpDefense::XSpDefense(int n) : BattleItem(n) {}

std::string XSpDefense::getName() const {
    return "X Sp. Defense";
}

std::string XSpDefense::getEffect() const {
    return "An item that raises the Sp. Def stat of a Pokemon in battle. It wears off if the Pokemon is withdrawn.";
}

Pokemon::Stat XSpDefense::getStat() const {
    return Pokemon::Stat::SP_DEFENSE;
}

BattleItem::Id XSpDefense::getId() const {
    return BattleItem::Id::X_SP_DEFENSE;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(battleItemMutex);
        battleItems.insert(std::make_pair(BattleItem::Id::X_SP_DEFENSE, [](int n) -> std::unique_ptr<BattleItem> {
            return std::make_unique<XSpDefense>(n);
        }));
    });
}

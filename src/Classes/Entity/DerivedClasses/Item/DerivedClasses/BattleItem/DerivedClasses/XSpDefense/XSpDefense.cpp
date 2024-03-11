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

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(battleItemMutex);
        battleItems["X Sp. Defense"] = [](int n) -> std::unique_ptr<BattleItem> { return std::make_unique<XSpDefense>(n); };
    });
}

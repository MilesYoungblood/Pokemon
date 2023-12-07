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

BattleItem::Id XDefense::getId() const {
    return BattleItem::Id::X_DEFENSE;
}

namespace {
    AutoThread init([] -> void {
        battleItems.insert(std::make_pair(BattleItem::Id::X_DEFENSE, [](int n) -> std::unique_ptr<BattleItem> {
            return std::make_unique<XDefense>(n);
        }));
    });
}

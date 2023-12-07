//
// Created by Miles Youngblood on 12/6/2023.
//

#include "XAccuracy.h"

XAccuracy::XAccuracy(int n) : BattleItem(n) {}

std::string XAccuracy::getName() const {
    return "X Accuracy";
}

std::string XAccuracy::getEffect() const {
    return "An item that raises the Accuracy stat of a Pokemon in battle. It wears off if the Pokemon is withdrawn.";
}

Pokemon::Stat XAccuracy::getStat() const {
    return Pokemon::Stat::ACCURACY;
}

BattleItem::Id XAccuracy::getId() const {
    return BattleItem::Id::X_ACCURACY;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(battleItemMutex);
        battleItems.insert(std::make_pair(BattleItem::Id::X_ACCURACY, [](int n) -> std::unique_ptr<BattleItem> {
            return std::make_unique<XAccuracy>(n);
        }));
    });
}

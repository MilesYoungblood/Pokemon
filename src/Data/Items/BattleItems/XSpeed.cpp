//
// Created by Miles on 11/27/2023.
//

#include "BattleItems.h"

namespace {
    void init() {
        battleItems.insert({ BattleItem::Id::X_SPEED, {
                "X Speed",
                Pokemon::Stat::SPEED,
        }});
    }

    bool invoke{ (init(), true) };
}

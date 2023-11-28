//
// Created by Miles on 11/27/2023.
//

#include "BattleItems.h"

namespace {
    void init() {
        battleItems.insert({ BattleItem::Id::X_DEFENSE, {
                "X Defense",
                Pokemon::Stat::DEFENSE,
        }});
    }

    bool invoke{ (init(), true) };
}

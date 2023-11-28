//
// Created by Miles on 11/27/2023.
//

#include "BattleItems.h"

namespace {
    void init() {
        battleItems.insert({ BattleItem::Id::X_ATTACK, {
                "X Attack",
                Pokemon::Stat::ATTACK,
        }});
    }

    bool invoke{ (init(), true) };
}
